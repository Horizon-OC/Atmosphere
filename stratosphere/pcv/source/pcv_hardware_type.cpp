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
#include "pcv_hardware_type.hpp"

namespace ams::pcv {

    spl::HardwareType GetHardwareType() {
        static constinit bool cached       = false;
        static constinit u64 hardware_type = 0;

        if (!cached) {
            spl::Initialize();
            R_ABORT_UNLESS(spl::GetConfig(std::addressof(hardware_type), spl::ConfigItem::HardwareType));
            spl::Finalize();
            cached = true;
        }

        return static_cast<spl::HardwareType>(hardware_type);
    }

    bool IsMariko() {
        return GetHardwareType() >= spl::HardwareType::Hoag;
    }

    namespace clkrst {

        namespace {

            constinit BoardInfo g_board_info_table[] = {
                /* Copper */
                {
                    .code_name         = "nx-abcb", /* Unk */
                    .form_factor       = FormFactor_Console,
                    .regulator_variant = rgltr::RegulatorVariant_Erista_Max77621,
                }, {
                    /* Unk */
                    .code_name         = "nx-abca2", /* nx-odin */
                    .form_factor       = FormFactor_Standard,
                    .regulator_variant = rgltr::RegulatorVariant_Erista_Max77621,
                }, {
                    /* Calcio. */
                    .code_name         = "nx-abcb", /* Unk */
                    .form_factor       = FormFactor_Console,
                    .regulator_variant = rgltr::RegulatorVariant_Mariko_Max77812_B,
                }, {
                    /* Hoag */
                    .code_name         = "nx-abcc", /* nx-vali */
                    .form_factor       = FormFactor_Handheld,
                    .regulator_variant = rgltr::RegulatorVariant_Mariko_Max77812_B,
                }, {
                    /* Aula */
                    .code_name         = "nx-abcd", /* nx-fric */
                    .form_factor       = FormFactor_Standard,
                    .regulator_variant = rgltr::RegulatorVariant_Mariko_Max77812_B,
                }, {
                    /* Iowa */
                    .code_name         = "nx-abca2", /* nx-odin2/Modin */
                    .form_factor       = FormFactor_Standard,
                    .regulator_variant = rgltr::RegulatorVariant_Mariko_Max77812_B,
                }, {
                    /* Calcio */
                    .code_name         = "nx-abcb", /* ? */
                    .form_factor       = FormFactor_Console,
                    .regulator_variant = rgltr::RegulatorVariant_Mariko_Max77812_A,
                }, {
                    .code_name         = "nx-abcc", /* nx-vali */
                    .form_factor       = FormFactor_Handheld,
                    .regulator_variant = rgltr::RegulatorVariant_Mariko_Max77812_A,
                }, {
                    .code_name         = "nx-abcd", /* nx-fric */
                    .form_factor       = FormFactor_Standard,
                    .regulator_variant = rgltr::RegulatorVariant_Mariko_Max77812_A,
                }, {
                    /* Iowa */
                    .code_name         = "nx-abca2", /* nx-odin2 */
                    .form_factor       = FormFactor_Standard,
                    .regulator_variant = rgltr::RegulatorVariant_Mariko_Max77812_A,
                },
            };

            u32 GetHidRev() {
                constexpr dd::PhysicalAddress AbpBase = 0x70000000;
                constexpr size_t              AbpSize = 0x1000;

                const uintptr_t virt_address = dd::QueryIoMapping(AbpBase, AbpSize);
                AMS_ABORT_UNLESS(virt_address != 0);

                constexpr u32 HidRevOffset = 0x804;
                u32 hid_rev = reg::Read(virt_address + HidRevOffset);

                constexpr u32 MajorRevMask  = 0xf;
                constexpr u32 MajorRevShift = 4;

                return (hid_rev >> MajorRevShift) & MajorRevMask;
            }

            BoardInfo g_board_info;

            inline u64 GetRegulatorType() {
                spl::Initialize();

                u64 type;
                R_ABORT_UNLESS(spl::GetConfig(std::addressof(type), spl::ConfigItem::RegulatorType));
                spl::Finalize();

                return type;
            }

            BoardInfo GetMarikoBoardInfo(spl::HardwareType type) {
                if (GetRegulatorType() == 2) {
                    switch (type) {
                        case spl::HardwareType::Iowa:   return g_board_info_table[5];
                        case spl::HardwareType::Calcio: return g_board_info_table[2];
                        case spl::HardwareType::Hoag:   return g_board_info_table[3];
                        case spl::HardwareType::Aula:   return g_board_info_table[4];
                        AMS_UNREACHABLE_DEFAULT_CASE();
                    }
                } else {
                    switch (type) {
                        case spl::HardwareType::Iowa:   return g_board_info_table[9];
                        case spl::HardwareType::Calcio: return g_board_info_table[6];
                        case spl::HardwareType::Hoag:   return g_board_info_table[7];
                        case spl::HardwareType::Aula:   return g_board_info_table[8];
                        AMS_UNREACHABLE_DEFAULT_CASE();
                    }
                }
            }

        }

        BoardInfo &GetBoardInfo() {
            static constinit bool initialized = false;
            if (!initialized) {
                /* Read out the hidrev */
                constexpr u32 HidMajorRevT210B0 = 0x2;
                if (GetHidRev() >= HidMajorRevT210B0) {
                    g_board_info = GetMarikoBoardInfo(GetHardwareType());
                } else /* Erista. */ {
                    g_board_info = GetHardwareType() == spl::HardwareType::Copper ? g_board_info_table[0] : g_board_info_table[1];
                }

                initialized = true;
            }

            return g_board_info;
        }

    }

}
