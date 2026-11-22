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
#include "pcv_rgltr_power_domain.hpp"

#define AMS_PCV_I_RGLTR_SESSION_INTERFACE_INFO(C, H)                                                                                                                                               \
    AMS_SF_METHOD_INFO(C, H, 0, Result, RequestOutput,                        (bool in_enabled),                                                            (in_enabled))                          \
    AMS_SF_METHOD_INFO(C, H, 1, Result, CancelOutputRequest,                  (),                                                                           ())                                    \
    AMS_SF_METHOD_INFO(C, H, 2, Result, IsOutputEnabled,                      (sf::Out<bool> out_enabled),                                                  (out_enabled))                         \
    AMS_SF_METHOD_INFO(C, H, 3, Result, GetVoltageRangeInMicroVolt,           (sf::Out<u32> out_min_uv, sf::Out<u32> out_max_uv, sf::Out<u32> out_step_uv), (out_min_uv, out_max_uv, out_step_uv)) \
    AMS_SF_METHOD_INFO(C, H, 4, Result, GetVoltageInMicroVolt,                (sf::Out<u32> out_uv),                                                        (out_uv))                              \
    AMS_SF_METHOD_INFO(C, H, 5, Result, RequestVoltageInMicroVolt,            (s32 in_min_uv, s32 in_max_uv),                                               (in_min_uv, in_max_uv))                \
    AMS_SF_METHOD_INFO(C, H, 6, Result, CancelVoltageRequest,                 (),                                                                           ())                                    \
    AMS_SF_METHOD_INFO(C, H, 7, Result, GetMinimumOffStateHoldTime,           (sf::Out<u64> out_hold_time),                                                 (out_hold_time))                       \
    AMS_SF_METHOD_INFO(C, H, 8, Result, RequestMinimumOffStateHoldTime,       (u64 in_hold_time),                                                           (in_hold_time))                        \
    AMS_SF_METHOD_INFO(C, H, 9, Result, CancelMinimumOffStateHoldTimeRequest, (),                                                                           ())

AMS_SF_DEFINE_INTERFACE(ams::pcv::rgltr, IRgltrSession, AMS_PCV_I_RGLTR_SESSION_INTERFACE_INFO, 0x73726567)

namespace ams::pcv::rgltr {

    class RgltrSession {
        private:
            PowerDomain       *m_domain;
            PowerDomainSession m_domain_session{};
        private:
            void Signal();
        public:
            explicit RgltrSession(PowerDomain *domain);
            ~RgltrSession();

            Result RequestOutput(bool in_enabled);
            Result CancelOutputRequest();
            Result IsOutputEnabled(sf::Out<bool> out_enabled);
            Result GetVoltageRangeInMicroVolt(sf::Out<u32> out_min_uv, sf::Out<u32> out_max_uv, sf::Out<u32> out_step_uv);
            Result GetVoltageInMicroVolt(sf::Out<u32> out_uv);
            Result RequestVoltageInMicroVolt(s32 in_min_uv, s32 in_max_uv);
            Result RequestExactVoltageInMicroVolt(s32 voltage_uv);
            Result CancelVoltageRequest();
            Result GetMinimumOffStateHoldTime(sf::Out<u64> out_hold_time);
            Result RequestMinimumOffStateHoldTime(u64 in_hold_time);
            Result CancelMinimumOffStateHoldTimeRequest();
    };
    static_assert(ams::pcv::rgltr::IsIRgltrSession<RgltrSession>);

}
