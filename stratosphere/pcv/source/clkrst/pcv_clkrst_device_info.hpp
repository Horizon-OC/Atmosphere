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
#include "pcv_clkrst_source.hpp"

namespace ams::pcv::clkrst {

    enum ClkSystemInfoType : u32 {
        ClkSystemInfoType_Sclk,
        ClkSystemInfoType_Cclk,
        ClkSystemInfoType_Hclk,
        ClkSystemInfoType_Pclk,
        ClkSystemInfoType_Emc,
        ClkSystemInfoType_Aclk,
    };

    struct ClkSystemInfo {
        const char *name;
        ClkSystemInfoType type;
        u32 source_id;
        ClkSourceNode *source;
        u32 max_freq_khz;
        u32 unk_1C;
        const char *unk_20;
        void *dvfs;
    };
    static_assert(sizeof(ClkSystemInfo) == 0x30);

    enum ClkDivType : u32 {
        ClkDivType_None       = 0,
        ClkDivType_Fractional = 1, /* 8 bit 7.1 divider */
        ClkDivType_Uart       = 2, /* UARTA-D, UARTAPE */
        ClkDivType_Integer16  = 3, /* I2C1-6, 16 bit */
        ClkDivType_Unk5       = 5, /* 8 bit */
    };

    struct ClkDeviceRegInfo {
        const char *name;
        u32 unk_08;
        u32 flags;
        u32 clk_source_reg;
        u32 mux_mask;
        u32 mux_shift;
        u32 div_mask;
        u32 div_shift;
        u8  unk_24[8];
        ClkDivType div_type;
        u32 rst_set_reg;
        u32 rst_clr_reg;
        u32 clk_enb_set_reg;
        u32 clk_enb_clr_reg;
        u32 bank_bit;
        u32 max_freq_khz;
        u32 parent_ids[8];
        const char *gate_clock_name;
        u32 unk_c8[10];
    };

    void InitializeDeviceInfo(bool is_mariko);

    ClkSystemInfo          *GetClkSystemInfoTable();
    const ClkDeviceRegInfo *GetClkDeviceRegInfoTable();

    u32 GetDeviceMaxFreqKhz(size_t device_index);

}
