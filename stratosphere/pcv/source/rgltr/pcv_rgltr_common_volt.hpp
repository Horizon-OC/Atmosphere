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

    ALWAYS_INLINE bool IsVoltageInRange(u32 voltage, u32 min_uv, u32 max_uv) {
        return min_uv <= voltage && voltage <= max_uv;
    }

    ALWAYS_INLINE u32 GetVoltCodeImpl(u32 voltage, u32 min_uv, u32 step_uv) {
        return util::DivideUp(voltage - min_uv, step_uv);
    }

    ALWAYS_INLINE u32 GetVoltageFromCodeImpl(u8 volt_code, u32 min_uv, u32 step_uv) {
        return volt_code * step_uv + min_uv;
    }

    ALWAYS_INLINE u32 GetVoltCodeDelta(u32 old_code, u32 new_code) {
        return static_cast<u32>(std::abs(static_cast<s32>(old_code) - static_cast<s32>(new_code)));
    }

    ALWAYS_INLINE void SleepForRamp(u32 delay_us) {
        if (delay_us >= 1) {
            svc::SleepThread(static_cast<s64>(1000) * delay_us);
        }
    }

}
