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
#include "pcv_rgltr_power_domain.hpp"
#include "pcv_rgltr_control.hpp"
#include "pcv_rgltr_state_table.hpp"

namespace ams::pcv::rgltr {

    namespace {

        constinit DeviceCode g_state_table_domains[] = {
            PcvPowerDomainId_Max77620_Sd0,
            PcvPowerDomainId_Max77621_Cpu,
            PcvPowerDomainId_Max77812_Gpu,
        };
        static_assert(util::size(g_state_table_domains) == 3);

    }

    s32 GetStateTableCount() {
        return static_cast<s32>(util::size(g_state_table_domains));
    }

    bool IsStateTableDevice(PowerDomain *domain) {
        if (domain == nullptr) {
            return false;
        }

        for (const auto &code : g_state_table_domains) {
            if (domain->GetDeviceCode() == code) {
                return true;
            }
        }

        return false;
    }

    Result GetStateTable(PowerDomainState *state, s32 *out_count, s32 max_count) {
        R_UNLESS(max_count >= GetStateTableCount(), ResultInsufficientBuffer());

        s32 i = 0;
        for (; i < GetStateTableCount(); ++i) {
            const auto device_code = g_state_table_domains[i];
            state[i].device_code = device_code;

            PowerDomain *domain = FindPowerDomain(device_code);
            AMS_ASSERT(domain != nullptr);

            if (device_code == PcvPowerDomainId_Max77621_Gpu) {
                R_TRY(IsPowerDomainEnabled(domain, state[i].enabled));
                R_TRY(GetCachedVoltage(domain, state[i].voltage));
            } else if (device_code == PcvPowerDomainId_Max77621_Cpu) {
                /* Cpu always reads lut. */
                state[i].enabled = true;
                R_TRY(GetCachedVoltage(domain, state[i].voltage));
            } else {
                /* Try to read enabled flag through cache, read power domains on invalid cache. */
                Result rc = domain->IsEnabledCacheValid(state[i].enabled);
                if (R_FAILED(rc)) {
                    R_UNLESS(ResultInvalidCache::Includes(rc), rc);
                    R_TRY(domain->IsEnabled(state[i].enabled));
                }

                /* Same as with enabled, read voltage through cache first, perform actual fresh read on invalid cache. */
                rc = domain->GetCachedVoltage(state[i].voltage);
                if (R_FAILED(rc)) {
                    R_UNLESS(ResultInvalidCache::Includes(rc), rc);

                    rc = domain->GetVoltage(state[i].voltage);
                    if (R_FAILED(rc)) {
                        /* NOTE: Nintendo doesn't the voltage on 2192-0001 (0x2C0), but as far as I can tell this result is never thrown.*/
                        R_UNLESS(rc.GetValue() == 0x2C0, rc);
                        state[i].voltage = 0;
                    }
                }
            }
        }

        *out_count = i;
        R_SUCCEED();
    }

}
