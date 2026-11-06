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
#include "../pcv_i2c.hpp"

namespace ams::pcv::rgltr {

    namespace {

        bool IsSafeVoltage(const Regulator &regulator, u32 voltage) {
            /* NOTE: Nintendo uses default_uv as the lower bound. Might be a bug? */
            if (voltage < regulator.main_pmic.default_uv || voltage > regulator.main_pmic.max_uv) {
                return false;
            }

            return true;
        }

        u32 GetVoltCode(const Regulator &regulator, u32 voltage) {
            const u32 step_uv = regulator.main_pmic.step_uv;

            return (voltage - regulator.main_pmic.min_uv + step_uv - 1) / step_uv;
        }

        void VoltageTimeout(const Regulator &regulator, u32 volt_code) {
            const u32 old_volt_code   = regulator.main_pmic.volt_code;
            const u32 volt_code_delta = static_cast<u32>(std::abs(static_cast<s32>(old_volt_code) - static_cast<s32>(volt_code)));

            /* Calculate the timeout. */
            const u32 delay_us = (regulator.main_pmic.step_uv * volt_code_delta) / regulator.ramp_div;

            if (delay_us >= 1) {
                svc::SleepThread(static_cast<s64>(1000) * delay_us);
            }
        }

    }

    Result SetVoltageMax77620(u32 idx, u32 micro_volts) {
        Regulator &regulator = GetRegulator(idx);

        /* Check if the voltage is safe to apply */
        if (!IsSafeVoltage(regulator, micro_volts)) {
            return -1;
        }

        /* Get the voltage code */
        const u32 volt_code = GetVoltCode(regulator, micro_volts);

        /* Set the voltage. */
        u8 volt_reg;
        R_TRY(I2cRead(*regulator.session, regulator.volt_reg_byte, volt_reg));
        volt_reg = (volt_reg & ~regulator.voltage_mask) | (regulator.voltage_mask & volt_code);

        R_TRY(I2cWrite(*regulator.session, regulator.volt_reg_byte, volt_reg));
        VoltageTimeout(regulator, volt_code);

        /* Update voltage. */
        regulator.main_pmic.volt_code = static_cast<u8>(volt_code);

        return ResultSuccess();
    }

}
