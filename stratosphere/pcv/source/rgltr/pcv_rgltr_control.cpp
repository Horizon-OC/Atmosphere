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
#include "pcv_rgltr_max77620.hpp"
#include "pcv_rgltr_max77621.hpp"
#include "pcv_rgltr_max77812.hpp"
#include "pcv_rgltr_common_volt.hpp"

namespace ams::pcv::rgltr {

    namespace {

        /* NOTE: Nvidia may return failure on all IsRegulatorOpen here, but the caller allows this specific function to fail and just returns ResultSuccess. */

        Result SetVoltageImpl(u32 idx, u32 micro_volts) {
            if (!IsRegulatorOpen(idx)) {
                R_SUCCEED();
            }

            Regulator &regulator = GetRegulator(idx);
            switch (regulator.type) {
                case PmicType_Main:        R_RETURN(SetVoltageMax77620(idx, micro_volts));
                case PmicType_Erista_Dvfs: R_RETURN(SetVoltageMax77621(idx, micro_volts));
                case PmicType_Mariko_Dvfs: R_RETURN(SetVoltageMax77812Reg(idx, micro_volts, regulator.use_vout_d ? regulator.vout_d_reg : regulator.vout_reg));
                default:                   AMS_ABORT();
            }
        }

        Result GetVoltageImpl(u32 idx, u32 &micro_volts) {
            if (!IsRegulatorOpen(idx)) {
                R_SUCCEED();
            }

            Regulator &regulator = GetRegulator(idx);
            switch (regulator.type) {
                case PmicType_Main:        R_RETURN(GetVoltageMax77620(idx, micro_volts));
                case PmicType_Erista_Dvfs: R_RETURN(GetVoltageMax77621(idx, micro_volts));
                case PmicType_Mariko_Dvfs: R_RETURN(GetVoltageMax77812(idx, micro_volts));
                default:                   AMS_ABORT();
            }
        }

        u32 GetCachedVoltageImpl(u32 idx) {
            if (!IsRegulatorOpen(idx)) {
                return -1;
            }

            Regulator &regulator = GetRegulator(idx);
            switch (regulator.type) {
                case PmicType_Main: return GetCachedVoltageMax77620(idx);
                case PmicType_Erista_Dvfs:
                case PmicType_Mariko_Dvfs: return GetCachedVoltageDvfsPmic(idx);
                default: return -1;
            }
        }

        Result EnablePowerDomainImpl(u32 idx) {
            if (!IsRegulatorOpen(idx)) {
                R_SUCCEED();
            }

            Regulator &regulator = GetRegulator(idx);
            switch (regulator.type) {
                case PmicType_Main:        R_RETURN(EnableMax77620(idx));
                case PmicType_Erista_Dvfs: R_RETURN(EnableMax77621(idx));
                case PmicType_Mariko_Dvfs: R_RETURN(EnableMax77812(idx));
                default:                   AMS_ABORT();
            }
        }

        Result IsPowerDomainEnabledImpl(u32 idx, bool &enabled) {
            if (!IsRegulatorOpen(idx)) {
                R_SUCCEED();
            }

            Regulator &regulator = GetRegulator(idx);
            switch (regulator.type) {
                case PmicType_Main:        R_RETURN(IsEnabledMax77620(idx, enabled));
                case PmicType_Erista_Dvfs: R_RETURN(IsEnabledMax77621(idx, enabled));
                case PmicType_Mariko_Dvfs: R_RETURN(IsEnabledMax77812(idx, enabled));
                default:                   AMS_ABORT();
            }
        }

        Result DisablePowerDomainImpl(u32 idx) {
            if (!IsRegulatorOpen(idx)) {
                R_SUCCEED();
            }

            Regulator &regulator = GetRegulator(idx);
            switch (regulator.type) {
                case PmicType_Main:        R_RETURN(DisableMax77620(idx));
                case PmicType_Erista_Dvfs: R_RETURN(DisableMax77621(idx));
                case PmicType_Mariko_Dvfs: R_RETURN(DisableMax77812(idx));
                default:                   AMS_ABORT();
            }
        }

        bool IsCpuRegulator(const char *name) {
            constexpr const char *CpuName = "max77621_cpu";
            return strcmp(name, CpuName) == 0;
        }

        u32 ReadLutVoltage(PowerDomain *domain) {
            uintptr_t mapping = GetDvfsMappings();
            constexpr u32 ClDvfsI2cStatus = 0x48;
            constexpr u32 LastI2cStatusValueStatusShift = 1;
            constexpr u32 LastI2cStatusValueStatusMask  = 0x3F;
            constexpr u32 DlDvfsI2cLutOffset            = 0x200;

            u32 status = *reinterpret_cast<u32 *>(mapping + ClDvfsI2cStatus);
            u32 lut_idx = (status >> LastI2cStatusValueStatusShift) & LastI2cStatusValueStatusMask;

            u32 voltage = 0;
            if (lut_idx < MaxLutSize) {
                u8 code = static_cast<u8>(*reinterpret_cast<u32 *>(mapping + DlDvfsI2cLutOffset + lut_idx * sizeof(u32)));

                Regulator &regulator = GetRegulator(*domain);
                voltage = GetVoltageFromCodeImpl(code, regulator.dvfs_pmic.min_uv, regulator.dvfs_pmic.step_uv);
            }

            return voltage;
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

    Result GetVoltage(PowerDomain *domain, u32 &micro_volts) {
        R_UNLESS(domain != nullptr, ResultInvalidArgument());

        /* Initialize handle */
        DeviceHandle handle;
        if (!InitializeHandleByName(std::addressof(handle), domain->GetName())) {
            R_SUCCEED();
        }

        /* Get The voltage if it's open */
        const Result result = GetVoltageImpl(handle.device_index, micro_volts);
        FinalizeHandle(std::addressof(handle));

        R_RETURN(result);
    }

    Result GetCachedVoltage(PowerDomain *domain, u32 &micro_volts) {
        R_UNLESS(domain != nullptr, ResultInvalidArgument());

        if (IsCpuRegulator(domain->GetName())) {
            /* For cpu: read the voltage from lut. */
            micro_volts = ReadLutVoltage(domain);
            R_SUCCEED();
        }
        /* For anything else read the cached voltage. */

        /* Initialize handle */
        DeviceHandle handle;
        /* Note nintendo does not check if this succeeds */
        InitializeHandleByName(std::addressof(handle), domain->GetName());

        /* Read the cached voltage */
        micro_volts = GetCachedVoltageImpl(handle.device_index);

        /* Finalize */
        FinalizeHandle(std::addressof(handle));

        R_SUCCEED();
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

    Result IsPowerDomainEnabled(PowerDomain *domain, bool &enabled) {
        R_UNLESS(domain != nullptr, ResultInvalidArgument());

        /* Initialize handle */
        DeviceHandle handle;
        if (!InitializeHandleByName(std::addressof(handle), domain->GetName())) {
            R_SUCCEED();
        }

        const Result result = IsPowerDomainEnabledImpl(handle.device_index, enabled);

        /* Finalize them. */
        FinalizeHandle(std::addressof(handle));

        R_RETURN(result);
    }

    Result DisablePowerDomain(PowerDomain *domain) {
        R_UNLESS(domain != nullptr, ResultInvalidArgument());

        /* Initialize handle */
        DeviceHandle handle;
        if (!InitializeHandleByName(std::addressof(handle), domain->GetName())) {
            R_SUCCEED();
        }

        const Result result = DisablePowerDomainImpl(handle.device_index);

        /* Finalize them. */
        FinalizeHandle(std::addressof(handle));

        R_RETURN(result);
    }

}
