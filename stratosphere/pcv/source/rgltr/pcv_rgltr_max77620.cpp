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
#include "pcv_rgltr_max77620.hpp"
#include "pcv_rgltr_max77620_impl.hpp"
#include "pcv_rgltr_common_volt.hpp"
#include "../pcv_i2c.hpp"

namespace ams::pcv::rgltr {

    namespace max77620 {

        namespace {

            constexpr u32 AbpdevPmcNoIoPower = 0x44;

            u8 GetEnableRegister(const Regulator &regulator) {
                return regulator.is_ldo ? regulator.volt_reg : regulator.config_reg;
            }

            u32 ReadPmcNoIoPower(const Regulator &regulator) {
                u32 no_io_power = 0;
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_power), regulator.pmc_mmio + AbpdevPmcNoIoPower, 0, 0));
                return no_io_power;
            }

            void WritePmcNoIoPower(const Regulator &regulator, u32 value) {
                u32 no_io_power = 0;
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_power), regulator.pmc_mmio + AbpdevPmcNoIoPower, ~0, value));

                /* Nintendo rereads the value twice. */
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_power), regulator.pmc_mmio + AbpdevPmcNoIoPower, 0, 0));
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_power), regulator.pmc_mmio + AbpdevPmcNoIoPower, 0, 0));
            }

        }

        Result ReadEnabledRegister(u32 idx, u32 *enabled) {
            Regulator &regulator = GetRegulator(idx);
            const u8 enable_register = GetEnableRegister(regulator);

            u8 out;
            R_TRY(I2cRead(*regulator.session, enable_register, out));

            *enabled = static_cast<u8>(out & regulator.enable_mask) >> regulator.enable_shift;

            R_SUCCEED();
        }

        Result WriteEnabledRegister(u32 idx, u8 enabled) {
            Regulator &regulator = GetRegulator(idx);
            const u8 enable_register = GetEnableRegister(regulator);

            u8 value;
            R_TRY(I2cRead(*regulator.session, enable_register, value));

            value = (value & ~regulator.enable_mask) | (regulator.enable_mask & (enabled << regulator.enable_shift));

            R_RETURN(I2cWrite(*regulator.session, enable_register, value));
        }

        void SetPmcNoIoPowerBit(const Regulator &regulator) {
            WritePmcNoIoPower(regulator, ReadPmcNoIoPower(regulator) | regulator.pmc_bit);
        }

        void ClearPmcNoIoPowerBit(const Regulator &regulator) {
            WritePmcNoIoPower(regulator, ReadPmcNoIoPower(regulator) & ~regulator.pmc_bit);
        }

    }

    using namespace max77620;

    namespace {

        Result IsPowerGood(bool &out, const Regulator &regulator) {
            u8 status;

            if (regulator.is_ldo) {
                R_TRY(I2cRead(*regulator.session, regulator.config_reg, status));
                out = (status & Max77620PmicLdoPowerOkMask) != 0;
            } else {
                R_TRY(I2cRead(*regulator.session, Max77620PmicStatSdReg, status));
                out = (status & regulator.sd_status_mask) == 0;
            }

            R_SUCCEED();
        }

        Result WaitForPowerGood(const Regulator &regulator) {
            /* 1s max polling. */
            constexpr u32 EnablePollPeriodUs     = 50;
            constexpr u32 EnablePollCount        = 20021;
            constexpr Result ResultEnableTimeout = -14;

            for (u32 i = 0; i < EnablePollCount; ++i) {
                bool power_good;
                R_TRY(IsPowerGood(power_good, regulator));

                if (power_good) {
                    svc::SleepThread(static_cast<s64>(1000) * regulator.enable_delay_us);
                    R_SUCCEED();
                }

                svc::SleepThread(static_cast<s64>(1000) * EnablePollPeriodUs);
            }

            return ResultEnableTimeout;
        }

        bool IsSafeVoltage(const Regulator &regulator, u32 voltage) {
            /* NOTE: Nintendo uses default_uv as the lower bound. Might be a bug? */
            return IsVoltageInRange(voltage, regulator.main_pmic.default_uv, regulator.main_pmic.max_uv);
        }

        u8 GetVoltCode(const Regulator &regulator, u32 voltage) {
            return GetVoltCodeImpl(voltage, regulator.main_pmic.min_uv, regulator.main_pmic.step_uv);
        }

        u32 GetVoltageFromCode(const Regulator &regulator, u8 volt_code) {
            return GetVoltageFromCodeImpl(volt_code, regulator.main_pmic.min_uv, regulator.main_pmic.step_uv);
        }

        void VoltageTimeout(const Regulator &regulator, u32 volt_code) {
            const u32 volt_code_delta = GetVoltCodeDelta(regulator.main_pmic.volt_code, volt_code);

            /* Calculate the timeout. */
            const u32 delay_us = (regulator.main_pmic.step_uv * volt_code_delta) / regulator.ramp_div;

            SleepForRamp(delay_us);
        }

    }

    Result SetVoltageMax77620(u32 idx, u32 micro_volts) {
        Regulator &regulator = GetRegulator(idx);

        /* Check if the voltage is safe to apply */
        R_UNLESS(IsSafeVoltage(regulator, micro_volts), ResultInvalidArgument());

        /* Get the voltage code */
        const u32 volt_code = GetVoltCode(regulator, micro_volts);

        /* Set the voltage. */
        u8 volt_reg;
        R_TRY(I2cRead(*regulator.session, regulator.volt_reg, volt_reg));
        volt_reg = (volt_reg & ~regulator.voltage_mask) | (regulator.voltage_mask & volt_code);

        R_TRY(I2cWrite(*regulator.session, regulator.volt_reg, volt_reg));
        VoltageTimeout(regulator, volt_code);

        /* Update voltage. */
        regulator.main_pmic.volt_code = static_cast<u8>(volt_code);

        R_SUCCEED();
    }

    Result GetVoltageMax77620(u32 idx, u32 &micro_volts) {
        Regulator &regulator = GetRegulator(idx);

        u8 vout;
        R_TRY(I2cRead(*regulator.session, regulator.volt_reg, vout));
        u8 volt_code = vout & regulator.voltage_mask;

        micro_volts = GetVoltageFromCode(regulator, volt_code);

        R_SUCCEED();
    }

    u32 GetCachedVoltageMax77620(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        return GetVoltageFromCode(regulator, regulator.main_pmic.volt_code);
    }

    void GetVoltageRangeMax77620(u32 idx, u32 &default_uv, u32 &max_uv, u32 &step_uv) {
        Regulator &regulator = GetRegulator(idx);

        /* Why are they using default uv? TODO: Verify */
        default_uv = regulator.main_pmic.default_uv;
        max_uv     = regulator.main_pmic.max_uv;
        step_uv    = regulator.main_pmic.step_uv;
    }

    bool FinalizeMax77620(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        if (regulator.ref_count <= 0) {
            return false;
        }

        if (--regulator.ref_count == 0) {
            regulator.is_open = false;
        }

        return true;
    }

    Result EnableMax77620(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        if (regulator.fps_src != FpsSourceNone) {
            R_SUCCEED();
        }

        /* Only the first regulator can be forced on. */
        if (idx == 0 && regulator.forced_on) {
            R_SUCCEED();
        }

        const u8 enable_value = regulator.enable_value;
        R_TRY(WriteEnabledRegister(idx, enable_value));
        regulator.enabled_state = enable_value;

        const Result result = WaitForPowerGood(regulator);

        if (regulator.pmc_bit) {
            ClearPmcNoIoPowerBit(regulator);
        }

        return result;
    }

    Result IsEnabledMax77620(u32 idx, bool &enabled) {
        Regulator &regulator = GetRegulator(idx);

        /* Only the first regulator can be forced on. */
        if (idx == 0 && regulator.forced_on) {
            enabled = true;
            R_SUCCEED();
        }

        u32 enabled_register;
        R_TRY(ReadEnabledRegister(idx, std::addressof(enabled_register)));

        enabled = enabled_register != 0;
        R_SUCCEED();
    }

    Result DisableMax77620(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        if (regulator.fps_src != FpsSourceNone) {
            R_SUCCEED();
        }

        /* Only the first regulator can be forced on. */
        if (idx == 0 && regulator.forced_on) {
            R_SUCCEED();
        }

        if (regulator.pmc_bit) {
            SetPmcNoIoPowerBit(regulator);
        }

        /* Clear the enable field. */
        R_TRY(WriteEnabledRegister(idx, 0));
        regulator.enabled_state = 0;

        SleepForRamp(regulator.disable_delay_us);

        R_SUCCEED();
    }

}
