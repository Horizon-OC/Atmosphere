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
#include "pcv_rgltr_power_domain.hpp"
#include "pcv_rgltr_control.hpp"
#include "../pcv_device_registry.hpp"
#include "../pcv_hardware_type.hpp"

namespace ams::pcv::rgltr {

    namespace {

        #include "pcv_rgltr_tables.inc"

        constinit Regulator *g_regulator_table = nullptr;
        uintptr_t g_dvfs_mapping;

        constinit PowerDomain g_power_domains[] = {
            { "max77620_sd0",  PcvPowerDomainId_Max77620_Sd0,  },
            { "max77620_sd1",  PcvPowerDomainId_Max77620_Sd1,  },
            { "max77620_sd2",  PcvPowerDomainId_Max77620_Sd2,  },
            { "max77620_sd3",  PcvPowerDomainId_Max77620_Sd3,  },
            { "max77620_ldo0", PcvPowerDomainId_Max77620_Ldo0, },
            { "max77620_ldo1", PcvPowerDomainId_Max77620_Ldo1, },
            { "max77620_ldo2", PcvPowerDomainId_Max77620_Ldo2, },
            { "max77620_ldo3", PcvPowerDomainId_Max77620_Ldo3, },
            { "max77620_ldo4", PcvPowerDomainId_Max77620_Ldo4, },
            { "max77620_ldo5", PcvPowerDomainId_Max77620_Ldo5, },
            { "max77620_ldo6", PcvPowerDomainId_Max77620_Ldo6, },
            { "max77620_ldo7", PcvPowerDomainId_Max77620_Ldo7, },
            { "max77620_ldo8", PcvPowerDomainId_Max77620_Ldo8, },
            { "max77621_cpu",  PcvPowerDomainId_Max77621_Cpu,  },
            { "max77621_gpu",  PcvPowerDomainId_Max77621_Gpu,  },
            { "max77812_cpu",  PcvPowerDomainId_Max77812_Cpu,  },
            { "max77812_gpu",  PcvPowerDomainId_Max77812_Gpu,  },
            { "max77812_dram", PcvPowerDomainId_Max77812_Dram, },
        };
        static_assert(util::size(g_power_domains) == RegulatorCount);

        constexpr size_t PowerDomainTargetCount = 5;
        constinit DeviceRegistry<PowerDomain, RegulatorCount + PowerDomainTargetCount> g_domain_registry;

        bool IsRegulatorPresent(RegulatorVariant regulator_variant, const char *name) {
            const bool is_max77621 = (regulator_variant == RegulatorVariant_Erista_Max77621);

            const char *absent_cpu = is_max77621 ? "max77812_cpu" : "max77621_cpu";
            const char *absent_gpu = is_max77621 ? "max77812_gpu" : "max77621_gpu";

            return std::strcmp(name, absent_cpu) != 0 && std::strcmp(name, absent_gpu) != 0;
        }

        void RegisterPowerDomainTarget(PowerDomain &device) {
            switch (device.GetDeviceCode().GetInternalValue()) {
                case PcvPowerDomainId_Max77620_Ldo3:
                    g_domain_registry.Register(DeviceCode_GcCardPower3v1, std::addressof(device));
                    break;
                case PcvPowerDomainId_Max77620_Ldo5:
                    g_domain_registry.Register(DeviceCode_GcCardPower1v8, std::addressof(device));
                    break;
                case PcvPowerDomainId_Max77620_Ldo6:
                    g_domain_registry.Register(i2c::DeviceCode_I2c2, std::addressof(device));
                    g_domain_registry.Register(i2c::DeviceCode_I2c3, std::addressof(device));
                    break;
                case PcvPowerDomainId_Max77620_Ldo8:
                    g_domain_registry.Register((GetHardwareType() == spl::HardwareType::Hoag) ? DeviceCode_SioMcuPower : DeviceCode_DisplayPortHdmiPower, std::addressof(device));
                    break;
                default:
                    break;
            }
        }

        void QueryDvfsMappings() {
            constexpr dd::PhysicalAddress DvfsBase = 0x70110000;
            constexpr size_t              DvfsSize = 0x400;
            g_dvfs_mapping = dd::QueryIoMapping(DvfsBase, DvfsSize);
        }

        void InitializePowerDomains() {
            const auto regulator_variant = GetRegulatorVariant();

            for (auto &domain : g_power_domains) {
                /* Skip regulators that aren't present */
                if (!IsRegulatorPresent(regulator_variant, domain.GetName())) {
                    continue;
                }

                /* Register the power domain. */
                g_domain_registry.Register(domain.GetDeviceCode(), std::addressof(domain));

                /* Register power domain target. */
                RegisterPowerDomainTarget(domain);
            }
        }

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

            /* Initialize dvfs pmic. */
            if (GetRegulatorVariant() /* == Regulator_Mariko_Max77812_B/A */ ) {
                InitializeMax77812();
            } else {
                InitializeMax77621();
            }
        }

        void InitializePanelVoltage() {
            /* uV */
            constexpr u32 Sd2Voltage  = 1325000;
            constexpr u32 Ldo0Voltage = 1200000;
            constexpr u32 Ldo8Voltage = 2800000;

            /* Needed for Ldo0 and Ldo7 */
            PowerDomain *sd2_domain = g_domain_registry.Find(PcvPowerDomainId_Max77620_Sd2);
            R_ABORT_UNLESS(SetVoltage(sd2_domain, Sd2Voltage));
            R_ABORT_UNLESS(EnablePowerDomain(sd2_domain));

            /* Panel. */
            PowerDomain *ldo0_domain = g_domain_registry.Find(PcvPowerDomainId_Max77620_Ldo0);
            R_ABORT_UNLESS(SetVoltage(ldo0_domain, Ldo0Voltage));
            R_ABORT_UNLESS(EnablePowerDomain(ldo0_domain));

            /* DisplayPort, HDMI, SioMcu */
            if (GetHardwareType() == spl::HardwareType::Hoag) {
                PowerDomain *ldo8_domain = g_domain_registry.Find(PcvPowerDomainId_Max77620_Ldo8);
                R_ABORT_UNLESS(SetVoltage(ldo8_domain, Ldo8Voltage));
                R_ABORT_UNLESS(EnablePowerDomain(ldo8_domain));
            }
        }

        u32 GetRegulatorIdxByDomain(const PowerDomain &domain) {
            const auto idx = std::addressof(domain) - g_power_domains;
            AMS_ABORT_UNLESS(0 <= idx && idx < static_cast<ptrdiff_t>(RegulatorCount));

            return static_cast<u32>(idx);
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

        /* Initialize all power domains. */
        InitializePowerDomains();

        /* Initialize panel voltage. */
        InitializePanelVoltage();
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

    Regulator &GetRegulator(const PowerDomain &domain) {
        return GetRegulator(GetRegulatorIdxByDomain(domain));
    }

    PowerDomain *FindPowerDomain(DeviceCode device_code) {
        return g_domain_registry.Find(device_code);
    }

    uintptr_t GetDvfsMappings() {
        return g_dvfs_mapping;
    }

}
