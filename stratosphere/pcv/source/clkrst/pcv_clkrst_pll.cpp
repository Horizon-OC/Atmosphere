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
#include <stratosphere.hpp>
#include "pcv_clkrst_car.hpp"
#include "pcv_clkrst_pll_data.hpp"

namespace ams::pcv::clkrst {

    namespace {

        constinit const ClkPllInfo *g_clk_pll_info_table = nullptr;

        constinit u8 g_pll_div_table[] = { 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20, 24, 30, 32, };
        static_assert(sizeof(g_pll_div_table) == 17);

        constexpr u8 PllDivTablePow2[] = { 1, 2, 4, 8, 16, 32, 64, 128, 4, };

        constexpr u32 SdmShift = 13;
        constexpr u32 SdmRound = 4096;

    }

    void InitializePll(bool is_mariko) {
        g_clk_pll_info_table = is_mariko ? impl::PllInfoTableT210B01 : impl::PllInfoTableT210;

        g_pll_div_table[std::size(g_pll_div_table) - 1] = is_mariko ? 31 : 32;
    }

    const ClkPllInfo *GetPllInfoTable() {
        return g_clk_pll_info_table;
    }

    u32 GetPllPDivider(size_t p) {
        AMS_ABORT_UNLESS(p < std::size(g_pll_div_table));
        return g_pll_div_table[p];
    }

    u32 CalcFreqFromDivider71(u32 in_khz, u32 div, bool bypass, bool enable) {
        if (bypass) {
            return in_khz;
        }

        if (!enable) {
            return 0;
        }

        return static_cast<u32>((2 * static_cast<u64>(in_khz)) / (div + 2));
    }

    u32 CalcFreqShift(u32 in_khz, u32 shift, bool bypass, bool enable) {
        if (bypass) {
            return in_khz;
        }

        if (!enable) {
            return 0;
        }

        return in_khz >> shift;
    }

    u32 CommonDivMN32(u32 in_khz, u32 m, u32 n, bool bypass, bool enable) {
        if (bypass) {
            return in_khz;
        }

        if (!enable || m == 0 || n == 0) {
            return 0;
        }

        if (m > n) {
            return in_khz;
        }

        return m * in_khz / n;
    }

    u32 CalcPllFreq(size_t pll_index, u32 ref_khz, u32 m, u32 n, u32 p, bool bypass, bool enable, bool shift_pdiv) {
        AMS_ABORT_UNLESS(pll_index < std::size(impl::PllInfoTableT210));

        if (bypass) {
            return ref_khz;
        }

        if (!enable || m == 0 || n == 0) {
            return 0;
        }

        const ClkPllInfo &info = g_clk_pll_info_table[pll_index];

        if (const ClkPllSdm *sdm = info.sdm; sdm != nullptr && (sdm->lock_mask & ~ReadCarReg(info.misc_regs[sdm->lock_reg_idx])) == 0) {
            AMS_ABORT_UNLESS(p < (shift_pdiv ? std::size(PllDivTablePow2) : std::size(g_pll_div_table)));

            const u32 m_pdiv   = (m * (shift_pdiv ? PllDivTablePow2[p] : g_pll_div_table[p])) << SdmShift;
            const s32 sdm_frac = static_cast<s16>(ReadCarReg(info.misc_regs[sdm->sdm_reg_idx]) >> sdm->sdm_shift);
            const u32 numer    = static_cast<u32>(sdm_frac) + (n << SdmShift) + SdmRound;

            return static_cast<u32>((m_pdiv + static_cast<u64>(numer) * ref_khz - 1) / m_pdiv);
        }

        const u32 pre_div = ref_khz / m * n;

        if (shift_pdiv) {
            return pre_div >> p;
        }

        return pre_div / GetPllPDivider(p);
    }

    u32 ReadPllFreq(size_t pll_index, u32 ref_khz, bool use_bypass, bool shift_pdiv) {
        const ClkPllInfo &info = g_clk_pll_info_table[pll_index];
        const u32 reg = ReadCarReg(info.base_reg);

        const u32 m = (reg & info.m_div_mask) >> info.m_div_shift;
        const u32 n = (reg & info.n_div_mask) >> info.n_div_shift;
        const u32 p = (reg & info.p_div_mask) >> info.p_div_shift;

        const bool bypass = use_bypass && ((reg & (1u << info.bypass_bit)) != 0);
        const bool enable = (reg & (1u << info.enable_bit)) != 0;

        return CalcPllFreq(pll_index, ref_khz, m, n, p, bypass, enable, shift_pdiv);
    }

}
