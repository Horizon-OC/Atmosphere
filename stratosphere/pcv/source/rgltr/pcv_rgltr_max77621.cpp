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
#include "pcv_rgltr_max77621.hpp"
#include "pcv_rgltr_common_volt.hpp"
#include "../pcv_i2c.hpp"

namespace ams::pcv::rgltr {

    namespace {

        bool IsSafeVoltage(const Regulator &regulator, u32 voltage) {
            return IsVoltageInRange(voltage, regulator.dvfs_pmic.min_uv, regulator.dvfs_pmic.max_uv);
        }

        u8 GetVoltCode(const Regulator &regulator, u32 voltage) {
            return static_cast<u8>(GetVoltCodeImpl(voltage, regulator.dvfs_pmic.min_uv, regulator.dvfs_pmic.step_uv) + 2);
        }

        u32 GetVoltageFromCode(const Regulator &regulator, u8 volt_code) {
            return GetVoltageFromCodeImpl(volt_code, regulator.dvfs_pmic.min_uv, regulator.dvfs_pmic.step_uv);
        }

        void VoltageTimeout(const Regulator &regulator, u32 volt_code) {
            const u32 volt_code_delta = GetVoltCodeDelta(regulator.dvfs_pmic.volt_code, volt_code);

            /* Calculate the timeout. */
            const u32 delay_us = (regulator.dvfs_pmic.step_uv * volt_code_delta) / regulator.ramp_rate_uv_per_us;

            SleepForRamp(delay_us);
        }

    }

    Result SetVoltageMax77621(u32 idx, u32 micro_volts) {
        Regulator &regulator = GetRegulator(idx);

        /* Check that the voltage is safe to apply. */
        R_UNLESS(IsSafeVoltage(regulator, micro_volts), ResultInvalidArgument());

        u8 volt_code = GetVoltCode(regulator, micro_volts);
        u8 vout      = volt_code | Max77621DvcDvsEnableMask;
        /* Write the voltage. */
        R_TRY(I2cWrite(*regulator.session, Max77621VoutDvsReg, vout));

        /* Timeout */
        VoltageTimeout(regulator, volt_code);

        regulator.dvfs_pmic.volt_code = volt_code;

        R_SUCCEED();
    }

    Result GetVoltageMax77621(u32 idx, u32 &micro_volts) {
        Regulator &regulator = GetRegulator(idx);

        u8 vout;
        R_TRY(I2cRead(*regulator.session, Max77621VoutDvsReg, vout));
        u8 volt_code = vout & Max77621DvcDvsVoltMask;

        micro_volts = GetVoltageFromCode(regulator, volt_code);

        R_SUCCEED();
    }

    Result EnableMax77621(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        /* Only the first reference actually enables the regulator. */
        if (regulator.enable_count++ != 0) {
            R_SUCCEED();
        }

        /* Enable. */
        u8 vout;
        R_TRY(I2cRead(*regulator.session, Max77621VoutReg, vout));
        vout |= Max77621DvcDvsEnableBit;

        R_TRY(I2cWrite(*regulator.session, Max77621VoutReg, vout));

        /* Wait for it to be enabled. */
        if (regulator.enable_delay_us) {
            svc::SleepThread(static_cast<s64>(1000) * regulator.enable_delay_us);
        }

        R_SUCCEED();
    }

    Result IsEnabledMax77621(u32 idx, bool &enabled) {
        Regulator &regulator = GetRegulator(idx);

        /* Read vout. */
        u8 vout;
        R_TRY(I2cRead(*regulator.session, Max77621VoutReg, vout));
        enabled = vout & Max77621DvcDvsEnableBit && regulator.enable_count != 0;

        R_SUCCEED();
    }

    Result DisableMax77621(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        if (!regulator.enable_count) {
            /* Already disabled */
            R_SUCCEED();
        }

        if (--regulator.enable_count) {
            /* Still enabled, nothing left to do. */
            R_SUCCEED();
        }

        /* We need to disable it. */
        /* Read vout. */
        u8 vout;
        R_TRY(I2cRead(*regulator.session, Max77621VoutReg, vout));

        /* Disable it. */
        vout &= Max77621DvcDvsVoltMask;
        R_TRY(I2cWrite(*regulator.session, Max77621VoutReg, vout));

        SleepForRamp(regulator.disable_delay_us);

        R_SUCCEED();
    }

    bool FinalizeMax77621(u32 idx) {
        Regulator &regulator = GetRegulator(idx);

        if (regulator.ref_count < 1) {
            return false;
        }

        if (regulator.ref_count == 1) {
            i2c::CloseSession(*regulator.session);
            regulator.is_open = false;
        }

        --regulator.ref_count;
        return true;
    }

}
