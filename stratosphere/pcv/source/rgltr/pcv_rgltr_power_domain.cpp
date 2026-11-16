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
#include "pcv_rgltr_power_domain.hpp"
#include "pcv_rgltr_control.hpp"

namespace ams::pcv::rgltr {

    Result PowerDomain::IsEnabledCacheValid(bool &enabled) {
        std::scoped_lock lk(m_mutex);

        /* Is the enabled cache valid? */
        if (m_enabled_cache_valid) {
            enabled = m_enabled_cache;

            R_SUCCEED();
        }

        R_THROW(ResultInvalidCache());
    }

    Result PowerDomain::IsEnabled(bool &enabled) {
        R_TRY(IsPowerDomainEnabled(this, enabled));

        std::scoped_lock lk(m_mutex);

        /* Invalidate the cache. */
        m_enabled_cache_valid = false;

        /* Set the cache. */
        m_enabled_cache = enabled;

        /* Validate the cache. */
        m_enabled_cache_valid = true;

        /* Succeed */
        R_SUCCEED();
    }

    Result PowerDomain::GetCachedVoltage(u32 &micro_volts) {
        std::scoped_lock lk(m_mutex);

        /* Get voltage cache if valid. */
        if (m_voltage_cache_valid) {
            micro_volts = m_voltage_cache_uv;

            R_SUCCEED();
        }

        R_THROW(ResultInvalidCache());
    }

    Result PowerDomain::GetVoltage(u32 &micro_volts) {
        /* Get the current voltage. */
        R_TRY(rgltr::GetVoltage(this, micro_volts));

        std::scoped_lock lk(m_mutex);
        /* Invalidate the cache. */
        m_voltage_cache_valid = false;

        /* Cache the voltage. */
        m_voltage_cache_uv = micro_volts;

        /* Validate the cache. */
        m_voltage_cache_valid = true;

        /* Succeed. */
        R_SUCCEED();
    }

}
