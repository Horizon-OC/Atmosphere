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
#include "pcv_clkrst_device.hpp"
#include "../pcv_hardware_type.hpp"
#include "../pcv_device_registry.hpp"

namespace ams::pcv::clkrst {

    namespace {

        #include "pcv_clkrst_device_table.inc"

        constinit DeviceRegistry<ClkrstDevice, ClkrstDeviceCount + ClkrstDeviceAliasCount> g_device_registry;

        bool NeedsRegistering(ClkrstDevice &device, bool is_mariko) {
            switch (device.module_id) {
                case ModuleId_Extperiph2: return is_mariko;
                case ModuleId_Owr:        return false; /* NOTE: Nvidia registers this with vcc_debug_ip enabled. */
                default:                  return true;
            }
        }

        inline void RegisterAlias(ClkrstDevice &device) {
            for (const auto &alias : g_device_alias_table) {
                if (alias.module_id == device.module_id) {
                    g_device_registry.Register(DeviceCode(alias.alias_id), std::addressof(device));
                }
            }
        }

        void RegisterModules(bool is_mariko) {
            for (auto &device : g_device_table) {
                /* Register all devices that need to be registered. */
                if (!NeedsRegistering(device, is_mariko)) {
                    continue;
                }

                /* Register the device. */
                g_device_registry.Register(DeviceCode(device.module_id), std::addressof(device));

                /* If it has an alias, register it as well. */
                RegisterAlias(device);
            }
        }
    }

    void Initialize() {
        RegisterModules(IsMariko());
    }

}
