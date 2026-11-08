/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stratosphere.hpp>
#include "pcv_rgltr.hpp"

#include "../gpio/pcv_gpio_handle.hpp"
#include "../pcv_i2c.hpp"

#include "pcv_rgltr_volt_max77621.hpp"

namespace ams::pcv::rgltr {

    namespace {

        bool NeedsSetup(Regulator &regulator) {
            constexpr const char Name[] = "max77621";

            return std::strncmp(regulator.name, Name, sizeof(Name) - 1) == 0 && !regulator.is_initialized;
        }

        void WriteControlInitRegisters(Regulator &regulator) {
            R_DISCARD(I2cWrite(*regulator.session, Max77621Control1Reg, regulator.ctrl_reg1));
            R_DISCARD(I2cWrite(*regulator.session, Max77621Control2Reg, regulator.ctrl_reg2));
        }

        Result DisableRegulator(size_t idx) {
            Regulator &regulator = GetRegulator(idx);

            if (!regulator.enable_count) {
                /* Already disabled */
                return ResultSuccess();
            }

            --regulator.enable_count;

            /* Nothing more needs to be done. */
            if (regulator.enable_count) {
                return ResultSuccess();
            }

            /* We need to disable vout entirely. */
            u8 vout;
            R_TRY(I2cRead(*regulator.session, Max77621VoutReg, vout));

            vout &= Max77621DvcDvsVoltMask;
            R_TRY(I2cWrite(*regulator.session, Max77621VoutReg, vout));

            if (regulator.disable_delay_us) {
                svc::SleepThread(static_cast<u64>(1000) * regulator.disable_delay_us);
            }

            return ResultSuccess();
        }

        Result SetupDirection(Regulator &regulator) {
            /* Nintendo treats a failed read the same as the pin being an input. */
            gpio::GpioDirection direction = gpio::GpioDirection_Input;
            if (R_FAILED(gpio::GetDirection(std::addressof(regulator.gpio_handle), direction))) {
                direction = gpio::GpioDirection_Input;
            }

            /* Ensure the direction is an output. */
            if (direction != gpio::GpioDirection_Output) {
                R_TRY(gpio::SetDirection(std::addressof(regulator.gpio_handle), gpio::GpioDirection_Output));
            }

            R_SUCCEED();
        }

        void SetupDriveMode(Regulator &regulator) {
            /* Nintendo treats a failed read the same as the pin not being push pull. */
            gpio::GpioDriveMode drive_mode = gpio::GpioDriveMode_OpenDrain;
            if (R_FAILED(gpio::GetDriveMode(std::addressof(regulator.gpio_handle), drive_mode))) {
                drive_mode = gpio::GpioDriveMode_OpenDrain;
            }

            /* Ensure the drive mode is push pull */
            if (drive_mode != gpio::GpioDriveMode_PushPull) {
                R_DISCARD(gpio::SetDriveMode(std::addressof(regulator.gpio_handle), gpio::GpioDriveMode_PushPull));
                R_DISCARD(gpio::GetDriveMode(std::addressof(regulator.gpio_handle), drive_mode));
            }
        }

        void SetupGpioOutput(Regulator &regulator, size_t idx) {
            /* Read the output value. */
            u8 output_value = 2;
            if (R_FAILED(gpio::GetOutputValue(std::addressof(regulator.gpio_handle), output_value))) {
                output_value = 2;
            }
            const bool gpio_is_high = output_value == 1;

            u8 vout;
            if (R_FAILED(I2cRead(*regulator.session, Max77621VoutReg, vout))) {
                /* Assume it's disabled and raise the gpio. */
                R_DISCARD(gpio::SetOutputValue(std::addressof(regulator.gpio_handle), 1));
                regulator.enable_count = 0;
                return;
            }

            const bool vout_enabled = (vout & Max77621DvcDvsEnableMask) != 0;

            if (vout_enabled) {
                if (gpio_is_high) {
                    /* Everything is already good. */
                    regulator.enable_count = 1;
                } else {
                    /* The regulator is enabled, but the gpio is low. Reset it. */
                    /* Note: enable_count is zeroed first, so Nintendo's DisableRegulator call is a no-op. */
                    regulator.enable_count = 0;
                    R_DISCARD(DisableRegulator(idx));
                    R_DISCARD(gpio::SetOutputValue(std::addressof(regulator.gpio_handle), 1));
                }
            } else if (regulator.enable_count == 0) {
                R_DISCARD(gpio::SetOutputValue(std::addressof(regulator.gpio_handle), 1));
                regulator.enable_count = 0;
            } else if (gpio_is_high) {
                regulator.enable_count = 1;
            } else {
                /* Disable it, enable_count was set to 0 first so Nintendo's disable is a no-op. */
                regulator.enable_count = 0;
                R_DISCARD(DisableRegulator(idx));
                R_DISCARD(gpio::SetOutputValue(std::addressof(regulator.gpio_handle), 1));
            }
        }

        Result SetupGpio(Regulator &regulator, size_t idx) {
            /* Set device name. */
            gpio::SetDeviceHandleName(std::addressof(regulator.gpio_handle), regulator.gpio_name);

            /* (this is just to read a register lol) */
            R_DISCARD(gpio::ReadAlternateMode(std::addressof(regulator.gpio_handle)));

            R_TRY(SetupDirection(regulator));
            SetupDriveMode(regulator);

            /* Read the pull state. */
            {
                gpio::GpioPullState state;
                R_DISCARD(gpio::GetPullState(std::addressof(regulator.gpio_handle), state));
            }

            SetupGpioOutput(regulator, idx);

            R_SUCCEED();
        }

        enum RampCode : u8 {
            Ramp12mVPerUs  = 0,
            Ramp25mVPerUs  = 1,
            Ramp50mVPerUs  = 2,
            Ramp200mVPerUs = 3,
        };

        struct Max77621Ramp {
            RampCode code;
            u32 uv_per_us;
        };

        Max77621Ramp SelectRamp(u32 requested_value) {
            if (requested_value >= 200000) {
                return { Ramp200mVPerUs, 200000, };
            } else if (requested_value >= 50000) {
                return { Ramp50mVPerUs, 50000, };
            } else if (requested_value >= 25000) {
                return { Ramp25mVPerUs, 25000, };
            } else {
                return { Ramp12mVPerUs, 12000, };
            }
        }

        Result ConfigureRamp(Regulator &regulator) {
            /* Select the ramp. */
            const Max77621Ramp ramp = SelectRamp(regulator.ramp_rate_uv_per_us);

            /* Set the ramp. */
            u8 ctrl1;
            R_TRY(I2cRead(*regulator.session, Max77621Control1Reg, ctrl1));

            ctrl1 = (ctrl1 & ~Max77621RampMask) | ramp.code;
            R_TRY(I2cWrite(*regulator.session, Max77621Control1Reg, ctrl1));

            regulator.ramp_rate_uv_per_us = ramp.uv_per_us;

            return ResultSuccess();
        }

    }

    void InitializeMax77621() {
        for (size_t i = 0; i < RegulatorCount; ++i) {
            Regulator &regulator = GetRegulator(i);

            if (!NeedsSetup(regulator)) {
                continue;
            }

            /* Open the session. */
            R_ABORT_UNLESS(i2c::OpenSession(regulator.session, static_cast<DeviceCode>(regulator.i2c_device_code)));

            WriteControlInitRegisters(regulator);

            if (regulator.always_on) {
                regulator.enable_count = 1;
            } else {
                /* Gpio setup. */
                if (regulator.gpio_name != nullptr) {
                    const bool gpio_res = R_SUCCEEDED(SetupGpio(regulator, i));
                    R_DISCARD(gpio::FinalizeHandle(std::addressof(regulator.gpio_handle)));

                    if (!gpio_res) {
                        i2c::CloseSession(*regulator.session);
                        continue;
                    }
                }

                /* Configure the ramp rate. */
                if (R_FAILED(ConfigureRamp(regulator))) {
                    i2c::CloseSession(*regulator.session);
                    continue;
                }

                /* Apply initial voltage. */
                R_DISCARD(SetVoltageMax77621(i, regulator.dvfs_pmic.default_uv));
            }

            regulator.is_initialized = true;
            i2c::CloseSession(*regulator.session);
        }
    }

}
