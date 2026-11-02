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

namespace ams::pcv::bpc {

    /* Interrupts left unmasked while asleep */
    constexpr inline u8 Max77620PmicIrqTopSleepWakeMask   = Max77620PmicIrqTopGlblMask | Max77620PmicIrqTopRtcMask | Max77620PmicIrqTopOnOffMask;
    constexpr inline u8 Max77620PmicOnOffIrqSleepWakeMask = Max77620PmicOnOffIrqEn0RiseMask | Max77620PmicOnOffIrqAcOkFallMask | Max77620PmicOnOffIrqAcOkRiseMask;
    constexpr inline u8 Max77620PmicIrqTopSleepMask       = static_cast<u8>(~Max77620PmicIrqTopSleepWakeMask);
    constexpr inline u8 Max77620PmicOnOffIrqSleepMask     = static_cast<u8>(~Max77620PmicOnOffIrqSleepWakeMask);

    /* Wakeup masks */
    constexpr inline u8 Max77620PmicWakeupReasonRtcMask      = BIT(2); /* IRQTOP RTC. */
    constexpr inline u8 Max77620PmicWakeupReasonEn0RiseMask  = BIT(3); /* ONOFFIRQ EN0 rise. */
    constexpr inline u8 Max77620PmicWakeupReasonAcOkFallMask = BIT(4); /* ONOFFIRQ AC-OK fall. */
    constexpr inline u8 Max77620PmicWakeupReasonAcOkRiseMask = BIT(5); /* ONOFFIRQ AC-OK rise. */

}
