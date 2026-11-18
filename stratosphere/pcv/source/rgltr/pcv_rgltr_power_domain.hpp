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

    struct PowerDomainSession {
        bool output_request_valid = false;
        bool output_requested     = false;
        bool voltage_min_valid    = false;
        s32  voltage_min_uv       = 0;
        bool voltage_max_valid    = false;
        s32  voltage_max_uv       = 0;
        bool hold_time_valid      = false;
        u64  hold_time            = 0;
    };

    class PowerDomain {
        private:
            static constexpr size_t MaxSessions = 30; /* RgltrMaxSessions */
        private:
            const char *m_name;
            DeviceCode m_device_code;
            /* Default output request. Only Ldo6 (I2C2/I2C3) has one, and it's off. */
            bool m_off_by_default;
            os::SdkMutex m_mutex{};

            /* This is gross but not nearly as gross as using intrusive linked lists. */
            std::array<PowerDomainSession *, MaxSessions> m_attached_sessions{};

            bool m_enabled_cache       = false;
            bool m_enabled_cache_valid = false;

            u32 m_voltage_cache_uv{};
            bool m_voltage_cache_valid = false;

            u64 m_min_off_hold_time_ns{};
            u64 m_last_off_time_ns{};
        public:
            constexpr PowerDomain(const char *name, DeviceCode code) : m_name(name), m_device_code(code), m_off_by_default(code.GetInternalValue() == PcvPowerDomainId_Max77620_Ldo6) { /* ... */ }

            ALWAYS_INLINE constexpr const char *GetName()      const { return m_name; }
            ALWAYS_INLINE constexpr DeviceCode GetDeviceCode() const { return m_device_code; }
        private:
            ALWAYS_INLINE bool IsEnabledInCache(bool enabled) const { return m_enabled_cache_valid && m_enabled_cache == enabled; }
        private:
            PowerDomainSession *&GetAvailableSession();
            PowerDomainSession *&FindSession(PowerDomainSession *session);
            ALWAYS_INLINE void FreeSession(PowerDomainSession *&slot) { slot = nullptr; }
        public:
            /* Power domain session. */
            void AttachSession(PowerDomainSession *session);
            void DetachSession(PowerDomainSession *session);
            void UpdateAfterSessionClose();
            bool HasOpenSessions();
        private:
            /* Resolve sessions. */
            Result ResolveOutputRequests(bool &out_found, bool &out_enable);
        private:
            Result SetOutputEnabled(bool enable);
            Result ApplyRequests(bool enable);
        public:
            Result SetOutputRequest(PowerDomainSession *session, bool enable);
        public:
            Result IsEnabledCacheValid(bool &enabled);
            Result IsEnabled(bool &enabled);
            Result GetCachedVoltage(u32 &micro_volts);
            Result GetVoltage(u32 &micro_volts);
    };
}
