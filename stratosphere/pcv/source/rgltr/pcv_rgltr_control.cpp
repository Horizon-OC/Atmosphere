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
#include "../pcv_device_handle.hpp"
#include "pcv_rgltr_power_domain.hpp"
#include "pcv_rgltr_control.hpp"
#include "pcv_rgltr_device_handle.hpp"
#include "pcv_rgltr.hpp"
#include "pcv_rgltr_max77620_init.hpp"
#include "pcv_rgltr_max77620.hpp"
#include "pcv_rgltr_max77621.hpp"
#include "pcv_rgltr_max77812.hpp"

namespace ams::pcv::rgltr {

    namespace {

        Result SetVoltageImpl(u32 idx, u32 micro_volts) {
            Regulator &regulator = GetRegulator(idx);
            switch (regulator.type) {
                case PmicType_Main:        R_RETURN(SetVoltageMax77620(idx, micro_volts));
                case PmicType_Erista_Dvfs: R_RETURN(SetVoltageMax77621(idx, micro_volts));
                case PmicType_Mariko_Dvfs: R_RETURN(SetVoltageMax77812Reg(idx, micro_volts, regulator.use_vout_d ? regulator.vout_d_reg : regulator.vout_reg));
                default:                   AMS_ABORT();
            }
        }

        Result EnablePowerDomainImpl(u32 idx) {
            Regulator &regulator = GetRegulator(idx);
            switch (regulator.type) {
                case PmicType_Main:        R_RETURN(EnableMax77620(idx));
                case PmicType_Erista_Dvfs: R_RETURN(EnableMax77621(idx));
                case PmicType_Mariko_Dvfs: R_RETURN(EnableMax77812(idx));
                default:                   AMS_ABORT();
            }
        }

    }

    Result SetVoltage(PowerDomain *domain, u32 micro_volts) {
        R_UNLESS(domain != nullptr, ResultInvalidArgument());

        /* Initialize handle */
        DeviceHandle handle;
        if (!InitializeHandleByName(std::addressof(handle), domain->GetName())) {
            R_SUCCEED();
        }

        /* Try to set the voltage if it's open */
        const Result result = SetVoltageImpl(handle.device_index, micro_volts);
        FinalizeHandle(std::addressof(handle));

        R_RETURN(result);
    }

    Result EnablePowerDomain(PowerDomain *domain) {
        R_UNLESS(domain != nullptr, ResultInvalidArgument());

        /* Initialize handle */
        DeviceHandle handle;
        if (!InitializeHandleByName(std::addressof(handle), domain->GetName())) {
            R_SUCCEED();
        }

        /* Enable it. */
        const Result result = EnablePowerDomainImpl(handle.device_index);

        /* Finalize them. */
        FinalizeHandle(std::addressof(handle));

        R_RETURN(result);
    }

}
