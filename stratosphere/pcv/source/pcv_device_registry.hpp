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

namespace ams::pcv {

    template<typename Device, size_t Capacity>
    class DeviceRegistry {
        private:
            struct Entry {
                DeviceCode device_code{InvalidDeviceCode};
                Device    *device{};
            };
        private:
            os::SdkMutex m_mutex{};
            size_t       m_count{};
            Entry        m_entries[Capacity]{};
        public:
            constexpr DeviceRegistry() = default;

            void Register(DeviceCode device_code, Device *device) {
                std::scoped_lock lk(m_mutex);

                AMS_ABORT_UNLESS(m_count < Capacity);
                m_entries[m_count++] = { device_code, device };
            }

            Device *Find(DeviceCode device_code) {
                std::scoped_lock lk(m_mutex);

                for (size_t i = 0; i < m_count; ++i) {
                    if (m_entries[i].device_code == device_code) {
                        return m_entries[i].device;
                    }
                }

                return nullptr;
            }

            void Unregister(DeviceCode device_code) {
                std::scoped_lock lk(m_mutex);

                for (size_t i = 0; i < m_count; ++i) {
                    if (m_entries[i].device_code == device_code) {
                        m_entries[i] = m_entries[--m_count];
                        return;
                    }
                }
            }
    };

}
