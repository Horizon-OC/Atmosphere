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
#include "pcv_rgltr_volt_max77812.hpp"
#include "pcv_rgltr_max77812_init.hpp"
#include "../pcv_i2c.hpp"

namespace ams::pcv::rgltr {

    namespace {

        bool IsSafeVoltage(const Regulator &regulator, u32 voltage) {
            return regulator.dvfs_pmic.min_uv <= voltage && voltage <= regulator.dvfs_pmic.max_uv;
        }

        u8 GetVoltCode(const Regulator &regulator, u32 voltage) {
            const u32 step_uv = regulator.dvfs_pmic.step_uv;

            return static_cast<u8>((voltage - regulator.dvfs_pmic.min_uv + step_uv - 1) / step_uv);
        }

        constexpr u32 RampMarginPercent = 6;

        constexpr u32 AddRampMargin(u32 ramp_us) {
            return ramp_us + (ramp_us * RampMarginPercent) / 100;
        }

        void VoltageTimeout(const Regulator &regulator, u8 volt_code, u8 reg) {
            const Slew &slew = GetSlew();

            const u32 old_volt_code   = regulator.dvfs_pmic.volt_code;
            const u32 volt_code_delta = static_cast<u32>(std::abs(static_cast<s32>(old_volt_code) - static_cast<s32>(volt_code)));

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
            if (delay_us >= 1) {
                svc::SleepThread(static_cast<s64>(1000) * delay_us);
            }
        }

    }

    Result SetVoltageMax77812Reg(u32 idx, u32 micro_volts, u8 reg) {
        Regulator &regulator = GetRegulator(idx);

        /* Check that the voltage is safe to apply. */
        if (!IsSafeVoltage(regulator, micro_volts)) {
            return -1; /* Todo figure out a better way of handling this. */
        }

        const u8 volt_code = GetVoltCode(regulator, micro_volts);

        /* Write the voltage. */
        R_TRY(I2cWrite(*regulator.session, reg, volt_code));

        /* Wait for the rail to settle. */
        VoltageTimeout(regulator, volt_code, reg);

        /* Update the voltage. */
        regulator.dvfs_pmic.volt_code = volt_code;

        return ResultSuccess();
    }

}
