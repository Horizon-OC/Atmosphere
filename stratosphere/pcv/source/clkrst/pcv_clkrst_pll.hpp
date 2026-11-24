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

    struct ClkPllCfg {
        u32 inHz;
        u32 outHz;
        u32 n;
        u32 m;
        u32 p;
        u32 unk14;
        u32 sdm;
    };
    static_assert(sizeof(ClkPllCfg) == 0x1C);

    struct ClkPllParam {
        u32 max_freq;
        u32 input_min_hz;
        u32 input_max_hz;
        u32 cf_min_hz;
        u32 cf_max_hz;
        u32 vco_min_hz;
        u32 vco_max_hz;
        u32 lock_delay;
        u32 fixed_rate;
        u32 unk_24;
        const ClkPllCfg *cfg;
        u32 cfg_count;
        u32 ref_div;
        u32 misc_init;
        u32 unk_3c;
        u64 setup_fn; /* TODO. */
    };
    static_assert(sizeof(ClkPllParam) == 0x48);

    enum ClkPllType : u32 {
        ClkPllType_Pll    = 0,
        ClkPllType_PllOut = 1,
    };

    struct ClkPllSdm {
        u32 unk_0;
        u32 unk_4;
        u32 unk_8;
        u32 unk_c;
    };
    static_assert(sizeof(ClkPllSdm) == 0x10);

    struct ClkPllInfo {
        const char *name;
        ClkPllType type;
        u32 base_reg;
        u32 misc_reg;
        u32 out_reg;
        u32 unk_18;
        u32 flags;
        u32 bypass_bit;
        u32 enable_bit;
        u32 ref_dis_bit;
        u32 lock_bit;
        u8  unk_30[0x18];
        u32 unk_48;
        u32 p_div_shift;
        u32 p_div_mask;
        u32 n_div_shift;
        u32 n_div_mask;
        u32 m_div_shift;
        u32 m_div_mask;
        u32 unk_64;
        u32 unk_68;
        u32 unk_6C;
        u32 ratio_shift;
        u32 ratio_mask;
        u32 unk_78;
        u32 unk_7C;
        const ClkPllParam *param;
        u32 misc_regs[6];
        u8  unk_a0[8];
        const ClkPllSdm *sdm;
        u8 unk_b0[8];
    };
    static_assert(sizeof(ClkPllInfo) == 0xB8);

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
        const void *source;
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

    const ClkPllInfo *GetPllInfoTable(bool is_mariko);
    ClkSystemInfo *GetClkSystemInfoTable(bool is_mariko);
    const ClkDeviceRegInfo *GetClkDeviceRegInfoTable(bool is_mariko);

    void InitializeDeviceMaxFreqs(bool is_mariko);
    u32 GetDeviceMaxFreqKhz(size_t device_index);

}
