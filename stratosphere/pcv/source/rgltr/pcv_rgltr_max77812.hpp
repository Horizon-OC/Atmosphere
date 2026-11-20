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

    struct Slew {
        u32 start_per_us;
        u32 shdn_per_us;
        u32 ramp_up_per_us;
        u32 ramp_down_per_us;
    };

    Result SetVoltageMax77812Reg(u32 idx, u32 micro_volts, u8 reg);
    Result GetVoltageMax77812(u32 idx, u32 &out_micro_volts);
    u32 GetCachedVoltageDvfsPmic(u32 idx);
    void GetVoltageRangeDvfsPmic(u32 idx, u32 &min_uv, u32 &max_uv, u32 &step_uv);
    Result EnableMax77812(u32 idx);
    Result IsEnabledMax77812(u32 idx, bool &enabled);
    Result DisableMax77812(u32 idx);
    bool FinalizeMax77812(u32 idx);

    Slew &GetSlew();

}
