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
#include "pcv_rgltr.hpp"
#include "pcv_rgltr_max77620_init.hpp"
#include "pcv_rgltr_max77621_init.hpp"
#include "pcv_rgltr_max77812_init.hpp"

namespace ams::pcv::rgltr {

    namespace {

        #include "pcv_rgltr_tables.inc"

        constinit Regulator *g_regulator_table = nullptr;
        uintptr_t g_dvfs_mapping;

        u64 GetRegulatorType() {
            static constinit bool cached        = false;
            static constinit u64 regulator_type = 0;

            if (!cached) {
                spl::Initialize();
                R_ABORT_UNLESS(spl::GetConfig(std::addressof(regulator_type), spl::ConfigItem::RegulatorType));
                spl::Finalize();
                cached = true;
            }

            return regulator_type;
        }

        constexpr RegulatorVariant RegulatorVariants[] = {
            RegulatorVariant_Erista_Max77621,
            RegulatorVariant_Mariko_Max77812_A,
            RegulatorVariant_Mariko_Max77812_B,
        };

        void InitializeRegulators() {
            /* Initialize the main pmic. */
            InitializeMax77620();

            if (GetRegulatorVariant() /* == Regulator_Mariko_Max77812_B/A */ ) {
                InitializeMax77812();
            } else {
                InitializeMax77621();
            }
        }

        void QueryDvfsMappings() {
            constexpr dd::PhysicalAddress DvfsBase = 0x70110000;
            constexpr size_t              DvfsSize = 0x400;
            g_dvfs_mapping = dd::QueryIoMapping(DvfsBase, DvfsSize);
        }

    }

    RegulatorVariant GetRegulatorVariant() {
        const u64 type = GetRegulatorType();
        AMS_ABORT_UNLESS(type < util::size(RegulatorVariants));

        return RegulatorVariants[type];
    }

    void Initialize() {
        /* Query dvfs mappings. */
        QueryDvfsMappings();

        /* Initialize all regulators. */
        InitializeRegulators();
    }

    void SetRegulatorTable(u8 cid4) {
        AMS_ABORT_UNLESS(cid4 == Cid4Erista || cid4 == Cid4Mariko);

        if (cid4 == Cid4Erista) {
            g_regulator_table = RegulatorTableErista;
        } else {
            g_regulator_table = RegulatorTableMariko;
        }
    }

    Regulator &GetRegulator(u32 idx) {
        AMS_ABORT_UNLESS(g_regulator_table != nullptr);
        AMS_ABORT_UNLESS(idx < RegulatorCount);

        return g_regulator_table[idx];
    }

}
