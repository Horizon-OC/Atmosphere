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
#include "pcv_rgltr_common_volt.hpp"
#include "../pcv_i2c.hpp"

namespace ams::pcv::rgltr {

    namespace {

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

}
