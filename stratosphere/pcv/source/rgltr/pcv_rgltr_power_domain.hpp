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

namespace ams::pcv::rgltr {

    class PowerDomain {
        private:
            const char *m_name;
            DeviceCode m_device_code;
            os::SdkMutex m_mutex{};
        public:
            constexpr PowerDomain(const char *name, DeviceCode code) : m_name(name), m_device_code(code) { /* ... */ }

            ALWAYS_INLINE constexpr const char *GetName()      const { return m_name; }
            ALWAYS_INLINE constexpr DeviceCode GetDeviceCode() const { return m_device_code; }
    };

}
