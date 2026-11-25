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

namespace ams::pcv::clkrst {

    namespace {

        constinit uintptr_t g_car_mapping = 0;
        constinit uintptr_t g_tmr_mapping = 0;

        constexpr u32 TimerUsCounter = 0x10;

    }

    void InitializeCar() {
        constexpr dd::PhysicalAddress CarBase = 0x60006000;
        constexpr size_t              CarSize = 0x1000;

        g_car_mapping = dd::QueryIoMapping(CarBase, CarSize);
        AMS_ABORT_UNLESS(g_car_mapping != 0);
    }

    u32 ReadCarReg(u32 reg) {
        return reg::Read(g_car_mapping + reg);
    }

    void WriteCarReg(u32 reg, u32 value) {
        reg::Write(g_car_mapping + reg, value);
    }

    void WriteClkReg(u32 reg, u32 value) {
        WriteCarReg(reg, value);
        AMS_UNUSED(ReadCarReg(reg));
        __asm__ __volatile__("dsb st" ::: "memory");
        SleepUs(2);
    }

    void SleepUs(u32 us) {
        if (g_tmr_mapping == 0) {
            constexpr dd::PhysicalAddress TmrBase = 0x60005000;
            constexpr size_t              TmrSize = 0x1000;

            g_tmr_mapping = dd::QueryIoMapping(TmrBase, TmrSize);
            AMS_ABORT_UNLESS(g_tmr_mapping != 0);
        }

        const u32 start = reg::Read(g_tmr_mapping + TimerUsCounter);
        while (reg::Read(g_tmr_mapping + TimerUsCounter) - start <= us) { /* spin. */ }
    }

}
