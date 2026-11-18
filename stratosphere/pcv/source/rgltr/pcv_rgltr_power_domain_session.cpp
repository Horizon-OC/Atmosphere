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

namespace ams::pcv::rgltr {

    PowerDomainSession *&PowerDomain::GetAvailableSession() {
        for (auto &session_entry : m_attached_sessions) {
            /* Check that the session slot is free. */
            if (session_entry == nullptr) {
                return session_entry;
            }
        }

        /* There are no free session slot. */
        AMS_ABORT();
    }

    PowerDomainSession *&PowerDomain::FindSession(PowerDomainSession *session) {
        for (auto &session_entry : m_attached_sessions) {
            /* Find the session. */
            if (session_entry == session) {
                return session_entry;
            }
        }

        /* The session isn't attached to this domain. */
        AMS_ABORT();
    }

    void PowerDomain::AttachSession(PowerDomainSession *session) {
        std::scoped_lock lk(m_mutex);

        /* Attach to an available session slot, abort when no slot is available */
        GetAvailableSession() = session;
    }

    void PowerDomain::DetachSession(PowerDomainSession *session) {
        std::scoped_lock lk(m_mutex);

        /* Detach the session. */
        /* This aborts when the session isn't attached. */
        FreeSession(FindSession(session));
    }

    void PowerDomain::UpdateAfterSessionClose() {
        AMS_ABORT("TODO");
    }

    bool PowerDomain::HasOpenSessions() {
        std::scoped_lock lk(m_mutex);

        for (const auto *session : m_attached_sessions) {
            /* There's an attached session. */
            if (session != nullptr) {
                return true;
            }
        }

        /* Nothing attached. */
        return false;
    }

}
