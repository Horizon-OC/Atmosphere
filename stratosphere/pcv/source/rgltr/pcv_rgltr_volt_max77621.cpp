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
            if (voltage < regulator.dvfs_pmic.min_uv || voltage > regulator.dvfs_pmic.max_uv) {
                return false;
            }

            return true;
        }

        u8 GetVoltCode(const Regulator &regulator, u32 voltage) {
            const u32 step_uv = regulator.dvfs_pmic.step_uv;

            return static_cast<u8>(util::DivideUp(voltage - regulator.dvfs_pmic.min_uv, step_uv) + 2);
        }

        void VoltageTimeout(const Regulator &regulator, u32 volt_code) {
            const u32 old_volt_code   = regulator.dvfs_pmic.volt_code;
            const u32 volt_code_delta = static_cast<u32>(std::abs(static_cast<s32>(old_volt_code) - static_cast<s32>(volt_code)));

            /* Calculate the timeout. */
            const u32 delay_us = (regulator.dvfs_pmic.step_uv * volt_code_delta) / regulator.ramp_rate_uv_per_us;

            if (delay_us >= 1) {
                svc::SleepThread(static_cast<s64>(1000) * delay_us);
            }
        }

    }

    Result SetVoltageMax77621(u32 idx, u32 micro_volts) {
        Regulator &regulator = GetRegulator(idx);

        /* Check that the voltage is safe to apply. */
        if (!IsSafeVoltage(regulator, micro_volts)) {
            return -1; /* Todo figure out a better way of handling this. */
        }

        u8 volt_code = GetVoltCode(regulator, micro_volts);
        u8 vout      = volt_code | Max77621DvcDvsEnableMask;
        /* Write the voltage. */
        R_TRY(I2cWrite(*regulator.session, Max77621VoutDvsReg, vout));

        /* Timeout */
        VoltageTimeout(regulator, volt_code);

        regulator.dvfs_pmic.volt_code = volt_code;

        return ResultSuccess();
    }
}
