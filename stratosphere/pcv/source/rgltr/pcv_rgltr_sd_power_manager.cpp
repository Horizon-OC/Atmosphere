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

#include "pcv_rgltr.hpp"
#include "pcv_rgltr_sd_power_manager.hpp"
#include "pcv_rgltr_power_domain.hpp"
#include "pcv_rgltr_control.hpp"

namespace ams::pcv::rgltr {

    Result SdPowerManager::EnsureLdoAttached() {
        /* We're already attached, nothing to do. */
        R_SUCCEED_IF(m_ldo_attached);

        /* Get the ldo domain. */
        PowerDomain *domain = FindPowerDomain(m_ldo_code);
        R_UNLESS(domain != nullptr, ddsf::ResultDeviceCodeNotFound());

        /* Attach. */
        m_ldo_session.emplace(domain);
        m_ldo_domain   = domain;
        m_ldo_attached = true;

        R_SUCCEED();
    }

    Result SdPowerManager::IsOutputEnabled(bool &out_enabled) {
        R_TRY(EnsureLdoAttached());

        R_RETURN(m_ldo_domain->IsEnabled(out_enabled));
    }

    Result SdPowerManager::SwitchTo1V8() {
        /* We're already set up. */
        R_SUCCEED_IF(m_state != SdPowerState::On3V3);

        /* Warcrime time. */
        R_TRY(m_ldo_session->RequestExactVoltageInMicroVolt(LowVoltageUv));
        R_TRY(m_ldo_session->RequestOutput(true));

        os::SleepThread(TimeSpan::FromMicroSeconds(150));

        /* Switch to 1.8V for uhs-I. */
        ClearIoRailPwr();
        m_state = SdPowerState::On1V8;

        R_SUCCEED();
    }

    Result SdPowerManager::PowerOn3V3(SdPowerState target_state) {
        /* Already enabled. */
        R_SUCCEED_IF(m_state != SdPowerState::Off);
        AMS_ABORT_UNLESS(target_state == SdPowerState::On3V3);

        /* Enable the io rail */
        PowerOnIoRail();
        ams::gpio::SetValue(std::addressof(m_pad_session), ams::gpio::GpioValue_High);
        os::SleepThread(TimeSpan::FromMilliSeconds(10));
        EnableIoRailPwr();

        /* Set 3.3V. */
        R_TRY(EnsureLdoAttached());
        R_TRY(m_ldo_session->RequestExactVoltageInMicroVolt(PowerOnVoltageUv));
        R_TRY(m_ldo_session->RequestOutput(true));

        os::SleepThread(TimeSpan::FromMicroSeconds(130));
        m_state = SdPowerState::On3V3;

        R_SUCCEED();
    }

    Result SdPowerManager::Enable() {
        R_RETURN(PowerOn3V3(SdPowerState::On3V3));
    }

    Result SdPowerManager::Disable() {
        /* Already disabled. */
        R_SUCCEED_IF(m_state == SdPowerState::Off);

        /* It must be at 1.8V */
        R_UNLESS(m_state == SdPowerState::On1V8, ResultInvalidSdPowerState());

        if (R_SUCCEEDED(EnsureLdoAttached())) {
            /* NOTE: Nintendo ignores the result. */
            R_DISCARD(m_ldo_session->RequestOutput(false));
        }

        os::SleepThread(TimeSpan::FromMilliSeconds(4));
        ams::gpio::SetValue(std::addressof(m_pad_session), ams::gpio::GpioValue_Low);
        os::SleepThread(TimeSpan::FromMilliSeconds(239));

        PowerOffIoRail();

        /* Prep for power off. */
        EnableIoRailPwr();

        m_state = SdPowerState::Off;

        R_SUCCEED();
    }

    Result SdPowerManager::IsEnabled(bool &enabled) {
        R_RETURN(IsOutputEnabled(enabled));
    }

    Result SdPowerManager::SetVoltage(u32 micro_volts) {
        bool enabled = false;
        R_TRY(IsOutputEnabled(enabled));

        /* Only allowed voltage for disabled output is 3.3V */
        if (!enabled) {
            R_UNLESS(micro_volts == PowerOnVoltageUv, ResultUnsupportedVoltage());
            R_SUCCEED();
        }

        /* If it's on, the only voltage allowed is 1.8V for uhs-I */
        R_UNLESS(micro_volts == LowVoltageUv, ResultUnsupportedVoltage());

        R_RETURN(SwitchTo1V8());
    }

    Result SdPowerManager::GetVoltage(u32 &micro_volts) {
        /* Note: Nintendo calls through regulator ISession here which just calls PowerDomain::GetVoltage. */
        /* We will just directly call PowerDomain::GetVoltage. */
        R_TRY(EnsureLdoAttached());

        R_RETURN(m_ldo_domain->GetVoltage(micro_volts));
    }

    Result SdPowerManager::GetVoltageRange(u32 &out_min_uv, u32 &out_max_uv, u32 &out_step_uv) {
        out_min_uv = LowVoltageUv;
        out_max_uv = PowerOnVoltageUv;
        out_step_uv = out_max_uv - out_min_uv;

        R_SUCCEED();
    }

    void SdPowerManager::Initialize() {
        /* Register the sd card power domain. */
        RegisterDomain(std::addressof(m_sd_domain), m_sd_domain.GetDeviceCode());

        /* Initialize gpio */
        ams::gpio::Initialize();

        /* Open session */
        R_ABORT_UNLESS(ams::gpio::OpenSession(std::addressof(m_pad_session), ams::gpio::DeviceCode_PowSdEn));

        /* Set the direction */
        ams::gpio::SetDirection(std::addressof(m_pad_session), ams::gpio::Direction_Output);
        ams::gpio::SetValue(std::addressof(m_pad_session),     ams::gpio::GpioValue_Low);

        /* Power off the sdmmc1 rail. */
        PowerOffIoRail();
    }

    SdPowerManager &GetSdPowerManager() {
        static constinit SdPowerManager manager;

        return manager;
    }

}
