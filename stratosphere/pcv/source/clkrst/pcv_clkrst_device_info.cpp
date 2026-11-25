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
#include "pcv_clkrst_table_util.hpp"
#include "pcv_clkrst_device_info.hpp"

namespace ams::pcv::clkrst {

    namespace {

        #include "pcv_clkrst_device_info_data.inc"

        static_assert(std::size(ClkDeviceRegInfoTableT210) == std::size(ClkDeviceRegInfoTableT210B01));

        constexpr size_t Sor1DeviceIndex = FindIndexByName(ClkDeviceRegInfoTableT210, "SOR1");
        static_assert(Sor1DeviceIndex < std::size(ClkDeviceRegInfoTableT210));
        static_assert(Sor1DeviceIndex == FindIndexByName(ClkDeviceRegInfoTableT210B01, "SOR1"));

        constinit u32 g_device_max_freq_khz[std::size(ClkDeviceRegInfoTableT210)] = {};

        inline bool UsesSor1Dp(const BoardInfo &board) {
            return board.form_factor == FormFactor_Standard;
        }

        constinit ClkSystemInfo          *g_clk_system_info_table     = nullptr;
        constinit const ClkDeviceRegInfo *g_clk_device_reg_info_table = nullptr;

    }

    ClkSystemInfo *GetClkSystemInfoTable() {
        return g_clk_system_info_table;
    }

    const ClkDeviceRegInfo *GetClkDeviceRegInfoTable() {
        return g_clk_device_reg_info_table;
    }

    void InitializeDeviceInfo(bool is_mariko) {
        g_clk_system_info_table     = is_mariko ? ClkSystemInfoTableT210B01     : ClkSystemInfoTableT210;
        g_clk_device_reg_info_table = is_mariko ? ClkDeviceRegInfoTableT210B01  : ClkDeviceRegInfoTableT210;

        /* Apply max frequencies. */
        const ClkDeviceRegInfo *table = g_clk_device_reg_info_table;

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
