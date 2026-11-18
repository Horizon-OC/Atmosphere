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

    Result PowerDomain::ResolveOutputRequests(bool &out_found, bool &out_enable) {
        out_found  = false;
        out_enable = false;

        for (const auto *session_entry : m_attached_sessions) {
            if (session_entry == nullptr || !session_entry->output_request_valid) {
                continue;
            }

            /* All requesting sessions must agree. */
            R_UNLESS(!out_found || session_entry->output_requested == out_enable, ResultRequestConflict());

            out_enable = session_entry->output_requested;
            out_found  = true;
        }

        /* No request: fall back to the domain default (only Ldo6 has one: off). */
        if (!out_found && m_off_by_default) {
            out_enable = false;
            out_found  = true;
        }

        R_SUCCEED();
    }

    Result PowerDomain::SetOutputEnabled(bool enable) {
        if (IsEnabledInCache(enable)) {
            R_SUCCEED();
        }

        if (enable) {
            const s64 ready_time_ns = m_min_off_hold_time_ns + m_last_off_time_ns;
            const s64 now_ns = os::ConvertToTimeSpan(os::GetSystemTick()).GetNanoSeconds();
            if (now_ns < ready_time_ns) {
                os::SleepThread(TimeSpan::FromNanoSeconds(ready_time_ns - now_ns));
            }

            R_TRY(EnablePowerDomain(this));
        } else {
            R_TRY(DisablePowerDomain(this));

            m_last_off_time_ns = os::ConvertToTimeSpan(os::GetSystemTick()).GetNanoSeconds();
        }

        m_enabled_cache       = enable;
        m_enabled_cache_valid = true;

        R_SUCCEED();
    }

    Result PowerDomain::ApplyRequests(bool enable) {
        bool found;
        bool resolved;

        R_TRY(ResolveOutputRequests(found, resolved));

        R_SUCCEED_IF(!found || resolved != enable);

        R_RETURN(SetOutputEnabled(enable));
    }

    Result PowerDomain::SetOutputRequest(PowerDomainSession *session, bool enable) {
        std::scoped_lock lk(m_mutex);

        const bool prev_valid     = session->output_request_valid;
        const bool prev_requested = session->output_requested;

        session->output_requested     = enable;
        session->output_request_valid = true;

        ON_RESULT_FAILURE {
            session->output_requested     = prev_valid ? prev_requested : false;
            session->output_request_valid = prev_valid;
        };

        R_RETURN(ApplyRequests(enable));
    }

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
