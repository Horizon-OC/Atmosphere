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
        u32 lock_reg_idx;
        u32 lock_mask;
        u32 sdm_reg_idx;
        u32 sdm_shift;
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

    void InitializePll(bool is_mariko);

    const ClkPllInfo *GetPllInfoTable();

    u32 GetPllPDivider(size_t p);

    u32 CalcFreqFromDivider71(u32 in_khz, u32 div, bool bypass, bool enable);
    u32 CalcFreqShift(u32 in_khz, u32 shift, bool bypass, bool enable);
    u32 CommonDivMN32(u32 in_khz, u32 m, u32 n, bool bypass, bool enable);

    u32 CalcPllFreq(size_t pll_index, u32 ref_khz, u32 m, u32 n, u32 p, bool bypass, bool enable, bool shift_pdiv);
    u32 ReadPllFreq(size_t pll_index, u32 ref_khz, bool use_bypass, bool shift_pdiv);

}
