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
#include "pcv_rgltr_session.hpp"
#include "pcv_rgltr_state_table.hpp"
#include "pcv_rgltr_event.hpp"
#include "pcv_rgltr_control.hpp"

namespace ams::pcv::rgltr {

    RgltrSession::RgltrSession(PowerDomain *domain) : m_domain(domain) {
        AMS_ASSERT(m_domain != nullptr);
        m_domain->AttachSession(std::addressof(m_domain_session));
    }

    RgltrSession::~RgltrSession() {
        m_domain->DetachSession(std::addressof(m_domain_session));
        m_domain->UpdateAfterSessionClose();
    }

    void RgltrSession::Signal() {
        /* Signal event on state table devices. */
        if (IsStateTableDevice(m_domain)) {
            os::SignalSystemEvent(GetStateTableEvent());
        }
    }

    Result RgltrSession::RequestOutput(bool in_enabled) {
        R_TRY(m_domain->SetOutputRequest(std::addressof(m_domain_session), in_enabled));

        Signal();

        R_SUCCEED();
    }

    Result RgltrSession::CancelOutputRequest() {
        R_RETURN(m_domain->CancelOutputRequest(std::addressof(m_domain_session)));
    }

    Result RgltrSession::IsOutputEnabled(sf::Out<bool> out_enabled) {
        R_RETURN(m_domain->IsEnabled(*out_enabled));
    }

    Result RgltrSession::GetVoltageRangeInMicroVolt(sf::Out<u32> out_min_uv, sf::Out<u32> out_max_uv, sf::Out<u32> out_step_uv) {
        R_RETURN(GetVoltageRange(m_domain, *out_min_uv, *out_max_uv, *out_step_uv));
    }

    Result RgltrSession::GetVoltageInMicroVolt(sf::Out<u32> out_uv) {
        R_RETURN(m_domain->GetVoltage(*out_uv));
    }

    Result RgltrSession::RequestVoltageInMicroVolt(s32 in_min_uv, s32 in_max_uv) {
        R_TRY(m_domain->SetVoltageRequest(std::addressof(m_domain_session), in_min_uv, in_max_uv));

        Signal();

        R_SUCCEED();
    }

    Result RgltrSession::CancelVoltageRequest() {
        R_TRY(m_domain->CancelVoltageRequest(std::addressof(m_domain_session)));

        Signal();

        R_SUCCEED();
    }

    Result RgltrSession::GetMinimumOffStateHoldTime(sf::Out<u64> out_hold_time) {
        R_RETURN(m_domain->GetMinimumOffStateHoldTime(out_hold_time.GetPointer()));
    }

    Result RgltrSession::RequestMinimumOffStateHoldTime(u64 in_hold_time) {
        R_RETURN(m_domain->SetMinimumOffStateHoldRequest(std::addressof(m_domain_session), in_hold_time));
    }

    Result RgltrSession::CancelMinimumOffStateHoldTimeRequest() {
        R_RETURN(m_domain->CancelMinimumOffStateHoldTimeRequest(std::addressof(m_domain_session)));
    }

}
