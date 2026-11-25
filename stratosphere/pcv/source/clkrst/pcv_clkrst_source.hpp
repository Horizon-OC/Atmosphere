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

namespace ams::pcv::clkrst {

    enum ClkSourceId : u32 {
        ClkSourceId_Invalid,
        ClkSourceId_Osc,
        ClkSourceId_ClkS,
        ClkSourceId_ClkM,
        ClkSourceId_PllA0,
        ClkSourceId_PllA,
        ClkSourceId_PllA1,
        ClkSourceId_PllC0,
        ClkSourceId_PllC1,
        ClkSourceId_PllC2,
        ClkSourceId_PllC3,
        ClkSourceId_PllC40,
        ClkSourceId_PllC41,
        ClkSourceId_PllC42,
        ClkSourceId_PllC43,
        ClkSourceId_PllD0,
        ClkSourceId_PllD2,
        ClkSourceId_PllDP,
        ClkSourceId_PllE0,
        ClkSourceId_PllM,
        ClkSourceId_PllMB,
        ClkSourceId_PllP0,
        ClkSourceId_PllP2,
        ClkSourceId_PllP3,
        ClkSourceId_PllP4,
        ClkSourceId_PllP5,
        ClkSourceId_PllPaux,
        ClkSourceId_PllREFEv,
        ClkSourceId_PllREFE0,
        ClkSourceId_PllREFE1,
        ClkSourceId_PllUv,
        ClkSourceId_PllU0,
        ClkSourceId_PllU1,
        ClkSourceId_PllU2,
        ClkSourceId_PllX0,
        ClkSourceId_UtmiPll,
        ClkSourceId_CpuBus,
        ClkSourceId_SystemBus,
        ClkSourceId_Ahb,
        ClkSourceId_Apb,
        ClkSourceId_Aclk,
        ClkSourceId_Mclk,
        ClkSourceId_PllRef,
        ClkSourceId_DvfsClk,
        ClkSourceId_Gpu,
        ClkSourceId_UsbTrk,
        ClkSourceId_UphyMgmt,
        ClkSourceId_Count,
    };

    struct ClkSourceNode {
        ClkSourceId id;
        const char *name;
        const char *parent_name;
        u32  last_freq_khz;
        u32  freq_khz;
        u64  unk_20;
    };

    extern ClkSourceNode g_clk_source_node_table[ClkSourceId_Count];

    ClkSourceNode &GetSourceNode(ClkSourceId id);

    void SetNodeFreq(ClkSourceId id, u32 khz);
    u32  GetNodeFreq(ClkSourceId id);

    void ReloadSourceClocks();

}
