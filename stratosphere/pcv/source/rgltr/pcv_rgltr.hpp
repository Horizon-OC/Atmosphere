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
#include <stratosphere.hpp>

namespace ams::pcv::rgltr {

    struct __attribute__((packed)) Regulator {
        u64 id;
        const char *name;
        u32 type;

        union {
            struct {
                u32 volt_reg;
                u32 step_uv;
                u32 min_uv;
                u32 default_uv;
                u32 max_uv;
                u32 volt_code;
                u32 unk_0;
            } main_pmic; /* Max77620 */
            struct {
                u32 unk_0;
                u32 step_uv;
                u32 unk_1;
                u32 min_uv;
                u32 max_uv;
                u32 volt_code;
                u32 default_uv;
            } dvfs_pmic; /* TODO: Better name for this */
            /* Max77621/Nax77812^ */
            /* Responsible for cpu, gpu and on mariko vddq. */
        };

        struct {
            u8 volt_reg_byte;
            u8 config_reg;
            u8 voltage_mask;
            u8 enable_mask;
            u8 enable_shift;
            u8 pad_35[3];
            u8 fps_reg;
            u8 pad_39[3];
            u32 unk_3c;
            u32 unk_40;
            u8 enable_value;
            u8 enabled_state;
            u8 pad_46[10];
            u32 unk_50;
            u32 unk_54;
            u32 is_ldo;
            u32 ramp_div_up;
            u32 enable_delay_ms;
            u32 unk_64;
            u32 unk_68;
            u8 ramp_bit;
            u8 pad_6d[1];
            u8 forced_on;
            u8 pad_6f[1];
            u32 fps_src;
            u32 fps_pd_period;
            u32 fps_pu_period;
            u32 ramp_div;
            u8 is_open;
            u8 is_initialized;
            u8 pad_82[2];
            s32 ref_count;
            u8 reg2_init;
            u8 reg3_init;
            u8 pad_8a[6];
            i2c::I2cSession *session;
            u32 i2c_device_code;
            u8 pad_9c[4];
            const char *gpio_name;
            u32 enable_count;
            u32 always_on;
            u32 pmc_mask;
            u32 pmc_bit;
            u8 pad_b8[73];
            u8 use_vout_d;
            u8 master_en_mask;
            u8 lpm_mask;
            u8 shdn_dly_reg;
            u8 pokn_mask;
            u8 pokn_int_mask;
            u8 vout_reg;
            u8 vout_d_reg;
            u8 vout_s_reg;
            u8 master_cfg_reg;
            u8 pad_10b[5];
            u32 dvfs_idx;
            u32 selected_master;
            u64 pmc_mmio;
        };
    };
    static_assert(sizeof(Regulator) == 0x120);

    struct Max77620InitReg {
        u8 reg;
        u8 time_period;
        u8 en_src;
        u8 sw_enable;
    };

    enum RegulatorVariant : u32 {
        RegulatorVariant_Erista_Max77621   = 0, /* 15A/15A cpu/gpu configuration. */
        RegulatorVariant_Mariko_Max77812_A = 1, /* Prototype, 5A/15A configuration (cpu/gpu). */
        RegulatorVariant_Mariko_Max77812_B = 2, /* Final version, 5/10/5A configuration (cpu/gpu/vddq) */
    };

    constexpr inline size_t RegulatorCount = 18;

    void Initialize();
    void SetRegulatorTable(u8 cid4);
    Regulator &GetRegulator(u32 idx);
    RegulatorVariant GetRegulatorVariant();

    constexpr u32 Cid4Erista = 0x35;
    constexpr u32 Cid4Mariko = 0x53;

}
