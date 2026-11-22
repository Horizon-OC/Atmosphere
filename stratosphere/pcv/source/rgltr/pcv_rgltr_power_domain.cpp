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

    Result PowerDomain::ResolveVoltageRequests(u32 &out_voltage_uv) {
        bool has_request = false;

        s32 min_uv = m_min_voltage_uv;
        s32 max_uv = m_max_voltage_uv;

        for (const auto *session_entry : m_attached_sessions) {
            if (session_entry == nullptr || !session_entry->voltage_min_valid || !session_entry->voltage_max_valid) {
                continue;
            }

            R_UNLESS(IsSaneVoltageRequest(session_entry, min_uv, max_uv), ResultRequestConflict());

            min_uv = std::max(min_uv, session_entry->voltage_min_uv);
            max_uv = std::min(max_uv, session_entry->voltage_max_uv);
            has_request = true;
        }

        if (has_request) {
            out_voltage_uv = min_uv;
            R_SUCCEED();
        }

        /* NOTE: Nintendo does this check, but m_default_voltage_valid is always false, so this is dead code. */
        /* if (m_default_voltage_valid) { */
            /* out_voltage_uv = m_default_voltage_uv; */
            /* R_SUCCEED(); */
        /* } */

        R_THROW(ResultInvalidCache());
    }

    u64 PowerDomain::ResolveOffStateHoldRequests() {
        u64 max_hold_time{};

        /* Find the largest requested hold time. */
        for (const auto *session_entry : m_attached_sessions) {
            if (session_entry != nullptr && session_entry->hold_time_valid &&session_entry->hold_time > max_hold_time) {
                max_hold_time = session_entry->hold_time;
            }
        }

        return max_hold_time;
    }

    Result PowerDomain::SetOutputEnabled(bool enable) {
        R_SUCCEED_IF(IsEnabledInCache(enable));

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

        /* Only continue if the result is the state we're applying. */
        R_SUCCEED_IF(!found || resolved != enable);

        R_RETURN(SetOutputEnabled(enable));
    }

    Result PowerDomain::ReapplyOutputRequests() {
        bool found;
        bool resolved;

        R_TRY(ResolveOutputRequests(found, resolved));

        R_SUCCEED_IF(!found);

        R_RETURN(SetOutputEnabled(resolved));
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

    Result PowerDomain::CancelOutputRequest(PowerDomainSession *session) {
        std::scoped_lock lk(m_mutex);

        /* Invalidate output requests. */
        session->output_request_valid = false;

        R_RETURN(ReapplyOutputRequests());
    }

    Result PowerDomain::ReapplyVoltageRequests() {
        u32 voltage_request{};
        R_TRY_CATCH(ResolveVoltageRequests(voltage_request)) {
            R_CATCH(ResultInvalidCache) { /* ... */ }
        } R_END_TRY_CATCH;

        /* Check if we need to change the voltage at all. */
        R_SUCCEED_IF(IsVoltageCached(voltage_request));

        R_TRY(SetVoltage(this, voltage_request));

        /* Cache the new voltage. */
        m_voltage_cache_uv    = voltage_request;
        m_voltage_cache_valid = true;

        R_SUCCEED();
    }

    Result PowerDomain::SetVoltageRequest(PowerDomainSession *session, s32 min_uv, s32 max_uv) {
        std::scoped_lock lk(m_mutex);

        R_UNLESS(IsSaneVoltageRequest(min_uv, max_uv), ResultUnsupportedVoltage());

        /* Save the previous voltage for potential rollbacks. */
        s32 prev_min_voltage{};
        s32 prev_max_voltage{};
        bool valid_session_voltage = IsValidSessionVoltage(session);
        if (valid_session_voltage) {
            prev_min_voltage = session->voltage_min_uv;
            prev_max_voltage = session->voltage_max_uv;
        }

        session->voltage_min_uv    = min_uv;
        session->voltage_min_valid = true;
        session->voltage_max_uv    = max_uv;
        session->voltage_max_valid = true;

        Result result_set_voltage = ReapplyVoltageRequests();
        R_SUCCEED_IF(R_SUCCEEDED(result_set_voltage));

        /* Roll back on failure assuming the previous session was valid. */
        if (valid_session_voltage) {
            session->voltage_min_uv    = prev_min_voltage;
            session->voltage_min_valid = true;
            session->voltage_max_uv    = prev_max_voltage;
            session->voltage_max_valid = true;
        } else {
            /* The previous session wasn't valid. */
            session->voltage_min_valid = false;
            session->voltage_max_valid = false;
        }

        R_THROW(result_set_voltage);
    }

    Result PowerDomain::CancelVoltageRequest(PowerDomainSession *session) {
        std::scoped_lock lk(m_mutex);

        /* Invalidate the session */
        session->voltage_min_valid = false;
        session->voltage_max_valid = false;

        R_RETURN(ReapplyVoltageRequests());
    }

    Result PowerDomain::GetMinimumOffStateHoldTime(u64 *out_hold_time) {
        std::scoped_lock lk(m_mutex);

        *out_hold_time = m_min_off_hold_time_ns;

        R_SUCCEED();
    }

    Result PowerDomain::SetMinimumOffStateHoldRequest(PowerDomainSession *session, u64 hold_time) {
        std::scoped_lock lk(m_mutex);

        session->hold_time       = hold_time;
        session->hold_time_valid = true;

        /* Resolve the minimum off hold time by finding the largest request. */
        m_min_off_hold_time_ns = ResolveOffStateHoldRequests();

        R_SUCCEED();
    }

    Result PowerDomain::CancelMinimumOffStateHoldTimeRequest(PowerDomainSession *session) {
        std::scoped_lock lk(m_mutex);

        /* Invalide the hold time. */
        session->hold_time_valid = false;

        /* Resolve it */
        m_min_off_hold_time_ns = ResolveOffStateHoldRequests();

        R_SUCCEED();
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
