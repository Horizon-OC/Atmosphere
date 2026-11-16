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
#include "pcv_rgltr_session.hpp"
#include "pcv_rgltr_manager.hpp"
#include "pcv_rgltr.hpp"
#include "pcv_rgltr_control.hpp"

namespace ams::pcv::rgltr {

    namespace {

        struct RgltrSessionTag;
        using SessionAllocator = sf::ExpHeapStaticAllocator<0x2000, RgltrSessionTag>;
        using SessionFactory   = sf::ObjectFactory<typename SessionAllocator::Policy>;

        class StaticAllocatorInitializer {
            public:
                StaticAllocatorInitializer() {
                    SessionAllocator::Initialize(lmem::CreateOption_ThreadSafe);
                }
        } g_static_allocator_initializer;
    }

    Result RgltrManager::OpenSession(sf::Out<sf::SharedPointer<IRgltrSession>> out_session, DeviceCode device_code) {
        PowerDomain *domain = FindPowerDomain(device_code);
        AMS_ABORT_UNLESS(domain != nullptr); /* Nintendo returns a bus error? TODO look at this. */

        /* Create the session. */
        auto session = SessionFactory::CreateSharedEmplaced<IRgltrSession, RgltrSession>(domain);
        AMS_ABORT_UNLESS(session != nullptr);

        *out_session = std::move(session);

        R_SUCCEED();
    }

    Result RgltrManager::GetRegulatorStateTable(const sf::OutArray<PowerDomainState> &out_states, s32 max_count, sf::Out<s32> out_count) {
        R_RETURN(GetStateTable(out_states.GetPointer(), out_count.GetPointer(), max_count));
    }

    Result RgltrManager::GetRegulatorStateTableUpdateEvent(sf::OutCopyHandle out_event) {
        AMS_UNUSED(out_event);
        AMS_ABORT("TODO");
    }

    Result RgltrManager::GetRegulatorStateTableCount(sf::Out<s32> out_count) {
        out_count.SetValue(GetStateTableCount());

        R_SUCCEED();
    }

}
