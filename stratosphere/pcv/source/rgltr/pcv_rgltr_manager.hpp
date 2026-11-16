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

#pragma once
#include <stratosphere.hpp>
#include "pcv_rgltr_session.hpp"

#define AMS_PCV_I_RGLTR_MANAGER_INTERFACE_INFO(C, H)                                                                                                                                                      \
    AMS_SF_METHOD_INFO(C, H, 0, Result, OpenSession,                       (sf::Out<sf::SharedPointer<ams::pcv::rgltr::IRgltrSession>> out_session, u32 device_code), (out_session, device_code))         \
    AMS_SF_METHOD_INFO(C, H, 1, Result, GetRegulatorStateTable,            (const sf::OutArray<ams::pcv::rgltr::PowerDomainState> &out_states, s32 max_count, sf::Out<s32> out_count), (out_states, max_count, out_count)) \
    AMS_SF_METHOD_INFO(C, H, 2, Result, GetRegulatorStateTableUpdateEvent, (sf::OutCopyHandle out_event),                                                             (out_event))                        \
    AMS_SF_METHOD_INFO(C, H, 3, Result, GetRegulatorStateTableCount,       (sf::Out<s32> out_count),                                                                  (out_count))

AMS_SF_DEFINE_INTERFACE(ams::pcv::rgltr, IRgltrManager, AMS_PCV_I_RGLTR_MANAGER_INTERFACE_INFO, 0x6D726567)

namespace ams::pcv::rgltr {

    class RgltrManager {
        public:
            Result OpenSession(sf::Out<sf::SharedPointer<IRgltrSession>> out_session, DeviceCode device_code);
            Result GetRegulatorStateTable(const sf::OutArray<PowerDomainState> &out_states, s32 max_count, sf::Out<s32> out_count);
            Result GetRegulatorStateTableUpdateEvent(sf::OutCopyHandle out_event);
            Result GetRegulatorStateTableCount(sf::Out<s32> out_count);
    };
    static_assert(ams::pcv::rgltr::IsIRgltrManager<RgltrManager>);

}
