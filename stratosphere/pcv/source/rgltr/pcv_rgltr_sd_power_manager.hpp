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
#include "pcv_rgltr_session.hpp"

namespace ams::pcv::rgltr {

    class SdPowerManager {
        private:
            static constexpr u32 PmcBase    = 0x7000E400;
            static constexpr u32 Sdmmc1Rail = BIT(12);

            /* PMC offsets. */
            static constexpr u32 ApbdevPmcNoIoPower = 0x44;
            static constexpr u32 ApbDevPmcPwrDet    = 0xE4;

            /* For power on. */
            static constexpr u32 PowerOnVoltageUv = 3300000;
            /* UHS-I */
            static constexpr u32 LowVoltageUv     = 1800000;
        private:
            enum class SdPowerState : u32 {
                Off   = 0,
                On1V8 = 1,
                On3V3 = 2,
            };
        private:
            PowerDomain                  m_sd_domain{"sdcard", DeviceCode_SdCardPower};

            DeviceCode                   m_ldo_code   = PcvPowerDomainId_Max77620_Ldo2;
            PowerDomain                 *m_ldo_domain = nullptr;
            util::optional<RgltrSession> m_ldo_session;
            bool                         m_ldo_attached = false;

            ams::gpio::GpioPadSession m_pad_session{};

            SdPowerState m_state = SdPowerState::Off;
        public:
            ALWAYS_INLINE PowerDomain &GetDomain() { return m_sd_domain; }
        private:
            ALWAYS_INLINE void PowerOnIoRail() {
                u32 no_io_register;
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_register), PmcBase + ApbdevPmcNoIoPower, 0, 0));
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_register), PmcBase + ApbdevPmcNoIoPower, ~0, no_io_register &= ~Sdmmc1Rail));

                /* Nintendo reads it back, TODO: Test if this is needed eventually. */
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_register), PmcBase + ApbdevPmcNoIoPower, 0, 0));
            }

            ALWAYS_INLINE void PowerOffIoRail() {
                u32 no_io_register;
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_register), PmcBase + ApbdevPmcNoIoPower, 0, 0));
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_register), PmcBase + ApbdevPmcNoIoPower, ~0, no_io_register |= Sdmmc1Rail));

                /* Nintendo reads it back, TODO: Test if this is needed eventually. */
                R_DISCARD(svc::ReadWriteRegister(std::addressof(no_io_register), PmcBase + ApbdevPmcNoIoPower, 0, 0));
            }

            ALWAYS_INLINE void ClearIoRailPwr() {
                u32 pmc_pwr_det;
                R_DISCARD(svc::ReadWriteRegister(std::addressof(pmc_pwr_det), PmcBase + ApbDevPmcPwrDet, 0, 0));
                pmc_pwr_det &= ~Sdmmc1Rail;
                R_DISCARD(svc::ReadWriteRegister(std::addressof(pmc_pwr_det), PmcBase + ApbDevPmcPwrDet, ~0, pmc_pwr_det));
                R_DISCARD(svc::ReadWriteRegister(std::addressof(pmc_pwr_det), PmcBase + ApbDevPmcPwrDet, 0, 0));
            }

            ALWAYS_INLINE void EnableIoRailPwr() {
                u32 pmc_pwr_det;
                R_DISCARD(svc::ReadWriteRegister(std::addressof(pmc_pwr_det), PmcBase + ApbDevPmcPwrDet, 0, 0));
                R_DISCARD(svc::ReadWriteRegister(std::addressof(pmc_pwr_det), PmcBase + ApbDevPmcPwrDet, ~0, pmc_pwr_det | Sdmmc1Rail));
                R_DISCARD(svc::ReadWriteRegister(std::addressof(pmc_pwr_det), PmcBase + ApbDevPmcPwrDet, 0, 0));
            }
        private:
            Result EnsureLdoAttached();
            Result IsOutputEnabled(bool &out_enabled);
            Result SwitchTo1V8();
            Result PowerOn3V3(SdPowerState target_state);
        public:
            Result Enable();
            Result Disable();
            Result IsEnabled(bool &enabled);
            Result SetVoltage(u32 micro_volts);
            Result GetVoltage(u32 &micro_volts);
            Result GetVoltageRange(u32 &out_min_uv, u32 &out_max_uv, u32 &out_step_uv);
            void Initialize();
    };

    SdPowerManager &GetSdPowerManager();

}