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
#include "pcv_clkrst_settings.hpp"
#include "pcv_clkrst_car.hpp"
#include "pcv_clkrst_pll.hpp"
#include "pcv_clkrst_source.hpp"
#include "pcv_clkrst_device_info.hpp"
#include "pcv_clkrst_clock.hpp"

namespace ams::pcv::clkrst {

    namespace {

        uintptr_t g_gpu_mapping{};
        uintptr_t g_fuse_mapping{};

        void InitGpuClockMappings() {
            /* Query gpu mapping. */
            constexpr dd::PhysicalAddress GpuBase = 0x57000000;
            constexpr size_t              GpuSize = 0x1000000;

            g_gpu_mapping = dd::QueryIoMapping(GpuBase, GpuSize);

            AMS_ABORT_UNLESS(g_gpu_mapping != 0);

            /* Query fuse mapping. */
            constexpr dd::PhysicalAddress FuseBase = 0x7000F000;
            constexpr size_t              FuseSize = 0x1000;

            g_fuse_mapping = dd::QueryIoMapping(FuseBase, FuseSize);

            AMS_ABORT_UNLESS(g_fuse_mapping != 0);
            constexpr u32 FuseOffset = 0x800;

            g_fuse_mapping += FuseOffset;
        }

        void SetupUsb2ClkSource() {
            constexpr u32 Usb2Divisor = 6;
            WriteClkReg(CLK_RST_CONTROLLER_CLK_SOURCE_USB2_HSIC_TRK, Usb2Divisor);
        }

        void SetupSataUsbClkSource() {
            constexpr u32 DivisorMask  = 0xFF;
            constexpr u32 RefclkDivBy4 = 6;
            constexpr u32 RefClkEnable = BIT(8);

            u32 reg = ReadCarReg(CLK_RST_CONTROLLER_CLK_SOURCE_PEX_SATA_USB_RX_BYP);

            /* Set the divisor */
            reg &= ~DivisorMask;
            reg |= RefclkDivBy4;

            WriteClkReg(CLK_RST_CONTROLLER_CLK_SOURCE_PEX_SATA_USB_RX_BYP, reg);

            /* Enable the clock */
            WriteClkReg(CLK_RST_CONTROLLER_CLK_SOURCE_PEX_SATA_USB_RX_BYP, reg | RefClkEnable);
        }

        void SetupUartFstMipiCalClkSource() {
            /* Check if it's already running */
            constexpr u32 ClkEnabled = BIT(17);
            if (ReadCarReg(CLK_RST_CONTROLLER_CLK_SOURCE_UART_FST_MIPI_CAL) & ClkEnabled) {
                return;
            }

            constexpr u32 ClkSrcPllpOut0 = BIT(29);
            constexpr u32 DivBy6         = 10;

            /* Enable it */
            WriteClkReg(CLK_RST_CONTROLLER_CLK_SOURCE_UART_FST_MIPI_CAL, ClkSrcPllpOut0 | DivBy6);
        }

        void SetupSpdifInClkSource() {
            /* Once again check if it's enabled */
            constexpr u32 ClkEnabled  = BIT(10);
            constexpr u32 ClkSrcShift = 29;
            constexpr u32 ClkSrcClkM  = 5 << ClkSrcShift;
            constexpr u32 DivBy1      = 0;

            if (ReadCarReg(CLK_RST_CONTROLLER_CLK_SOURCE_SPDIF_IN) & ClkEnabled) {
                return;
            }

            WriteClkReg(CLK_RST_CONTROLLER_CLK_SOURCE_SPDIF_IN, ClkSrcClkM | DivBy1);
        }

        void InitClockSocInfo() {
            /* Setup mappings */
            InitializeCar();

            InitGpuClockMappings();

            SetupUsb2ClkSource();

            bool is_mariko = IsMariko();

            /* Configure tables and adjust max freq. */
            InitializePll(is_mariko);
            InitializeDeviceInfo(is_mariko);

            if (is_mariko) {
                /* Setup clock sources. */
                SetupSataUsbClkSource();
                SetupUartFstMipiCalClkSource();
                SetupSpdifInClkSource();
            }

            /* Reload them. */
            ReloadSourceClocks();
        }

    }

    void InitializeClock() {
        /* NOTE: Nintendo reads various rmos settings here but none of these actually apply to retail. */
        /* In fact all of them are unused except rmos_debug_flag, which isn't even used here and actually just re-read later */
        /* So we will skip this for now. */
        InitClockSocInfo();
    }

}
