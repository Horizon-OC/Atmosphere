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

#define AMS_PCV_I_CLKRST_ARBITRATION_MANAGER_INTERFACE_INFO(C, H) \
    AMS_SF_METHOD_INFO(C, H, 0, Result, ReleaseControl, (u32 device_code), (device_code))

AMS_SF_DEFINE_INTERFACE(ams::pcv::clkrst, IClkrstArbitrationManager, AMS_PCV_I_CLKRST_ARBITRATION_MANAGER_INTERFACE_INFO, 0x636C6B61)

namespace ams::pcv::clkrst {

    class ClkrstArbitrationManager {
        private:
            sf::hipc::ServerManagerBase *m_server_manager;
            bool m_sdmmc1_released = false;
            bool m_sdmmc2_released = false;
            bool m_sdmmc4_released = false;
        public:
            constexpr explicit ClkrstArbitrationManager(sf::hipc::ServerManagerBase *manager) : m_server_manager(manager) { /* ... */ }

            Result ReleaseControl(u32 device_code) {
                switch (device_code) {
                    case DeviceCode_Sdmmc1.GetInternalValue(): {
                        m_sdmmc1_released = true;
                        break;
                    }
                    case DeviceCode_Sdmmc2.GetInternalValue(): {
                        m_sdmmc2_released = true;
                        break;
                    }
                    case DeviceCode_Sdmmc4.GetInternalValue(): {
                        m_sdmmc4_released = true;
                        break;
                    }
                    default: {
                        R_SUCCEED();
                    }
                }
                if (m_sdmmc1_released && m_sdmmc2_released && m_sdmmc4_released) {
                    m_server_manager->RequestStopProcessing();
                }
                R_SUCCEED();
            }
    };
    static_assert(IsIClkrstArbitrationManager<ClkrstArbitrationManager>);

}
