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
#include "../pcv_hardware_type.hpp"
#include "pcv_clkrst_pll.hpp"

namespace ams::pcv::clkrst {

    namespace {

        #include "pcv_clkrst_pll_data.inc"

        template<size_t N>
        consteval size_t FindDeviceRegInfoIndex(const ClkDeviceRegInfo (&table)[N], std::string_view name) {
            for (size_t i = 0; i < N; ++i) {
                if (std::string_view(table[i].name) == name) {
                    return i;
                }
            }

            return N;
        }

        static_assert(std::size(ClkDeviceRegInfoTableT210) == std::size(ClkDeviceRegInfoTableT210B01));

        constexpr size_t Sor1DeviceIndex = FindDeviceRegInfoIndex(ClkDeviceRegInfoTableT210, "SOR1");
        static_assert(Sor1DeviceIndex < std::size(ClkDeviceRegInfoTableT210));
        static_assert(Sor1DeviceIndex == FindDeviceRegInfoIndex(ClkDeviceRegInfoTableT210B01, "SOR1"));

        constinit u32 g_device_max_freq_khz[std::size(ClkDeviceRegInfoTableT210)] = {};

        inline bool UsesSor1Dp(const BoardInfo &board) {
            return board.form_factor == FormFactor_Standard;
        }

    }

    const ClkPllInfo *GetPllInfoTable(bool is_mariko) {
        if (is_mariko) {
            return PllInfoTableT210B01;
        } else {
            return PllInfoTableT210;
        }
    }

    ClkSystemInfo *GetClkSystemInfoTable(bool is_mariko) {
        if (is_mariko) {
            return ClkSystemInfoTableT210B01;
        } else {
            return ClkSystemInfoTableT210;
        }
    }

    const ClkDeviceRegInfo *GetClkDeviceRegInfoTable(bool is_mariko) {
        if (is_mariko) {
            return ClkDeviceRegInfoTableT210B01;
        } else {
            return ClkDeviceRegInfoTableT210;
        }
    }

    void InitializeDeviceMaxFreqs(bool is_mariko) {
        const ClkDeviceRegInfo *table = GetClkDeviceRegInfoTable(is_mariko);

        for (size_t i = 0; i < std::size(g_device_max_freq_khz); ++i) {
            g_device_max_freq_khz[i] = table[i].max_freq_khz;
        }

        constexpr u32 Sor1DpMaxFreqKhz = 540000;

        /* Lite, calcio and copper use dp, so a lower freq is needed. */
        if (UsesSor1Dp(GetBoardInfo())) {
            g_device_max_freq_khz[Sor1DeviceIndex] = std::min(g_device_max_freq_khz[Sor1DeviceIndex], Sor1DpMaxFreqKhz);
        }
    }

    u32 GetDeviceMaxFreqKhz(size_t device_index) {
        AMS_ABORT_UNLESS(device_index < std::size(g_device_max_freq_khz));

        return g_device_max_freq_khz[device_index];
    }

}
