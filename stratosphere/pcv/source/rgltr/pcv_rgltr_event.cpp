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

namespace ams::pcv::rgltr {

    constinit os::SystemEventType g_state_table_event;

    void InitializeEventServices() {
        R_ABORT_UNLESS(os::CreateSystemEvent(std::addressof(g_state_table_event), os::EventClearMode_ManualClear, true));
    }

    os::SystemEventType *GetStateTableEvent() {
        return std::addressof(g_state_table_event);
    }

}
