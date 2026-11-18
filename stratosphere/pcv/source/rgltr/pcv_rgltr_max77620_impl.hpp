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
#include "pcv_rgltr.hpp"

namespace ams::pcv::rgltr::max77620 {

    /* FPS (flexible power sequencer) sources. */
    constexpr inline u32 FpsSourceCount = 4;
    constexpr inline u32 FpsSourceNone  = 3;
    constexpr inline u32 FpsSourceNoOp  = 5;

    constexpr inline u32 EnabledRegulator = 3;
    constexpr inline u32 InvalidRegulator = 4;

    Result ReadEnabledRegister(u32 idx, u32 *enabled);
    Result WriteEnabledRegister(u32 idx, u8 enabled);

    void SetPmcNoIoPowerBit(const Regulator &regulator);
    void ClearPmcNoIoPowerBit(const Regulator &regulator);

}
