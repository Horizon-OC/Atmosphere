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

#include "pcv_rgltr.hpp"
#include "pcv_rgltr_max77812.hpp"
#include "pcv_rgltr_common_volt.hpp"
#include "../pcv_i2c.hpp"

namespace ams::pcv::rgltr {

    namespace {

        constinit Slew g_slew = {};

        bool IsSafeVoltage(const Regulator &regulator, u32 voltage) {
            return IsVoltageInRange(voltage, regulator.dvfs_pmic.min_uv, regulator.dvfs_pmic.max_uv);
        }

        u8 GetVoltCode(const Regulator &regulator, u32 voltage) {
            return static_cast<u8>(GetVoltCodeImpl(voltage, regulator.dvfs_pmic.min_uv, regulator.dvfs_pmic.step_uv));
        }

        u32 GetVoltageFromCode(const Regulator &regulator, u8 volt_code) {
            return GetVoltageFromCodeImpl(volt_code, regulator.dvfs_pmic.min_uv, regulator.dvfs_pmic.step_uv);
        }

        constexpr u32 RampMarginPercent = 6;

        constexpr u32 AddRampMargin(u32 ramp_us) {
            return ramp_us + (ramp_us * RampMarginPercent) / 100;
        }

        void VoltageTimeout(const Regulator &regulator, u8 volt_code, u8 reg) {
            const Slew &slew = GetSlew();

            const u32 old_volt_code   = regulator.dvfs_pmic.volt_code;
            const u32 volt_code_delta = GetVoltCodeDelta(old_volt_code, volt_code);

            /* Rising uses the ramp-up, falling uses ramp-down. */
            const u32 ramp_uv_per_us = (old_volt_code <= volt_code) ? slew.ramp_up_per_us : slew.ramp_down_per_us;

            /* Calculate the ramp delay. */
            u32 ramp_us = 0;
            if (ramp_uv_per_us != 0) {
                ramp_us = (regulator.dvfs_pmic.step_uv * volt_code_delta) / ramp_uv_per_us;
            }

            /* Read back the register, because why not. */
            {
                u8 out = 0;
                R_DISCARD(I2cRead(*regulator.session, reg, out));
            }

            /* Add a margin. */
            const u32 delay_us = AddRampMargin(ramp_us);

            /* Timeout. */
            SleepForRamp(delay_us);
        }

    }

    Result SetVoltageMax77812Reg(u32 idx, u32 micro_volts, u8 reg) {
        Regulator &regulator = GetRegulator(idx);

        /* Check that the voltage is safe to apply. */
        R_UNLESS(IsSafeVoltage(regulator, micro_volts), ResultInvalidArgument());

        const u8 volt_code = GetVoltCode(regulator, micro_volts);

        /* Write the voltage. */
        R_TRY(I2cWrite(*regulator.session, reg, volt_code));

        /* Wait for the rail to settle. */
        VoltageTimeout(regulator, volt_code, reg);

        /* Update the voltage. */
        regulator.dvfs_pmic.volt_code = volt_code;

        R_SUCCEED();
    }

    Result GetVoltageMax77812(u32 idx, u32 &out_micro_volts) {
        Regulator &regulator = GetRegulator(idx);

        u8 vout_reg;
        if (regulator.use_vout_d) {
            vout_reg = regulator.vout_d_reg;
        } else {
            vout_reg = regulator.vout_reg;
        }

        /* Do the completely sane action of reading the register and then getting amnesia. */
        u8 vout_value;
        R_DISCARD(I2cRead(*regulator.session, vout_reg, vout_value));

        /* Ok now we're awake, what were we doing? Right reading vout registers. */
        R_TRY(I2cRead(*regulator.session, vout_reg, vout_value));

        /* what. */
        {
            u8 dummy;
            R_DISCARD(I2cRead(*regulator.session, vout_reg, dummy));
        }

        regulator.dvfs_pmic.volt_code = vout_value;

        out_micro_volts = GetVoltageFromCode(regulator, vout_value);

        R_SUCCEED();
    }

    /* Todo move this in some common file. */
    u32 GetCachedVoltageDvfsPmic(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        return GetVoltageFromCode(regulator, regulator.dvfs_pmic.volt_code);
    }

    Result EnableMax77812(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        /* read enable register */
        {
            u8 enabled;
            R_DISCARD(I2cRead(*regulator.session, Max77812EnCtrlReg, enabled));
        }

        /* Already enabled. */
        if (regulator.enable_count++ != 0) {
            R_SUCCEED();
        }

        /* Reread */
        u8 enable_ctrl;
        R_TRY(I2cRead(*regulator.session, Max77812EnCtrlReg, enable_ctrl));

        /* Enable. */
        enable_ctrl |= regulator.master_en_mask;
        R_TRY(I2cWrite(*regulator.session, Max77812EnCtrlReg, enable_ctrl));

        const Slew &slew = GetSlew();

        if (slew.start_per_us) {
            /* GEt the voltage. */
            u32 voltage;
            R_TRY(GetVoltageMax77812(idx, voltage));

            constexpr u32 RampFixedOverheadUs = 78;

            const u32 ramp_us  = voltage / slew.start_per_us;
            const u32 delay_us = AddRampMargin(ramp_us) + RampFixedOverheadUs;

            /* Timeout. */
            SleepForRamp(delay_us);
        }

        /* read enable register again? I trust you nintendo :) */
        {
            u8 enabled;
            R_DISCARD(I2cRead(*regulator.session, Max77812EnCtrlReg, enabled));
        }

        R_SUCCEED();
    }

    Result IsEnabledMax77812(u32 idx, bool &enabled) {
        Regulator &regulator = GetRegulator(idx);

        {
            /* read twice once again */
            u8 discarded;
            R_TRY(I2cRead(*regulator.session, Max77812EnCtrlReg, discarded));
        }

        u8 ctrl_reg;
        R_TRY(I2cRead(*regulator.session, Max77812EnCtrlReg, ctrl_reg));

        enabled = ctrl_reg & regulator.master_en_mask;

        R_SUCCEED();
    }

    Result DisableMax77812(u32 idx) {
        Regulator &regulator = GetRegulator(idx);
        /* Is this even needed */
        {
            u8 en_ctrl;
            R_DISCARD(I2cRead(*regulator.session, Max77812EnCtrlReg, en_ctrl));
        }

        if (!regulator.enable_count) {
            /* Already disabled */
            R_SUCCEED();
        }

        if (--regulator.enable_count) {
            /* Still enabled, nothing left to do. */
            R_SUCCEED();
        }

        const Slew &slew = GetSlew();

        /* Fully disable it */
        u8 en_ctrl;
        R_TRY(I2cRead(*regulator.session, Max77812EnCtrlReg, en_ctrl));
        en_ctrl &= ~regulator.master_en_mask;
        R_TRY(I2cWrite(*regulator.session, Max77812EnCtrlReg, en_ctrl));

        /* Sleep */
        u64 delay_us = AddRampMargin(slew.shdn_per_us);
        SleepForRamp(delay_us);

        /* readback because why not */
        {
            u8 en_ctrl;
            R_DISCARD(I2cRead(*regulator.session, Max77812EnCtrlReg, en_ctrl));
        }

        R_SUCCEED();
    }

    bool FinalizeMax77812(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        if (regulator.ref_count <= 0) {
            return false;
        }

        if (--regulator.ref_count == 0) {
            regulator.is_open = false;
        }

        return true;
    }

    Slew &GetSlew() {
        return g_slew;
    }

}
