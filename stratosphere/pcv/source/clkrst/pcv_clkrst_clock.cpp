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
#include "pcv_clkrst_settings.hpp"

namespace ams::pcv::clkrst {

    namespace {

        uintptr_t g_car_mapping{};
        uintptr_t g_gpu_mapping{};
        uintptr_t g_fuse_mapping{};

        void MapCar() {
            constexpr dd::PhysicalAddress CarBase = 0x60006000;
            constexpr size_t              CarSize = 0x1000;

            g_car_mapping = dd::QueryIoMapping(CarBase, CarSize);

            AMS_ABORT_UNLESS(g_car_mapping != 0);
        }

        inline void WriteCarReg(u32 reg, u32 value) {
            reg::Write(g_car_mapping + reg, value);
        }

        inline u32 ReadCarReg(u32 reg) {
            return reg::Read(g_car_mapping + reg);
        }

        /* TODO: Mmove some of these into more generic util files. */
        void SleepUs(u32 us) {
            static constinit uintptr_t tmr_mapping{};
            if (tmr_mapping == 0) {
                constexpr dd::PhysicalAddress TmrBase = 0x60005000;
                constexpr size_t              TmrSize = 0x1000;

                tmr_mapping = dd::QueryIoMapping(TmrBase, TmrSize);
                AMS_ABORT_UNLESS(tmr_mapping != 0);
            }

            constexpr u32 TimerUsCounter = 0x10;
            const u32 start = reg::Read(tmr_mapping + TimerUsCounter);
            while (reg::Read(tmr_mapping + TimerUsCounter) - start <= us) { /* spin. */ }
        }

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

        void SetUsb2ClkSource() {
            constexpr u32 Usb2Divisor = 6;

            WriteCarReg(CLK_RST_CONTROLLER_CLK_SOURCE_USB2_HSIC_TRK, Usb2Divisor);
            AMS_UNUSED(ReadCarReg(CLK_RST_CONTROLLER_CLK_SOURCE_USB2_HSIC_TRK));

            __asm__ __volatile__("dsb st" ::: "memory");

            SleepUs(2);
        }

        void InitClockSocInfo() {
            /* Setup mappings */
            MapCar();

            InitGpuClockMappings();

            SetUsb2ClkSource();
        }

    }

    void InitializeClock() {
        /* NOTE: Nintendo reads various rmos settings here but none of these actually apply to retail. */
        /* In fact all of them are unused except rmos_debug_flag, which isn't even used here and actually just re-read later */
        /* So we will skip this for now. */
        InitClockSocInfo();
    }

}
