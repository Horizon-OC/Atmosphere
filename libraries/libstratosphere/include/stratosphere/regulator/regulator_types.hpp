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
#include <vapours.hpp>

namespace ams::pcv::rgltr {

    enum RegulatorVariant : u32 {
        RegulatorVariant_Erista_Max77621   = 0, /* 15A/15A cpu/gpu configuration. */
        RegulatorVariant_Mariko_Max77812_A = 1, /* Prototype, 5A/15A configuration (cpu/gpu). */
        RegulatorVariant_Mariko_Max77812_B = 2, /* Final version, 5/10/5A configuration (cpu/gpu/vddq) */
    };

    struct PowerDomainState {
        DeviceCode device_code;
        bool enabled;
        u8 reserved[3];
        u32 voltage;
    };

    /* Power control targets. */
    constexpr inline const DeviceCode DeviceCode_SdCardPower          = 0x3C000004; /* Ldo2, 1.8V - 3.3V */
    constexpr inline const DeviceCode DeviceCode_GcCardPower3v1       = 0x3C000404; /* Ldo3 */
    constexpr inline const DeviceCode DeviceCode_GcCardPower1v8       = 0x3C000405; /* Ldo5 */
    constexpr inline const DeviceCode DeviceCode_DisplayPortHdmiPower = 0x34000007; /* Ldo8 */
    constexpr inline const DeviceCode DeviceCode_SioMcuPower          = 0x3500041A; /* Ldo8, Max77812_B only */

}
