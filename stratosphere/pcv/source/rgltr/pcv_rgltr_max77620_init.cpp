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
#include "pcv_rgltr_volt_max77620.hpp"
#include "../pcv_i2c.hpp"

namespace ams::pcv::rgltr {

    namespace {

        constinit Max77620InitReg g_init_regs[] = {
            { .reg = 0x43, .time_period = 7, .en_src = 0, .sw_enable = 0, },
            { .reg = 0x44, .time_period = 7, .en_src = 1, .sw_enable = 0, },
            { .reg = 0x45, .time_period = 7, .en_src = 0, .sw_enable = 0, },
        };

        constinit u32 g_sd_rate_table[] = {
            13750, 27500, 55000, 100000,
        };

        constinit u32 g_ldo_rate_table[] = {
            100000, 5000,
        };

        /* FPS (flexible power sequencer) sources. */
        constexpr u32 FpsSourceCount = 4;
        constexpr u32 FpsSourceNone  = 3;
        constexpr u32 FpsSourceNoOp  = 5;

        constexpr u32 FpsPeriodCount = 8;

        constexpr u8 FpsSourceShift   = 6;
        constexpr u8 FpsSourceMask    = 0x3 << FpsSourceShift;
        constexpr u8 FpsPuPeriodShift = 3;
        constexpr u8 FpsPuPeriodMask  = 0x7 << FpsPuPeriodShift;
        constexpr u8 FpsPdPeriodShift = 0;
        constexpr u8 FpsPdPeriodMask  = 0x7 << FpsPdPeriodShift;

        constexpr u8 SdRampRateShift    = 6;
        constexpr u8 SdRampRateMask     = 0x3 << SdRampRateShift;
        constexpr u8 SdRampBitMask      = 0x1;
        constexpr u8 LdoRampSelectShift = 0;
        constexpr u8 LdoRampSelectMask  = 0x1 << LdoRampSelectShift;

        i2c::I2cSession g_session;
        u8 g_cid4;

        Result SetCid4() {
            /* Read the chip id. */
            /* NOTE: Nintendo reads this twice for no reason? lol */
            u8 chip_id;
            R_TRY(I2cRead(g_session, Max77620PmicCid4Reg, chip_id));

            g_cid4 = chip_id;

            return ResultSuccess();
        }

        void SetI2cSessions() {
            for (u32 i = 0; i < RegulatorCount; ++i) {
                GetRegulator(i).session = std::addressof(g_session);
            }
        }

        bool IsMax77620(const char *rgltr_name) {
            constexpr const char Name[] = "max77620";

            return std::strncmp(rgltr_name, Name, sizeof(Name) - 1) == 0;
        }

        void InitializeFpsRegs() {
            for (size_t i = 0; i < util::size(g_init_regs); ++i) {
                /* Ensure this is max77620. */
                if (!IsMax77620(GetRegulator(i).name)) {
                    continue;
                }

                const auto &init_reg = g_init_regs[i];

                u8 fps_value;
                R_DISCARD(I2cRead(g_session, init_reg.reg, fps_value));

                fps_value = (init_reg.time_period << 3) | (init_reg.en_src << 1) | init_reg.sw_enable;
                R_DISCARD(I2cWrite(g_session, init_reg.reg, fps_value));

                /* Read it again? sure nintendo. */
                R_DISCARD(I2cRead(g_session, init_reg.reg, fps_value));
            }
        }

        u8 GetEnableRegister(Regulator &reg) {
            return reg.is_ldo ? reg.volt_reg_byte : reg.config_reg;
        }

        Result ReadEnabledRegister(u32 idx, u32 *enabled) {
            Regulator &regulator = GetRegulator(idx);
            u8 enable_register = GetEnableRegister(regulator);

            u8 out;
            R_TRY(I2cRead(*regulator.session, enable_register, out));

            *enabled = static_cast<u8>(out & regulator.enable_mask) >> regulator.enable_shift;

            return ResultSuccess();
        }

        constexpr u32 EnabledRegulator = 3;
        constexpr u32 InvalidRegulator = 4;

        bool GetEnabled(u32 idx, bool &enabled) {
            const Regulator &regulator = GetRegulator(idx);

            /* anything but fps_src 3 is always automatically enabled. */
            if (regulator.fps_src != FpsSourceNone) {
                enabled = true;
                return true;
            }

            /* Only the first regulator can be forced on. */
            if (idx == 0 && regulator.forced_on) {
                enabled = true;
                return true;
            }

            /* For other sources, read the register. */
            u32 enabled_register;
            if (R_FAILED(ReadEnabledRegister(idx, std::addressof(enabled_register)))) {
                return false;
            }

            /* Check if it's valid */
            if (enabled_register == InvalidRegulator) {
                return false;
            }

            /* It's enabled if the field is non-zero. */
            enabled = enabled_register != 0;
            return true;
        }

        Result WriteEnabledRegister(u32 idx, u8 enabled) {
            Regulator &regulator = GetRegulator(idx);
            u8 enable_register = GetEnableRegister(regulator);

            u8 value;
            R_TRY(I2cRead(*regulator.session, enable_register, value));

            value = (value & ~regulator.enable_mask) | (regulator.enable_mask & (enabled << regulator.enable_shift));

            R_RETURN(I2cWrite(*regulator.session, enable_register, value));
        }

        void DropRegulatorReference(u32 idx) {
            s32 new_count = GetRegulator(idx).ref_count - 1;

            if (new_count >= 0) {
                if (new_count == 0 && GetRegulator(idx).is_open) {
                    GetRegulator(idx).is_open = false;
                }

                GetRegulator(idx).ref_count = new_count;
            }
        }

        bool SetFpsSourceAndPeriods(u32 idx, u32 fps_src, u32 pu_period, u32 pd_period) {
            Regulator &regulator = GetRegulator(idx);

            /* Only the real sources can be set. */
            if (fps_src >= FpsSourceCount) {
                return fps_src == FpsSourceNoOp;
            }

            /* Read fps reg. */
            u8 fps_value;
            if (R_FAILED(I2cRead(*regulator.session, regulator.fps_reg, fps_value))) {
                return false;
            }

            u8 field_mask = FpsSourceMask;
            u8 new_bits   = fps_src << FpsSourceShift;

            if (pu_period < FpsPeriodCount) {
                field_mask |= FpsPuPeriodMask;
                new_bits   |= pu_period << FpsPuPeriodShift;
            }

            if (pd_period < FpsPeriodCount) {
                field_mask |= FpsPdPeriodMask;
                new_bits   |= pd_period << FpsPdPeriodShift;
            }

            fps_value = (fps_value & ~field_mask) | new_bits;

            if (R_FAILED(I2cWrite(*regulator.session, regulator.fps_reg, fps_value))) {
                return false;
            }

            regulator.fps_src = fps_src;

            return true;
        }

        bool InitRampRate(u32 idx) {
            Regulator &regulator = GetRegulator(idx);

            /* Read the config. */
            u8 cfg = 0;
            if (R_FAILED(I2cRead(*regulator.session, regulator.config_reg, cfg))) {
                return false;
            }

            /* Configure the rate. */
            u32 rate;
            if (regulator.is_ldo) {
                rate = g_ldo_rate_table[(cfg & LdoRampSelectMask) >> LdoRampSelectShift];
            } else {
                rate = g_sd_rate_table[(cfg & SdRampRateMask) >> SdRampRateShift];

                cfg = (cfg & ~SdRampBitMask) | (regulator.ramp_bit ? SdRampBitMask : 0);

                if (R_FAILED(I2cWrite(*regulator.session, regulator.config_reg, cfg))) {
                    return false;
                }
            }

            regulator.ramp_rate_uv_per_us = rate;

            return true;
        }

        Result ReadCurrentVoltageUv(u32 idx, u32 &out_voltage) {
            Regulator &regulator = GetRegulator(idx);

            u8 out_volt;
            R_TRY(I2cRead(*regulator.session, regulator.volt_reg_byte, out_volt));

            /* Get the voltage code. */
            u32 volt_code = out_volt & regulator.voltage_mask;
            regulator.main_pmic.volt_code = volt_code;

            out_voltage = regulator.main_pmic.min_uv + regulator.main_pmic.step_uv * volt_code;

            return ResultSuccess();
        }

        void SyncPmcBit(u32 idx, bool enabled) {
            const Regulator &regulator = GetRegulator(idx);

            /* Discard the result because ReadWriteRegister is a meme. */
            constexpr u32 AbpdevPmcNoIoPower = 0x44;
            u32 no_io_power_out = 0;
            R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_power_out), regulator.pmc_mmio + AbpdevPmcNoIoPower, 0, 0));

            /* Check if there's a bit to set in the first place. */
            if (!regulator.pmc_bit) {
                return;
            }

            /* This should only be the case on regulators with fps_src 3. */
            AMS_ABORT_UNLESS(regulator.fps_src == FpsSourceNone);

            u32 set;
            if (enabled) {
                if (!(regulator.pmc_bit & no_io_power_out)) {
                    return;
                }

                set = 0;
            } else {
                if (regulator.pmc_bit & no_io_power_out) {
                    return;
                }

                set = regulator.pmc_bit;
            }

            /* Write the register. */
            no_io_power_out &= ~regulator.pmc_bit;
            R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_power_out), regulator.pmc_mmio + AbpdevPmcNoIoPower, ~0, no_io_power_out | set));

            /* Nintendo rereads the value twice for whatever reason? sure */
            R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_power_out), regulator.pmc_mmio + AbpdevPmcNoIoPower, 0, 0));
            R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_power_out), regulator.pmc_mmio + AbpdevPmcNoIoPower, 0, 0));
        }

        void ClampCurrentVoltage(u32 idx, u32 current_volt_uv, bool enabled) {
            const Regulator &regulator = GetRegulator(idx);

            const u32 default_uv = regulator.main_pmic.default_uv;
            const u32 max_uv     = regulator.main_pmic.max_uv;

            /* Nothing to do if the voltage is in range. */
            if (current_volt_uv >= default_uv && current_volt_uv <= max_uv) {
                return;
            }

            /* NOTE: Nintendo only fixes voltages that are too low (or if voltage == max). */
            const bool needs_update = (current_volt_uv < default_uv) || (default_uv == max_uv);

            if (enabled) {
                /* Enabled regulators are only touched if they have a pmc mask. */
                if (regulator.pmc_mask && needs_update) {
                    R_DISCARD(SetVoltageMax77620(idx, default_uv));
                }
            } else if (needs_update) {
                R_DISCARD(SetVoltageMax77620(idx, default_uv));
            }
        }

        void InitializeRegulator(u32 idx) {
            Regulator &regulator = GetRegulator(idx);
            /* Ensure this is max77620. */
            if (!IsMax77620(regulator.name)) {
                return;
            }

            constexpr u32 PmcBase = 0x7000E400;

            /* Ensure the regulator not in an invalid state. */
            u32 enabled_register = 0;
            if (R_FAILED(ReadEnabledRegister(idx, std::addressof(enabled_register))) || enabled_register == InvalidRegulator) {
                DropRegulatorReference(idx);
                return;
            }

            /* Enable the regulator. */
            regulator.enable_value  = EnabledRegulator;
            regulator.enabled_state = enabled_register;
            regulator.pmc_mmio      = PmcBase;

            /* Setup the power mode and fps config. */
            bool fps_ok;
            if (regulator.fps_src != FpsSourceNone) {
                if (enabled_register != EnabledRegulator) {
                    /* Enable it if it isn't enabled yet. */
                    if (R_FAILED(WriteEnabledRegister(idx, static_cast<u8>(EnabledRegulator)))) {
                        DropRegulatorReference(idx);
                        return;
                    }

                    regulator.enabled_state = EnabledRegulator;
                }
                fps_ok = SetFpsSourceAndPeriods(idx, regulator.fps_src, regulator.fps_pu_period, regulator.fps_pd_period);
            } else if (regulator.always_on) {
                if (R_FAILED(WriteEnabledRegister(idx, regulator.enable_value))) {
                    DropRegulatorReference(idx);
                    return;
                }
                regulator.enabled_state = regulator.enable_value;
                fps_ok = SetFpsSourceAndPeriods(idx, regulator.fps_src, regulator.fps_pu_period, regulator.fps_pd_period);
            } else {
                fps_ok = SetFpsSourceAndPeriods(idx, FpsSourceNone, regulator.fps_pu_period, regulator.fps_pd_period);
            }

            if (!fps_ok) {
                DropRegulatorReference(idx);
                return;
            }

            /* Configure ramp rate. */
            if (!InitRampRate(idx)) {
                DropRegulatorReference(idx);
                return;
            }

            /* Read the current voltage in uv. */
            u32 current_volt_uv = 0;
            if (R_FAILED(ReadCurrentVoltageUv(idx, current_volt_uv))) {
                DropRegulatorReference(idx);
                return;
            }

            /* Is it enabled? */
            /* NOTE: Nintendo ignores the result of this. */
            bool enabled = false;
            GetEnabled(idx, enabled);

            /* Sync pmc registers. */
            SyncPmcBit(idx, enabled);

            /* Clamp voltage is the current voltage is out of range. */
            ClampCurrentVoltage(idx, current_volt_uv, enabled);

            regulator.is_initialized = true;
        }

        void InitializeOnOffConfig() {
            constexpr u8 OnOffIrqUnmaskBits = Max77620PmicOnOffIrqPowerButtonMask | Max77620PmicOnOffIrqAcOkFallMask | Max77620PmicOnOffIrqAcOkRiseMask;

            /* Read the on off irq mask. */
            u8 on_off_irq_mask;
            if (R_SUCCEEDED(I2cRead(g_session, Max77620PmicOnOffIrqMReg, on_off_irq_mask))) {
                /* Clear it */
                on_off_irq_mask = 0xFF;

                /* NOTE: Nintendo discards */
                R_DISCARD(I2cWrite(g_session, Max77620PmicOnOffIrqMReg, on_off_irq_mask));
            }

            /* Reread it */
            if (R_SUCCEEDED(I2cRead(g_session, Max77620PmicOnOffIrqMReg, on_off_irq_mask))) {
                on_off_irq_mask &= ~OnOffIrqUnmaskBits;

                R_DISCARD(I2cWrite(g_session, Max77620PmicOnOffIrqMReg, on_off_irq_mask));
            }

            /* Write the config. */
            constexpr u8 ManualResetTime = 7;
            static_assert(ManualResetTime <= 7);

            u8 on_off_cfg;
            if (R_SUCCEEDED(I2cRead(g_session, Max77620PmicOnOffCnfg1Reg, on_off_cfg))) {
                on_off_cfg &= ~Max77620PmicOnOffCnfg1MrtMask;
                on_off_cfg |= (ManualResetTime << Max77620PmicOnOffCnfg1MrtShift);
                R_DISCARD(I2cWrite(g_session, Max77620PmicOnOffCnfg1Reg, on_off_cfg));
            }

            /* Write low battery config. */
            u8 low_battery_config = Max77620PmicCnfgGlbl1LbDacEnMask | Max77620PmicCnfgGlbl1LbHyst200 | Max77620PmicCnfgGlbl1LbDac2800;
            if (spl::GetHardwareType() == spl::HardwareType::Calcio) {
                low_battery_config |= Max77620PmicCnfgGlbl1MppLdMask;
            }
            R_DISCARD(I2cWrite(g_session, Max77620PmicCnfgGlbl1Reg, low_battery_config));

            /* Set on off config 2. */
            u8 on_off_cfg_2;
            if (R_SUCCEEDED(I2cRead(g_session, Max77620PmicOnOffCnfg2Reg, on_off_cfg_2))) {
                on_off_cfg_2 &= ~(Max77620PmicOnOffCnfg2WkAlarm1Mask | Max77620PmicOnOffCnfg2WkAlarm2Mask);

                R_DISCARD(I2cWrite(g_session, Max77620PmicOnOffCnfg2Reg, on_off_cfg_2));
            }
        }
    }

    void InitializeMax77620() {
        /* Open the session. */
        R_ABORT_UNLESS(i2c::OpenSession(std::addressof(g_session), i2c::DeviceCode_Max77620Pmic));

        /* Set the chip id. */
        R_ABORT_UNLESS(SetCid4());

        /* Set the regulator table. */
        SetRegulatorTable(g_cid4);

        /* Set the i2c sessions. */
        SetI2cSessions();

        /* Initialize fps regs. */
        InitializeFpsRegs();

        /* Fully initialize each regulator. */
        for (u32 i = 0; i < RegulatorCount; ++i) {
            InitializeRegulator(i);
        }

        /* Configure step down regulators config. */
        u8 step_down_cfg = 4;
        if (spl::GetHardwareType() == spl::HardwareType::Calcio) {
            step_down_cfg = 0;
        }

        R_ABORT_UNLESS(I2cWrite(g_session, Max77620PmicSdCfg2Reg, step_down_cfg));

        /* Initialize on off config. */
        InitializeOnOffConfig();
    }

}
