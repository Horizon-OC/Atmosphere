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

constinit Regulator RegulatorTableErista[RegulatorCount] = {
    /* Soc. */
    { 0, "max77620_sd0", 1,
    { .main_pmic = { .volt_reg = 22, .step_uv = 12500, .min_uv = 600000, .default_uv = 625000, .max_uv = 1400000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x16, .config_reg = 0x1D, .voltage_mask = 0x3F, .enable_mask = 0x30, .enable_shift = 0x4, .fps_reg = 0x4F, .unk_3c = 0x4, .unk_40 = 0x1, .unk_50 = 0x1, .enable_delay_us = 50, .disable_delay_us = 4080, .unk_68 = 0x80, .ramp_bit = 0x1, .fps_src = 0x1, .fps_pd_period = 0x7, .fps_pu_period = 0x1, .ramp_div = 0x6B6C, .always_on = 0x1 } },
    /* Vdd2. */
    { 1, "max77620_sd1", 1,
    { .main_pmic = { .volt_reg = 23, .step_uv = 12500, .min_uv = 600000, .default_uv = 1125000, .max_uv = 1125000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x17, .config_reg = 0x1E, .voltage_mask = 0x3F, .enable_mask = 0x30, .enable_shift = 0x4, .fps_reg = 0x50, .unk_3c = 0x4, .unk_40 = 0x1, .unk_50 = 0x1, .enable_delay_us = 1000, .disable_delay_us = 145800, .unk_68 = 0x40, .ramp_bit = 0x1, .fps_pd_period = 0x1, .fps_pu_period = 0x5, .ramp_div = 0x6B6C, .always_on = 0x1, .pmc_mask = 0x1 } },
    /* Supply for ldo{0-1,7-8}. */
    { 2, "max77620_sd2", 1,
    { .main_pmic = { .volt_reg = 24, .step_uv = 12500, .min_uv = 600000, .default_uv = 1325000, .max_uv = 1350000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x18, .config_reg = 0x1F, .voltage_mask = 0xFF, .enable_mask = 0x30, .enable_shift = 0x4, .fps_reg = 0x51, .unk_3c = 0x4, .unk_40 = 0x1, .unk_50 = 0x1, .enable_delay_us = 50, .disable_delay_us = 32000, .unk_68 = 0x20, .ramp_bit = 0x1, .fps_src = 0x1, .fps_pd_period = 0x5, .fps_pu_period = 0x2, .ramp_div = 0x6B6C } },
    /* 1.8V general. */
    { 3, "max77620_sd3", 1,
    { .main_pmic = { .volt_reg = 25, .step_uv = 12500, .min_uv = 600000, .default_uv = 1800000, .max_uv = 1800000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x19, .config_reg = 0x20, .voltage_mask = 0xFF, .enable_mask = 0x30, .enable_shift = 0x4, .fps_reg = 0x52, .unk_3c = 0x4, .unk_40 = 0x1, .unk_50 = 0x1, .enable_delay_us = 50, .disable_delay_us = 118000, .unk_68 = 0x10, .ramp_bit = 0x1, .fps_pd_period = 0x3, .fps_pu_period = 0x3, .ramp_div = 0x6B6C, .always_on = 0x1 } },
    /* Display panel. */
    { 4, "max77620_ldo0", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 25000, .min_uv = 800000, .default_uv = 1200000, .max_uv = 1200000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x23, .config_reg = 0x24, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x46, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 50, .disable_delay_us = 4000, .fps_src = 0x3, .fps_pd_period = 0x7, .ramp_div = 0xC350, .pmc_bit = 0x200 } },
    /* XUSB, PCIE. */
    { 5, "max77620_ldo1", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 25000, .min_uv = 800000, .default_uv = 1050000, .max_uv = 1050000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x25, .config_reg = 0x26, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x47, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 50, .disable_delay_us = 6000, .fps_src = 0x3, .fps_pd_period = 0x7, .ramp_div = 0xC350 } },
    /* SDMMC1. */
    { 6, "max77620_ldo2", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 1800000, .max_uv = 3300000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x27, .config_reg = 0x28, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x48, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 100, .disable_delay_us = 7000, .fps_src = 0x3, .fps_pd_period = 0x7, .ramp_div = 0xC350 } },
    /* GC ASIC. */
    { 7, "max77620_ldo3", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 3100000, .max_uv = 3100000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x29, .config_reg = 0x2A, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x49, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 100, .disable_delay_us = 3000, .fps_src = 0x3, .fps_pd_period = 0x7, .ramp_div = 0xC350 } },
    /* RTC, AO. */
    { 8, "max77620_ldo4", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 12500, .min_uv = 800000, .default_uv = 850000, .max_uv = 850000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x2B, .config_reg = 0x2C, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4A, .unk_3c = 0x4, .unk_40 = 0x1, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 50, .disable_delay_us = 610, .fps_pd_period = 0x7, .fps_pu_period = 0x1, .ramp_div = 0xC350, .always_on = 0x1, .pmc_mask = 0x1 } },
    /* GC card. */
    { 9, "max77620_ldo5", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 1800000, .max_uv = 1800000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x2D, .config_reg = 0x2E, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4B, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 60, .disable_delay_us = 3000, .fps_src = 0x3, .fps_pd_period = 0x7, .ramp_div = 0xC350 } },
    /* Touch, ALS. */
    { 10, "max77620_ldo6", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 2900000, .max_uv = 2900000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x2F, .config_reg = 0x30, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4C, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 100, .disable_delay_us = 3000, .fps_src = 0x3, .fps_pd_period = 0x7, .ramp_div = 0xC350 } },
    /* XUSB. */
    { 11, "max77620_ldo7", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 1050000, .max_uv = 1050000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x31, .config_reg = 0x32, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4D, .unk_3c = 0x4, .unk_40 = 0x1, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 50, .disable_delay_us = 2768, .fps_src = 0x1, .fps_pd_period = 0x4, .fps_pu_period = 0x3, .ramp_div = 0xC350, .always_on = 0x1 } },
    /* XUSB, DP, MCU. */
    { 12, "max77620_ldo8", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 1050000, .max_uv = 1050000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x33, .config_reg = 0x34, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4E, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 100, .disable_delay_us = 4000, .fps_src = 0x3, .fps_pd_period = 0x7, .ramp_div = 0xC350 } },
    /* Cpu. */
    { 13, "max77621_cpu", 2,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 6250, .unk_1 = 0, .min_uv = 618750, .max_uv = 1175000, .volt_code = 0, .default_uv = 1000000 } },
    { .unk_50 = 0x1, .ramp_rate_uv_per_us = 12000, .enable_delay_us = 500, .disable_delay_us = 60000, .ctrl_reg1 = 0xB0, .ctrl_reg2 = 0xC2, .i2c_device_code = 0x3A000003, .gpio_name = "max77620_gpio5", .always_on = 0x1 } },
    /* Gpu. */
    { 14, "max77621_gpu", 2,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 6250, .unk_1 = 0, .min_uv = 618750, .max_uv = 1150000, .volt_code = 0, .default_uv = 1000000 } },
    { .unk_50 = 0x1, .ramp_rate_uv_per_us = 12000, .enable_delay_us = 500, .disable_delay_us = 60000, .ctrl_reg1 = 0xB0, .ctrl_reg2 = 0xC2, .i2c_device_code = 0x3A000004, .gpio_name = "max77620_gpio6" } },
    /* Cpu. */
    { 0, "max77812_cpu", 3,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 5000, .unk_1 = 0, .min_uv = 250000, .max_uv = 1525000, .volt_code = 0, .default_uv = 1000000 } },
    { .unk_50 = 0x1, .unk_54 = 0x2, .always_on = 0x1, .dvfs_idx = 0 } },
    /* Gpu. */
    { 1, "max77812_gpu", 3,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 5000, .unk_1 = 0, .min_uv = 250000, .max_uv = 1525000, .volt_code = 0, .default_uv = 800000 } },
    { .unk_50 = 0x1, .unk_54 = 0x2, .dvfs_idx = 0x1 } },
    /* Vddq. */
    { 2, "max77812_dram", 3,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 5000, .unk_1 = 0, .min_uv = 250000, .max_uv = 1525000, .volt_code = 0, .default_uv = 600000 } },
    { .unk_50 = 0x1, .unk_54 = 0x2, .always_on = 0x1, .dvfs_idx = 0x2 } },
};

constinit Regulator RegulatorTableMariko[RegulatorCount] = {
    /* Soc. */
    { 0, "max77620_sd0", 1,
    { .main_pmic = { .volt_reg = 22, .step_uv = 12500, .min_uv = 600000, .default_uv = 625000, .max_uv = 1400000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x16, .config_reg = 0x1D, .voltage_mask = 0x3F, .enable_mask = 0x30, .enable_shift = 0x4, .fps_reg = 0x4F, .unk_3c = 0x4, .unk_50 = 0x1, .enable_delay_us = 50, .disable_delay_us = 4080, .unk_68 = 0x80, .ramp_bit = 0x1, .fps_src = 0x1, .fps_pd_period = 0x7, .fps_pu_period = 0x1, .ramp_div = 0x6B6C, .always_on = 0x1 } },
    /* Vdd2. */
    { 1, "max77620_sd1", 1,
    { .main_pmic = { .volt_reg = 23, .step_uv = 12500, .min_uv = 600000, .default_uv = 1100000, .max_uv = 1100000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x17, .config_reg = 0x1E, .voltage_mask = 0x3F, .enable_mask = 0x30, .enable_shift = 0x4, .fps_reg = 0x50, .unk_3c = 0x4, .unk_50 = 0x1, .enable_delay_us = 60, .disable_delay_us = 145800, .unk_68 = 0x40, .ramp_bit = 0x1, .fps_pd_period = 0x2, .fps_pu_period = 0x5, .ramp_div = 0x6B6C, .always_on = 0x1, .pmc_mask = 0x1 } },
    /* Supply for ldo{0-1,7-8}. */
    { 2, "max77620_sd2", 1,
    { .main_pmic = { .volt_reg = 24, .step_uv = 12500, .min_uv = 600000, .default_uv = 1325000, .max_uv = 1325000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x18, .config_reg = 0x1F, .voltage_mask = 0xFF, .enable_mask = 0x30, .enable_shift = 0x4, .fps_reg = 0x51, .unk_3c = 0x4, .unk_50 = 0x1, .enable_delay_us = 40, .disable_delay_us = 20000, .unk_68 = 0x20, .ramp_bit = 0x1, .fps_src = 0x3, .ramp_div = 0x6B6C } },
    /* 1.8V general. */
    { 3, "max77620_sd3", 1,
    { .main_pmic = { .volt_reg = 25, .step_uv = 12500, .min_uv = 600000, .default_uv = 1800000, .max_uv = 1800000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x19, .config_reg = 0x20, .voltage_mask = 0xFF, .enable_mask = 0x30, .enable_shift = 0x4, .fps_reg = 0x52, .unk_3c = 0x4, .unk_50 = 0x1, .enable_delay_us = 50, .disable_delay_us = 118000, .unk_68 = 0x10, .ramp_bit = 0x1, .fps_pd_period = 0x4, .fps_pu_period = 0x2, .ramp_div = 0x6B6C, .always_on = 0x1 } },
    /* Display panel. */
    { 4, "max77620_ldo0", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 25000, .min_uv = 800000, .default_uv = 1200000, .max_uv = 1200000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x23, .config_reg = 0x24, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x46, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 50, .disable_delay_us = 4000, .fps_src = 0x3, .ramp_div = 0xC350, .pmc_bit = 0x200 } },
    /* XUSB, PCIE. */
    { 5, "max77620_ldo1", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 25000, .min_uv = 800000, .default_uv = 1000000, .max_uv = 1000000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x25, .config_reg = 0x26, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x47, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 50, .disable_delay_us = 7000, .fps_src = 0x3, .ramp_div = 0xC350 } },
    /* SDMMC1. */
    { 6, "max77620_ldo2", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 1800000, .max_uv = 3300000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x27, .config_reg = 0x28, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x48, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 100, .disable_delay_us = 6000, .fps_src = 0x3, .ramp_div = 0xC350 } },
    /* GC ASIC. */
    { 7, "max77620_ldo3", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 3100000, .max_uv = 3100000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x29, .config_reg = 0x2A, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x49, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 100, .disable_delay_us = 3000, .fps_src = 0x3, .ramp_div = 0xC350 } },
    /* RTC, AO. */
    { 8, "max77620_ldo4", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 12500, .min_uv = 800000, .default_uv = 800000, .max_uv = 800000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x2B, .config_reg = 0x2C, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4A, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 50, .disable_delay_us = 610, .fps_pd_period = 0x7, .ramp_div = 0xC350, .always_on = 0x1, .pmc_mask = 0x1 } },
    /* GC card. */
    { 9, "max77620_ldo5", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 1800000, .max_uv = 1800000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x2D, .config_reg = 0x2E, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4B, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 70, .disable_delay_us = 3000, .fps_src = 0x3, .ramp_div = 0xC350 } },
    /* Touch, ALS. */
    { 10, "max77620_ldo6", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 2900000, .max_uv = 2900000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x2F, .config_reg = 0x30, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4C, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 100, .disable_delay_us = 3000, .fps_src = 0x3, .ramp_div = 0xC350 } },
    /* XUSB. */
    { 11, "max77620_ldo7", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 1000000, .max_uv = 3100000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x31, .config_reg = 0x32, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4D, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 50, .disable_delay_us = 2768, .fps_src = 0x3, .ramp_div = 0xC350 } },
    /* XUSB, DP, MCU. */
    { 12, "max77620_ldo8", 1,
    { .main_pmic = { .volt_reg = 0, .step_uv = 50000, .min_uv = 800000, .default_uv = 1000000, .max_uv = 2800000, .volt_code = 0, .unk_0 = 0 } },
    { .volt_reg_byte = 0x33, .config_reg = 0x34, .voltage_mask = 0x3F, .enable_mask = 0xC0, .enable_shift = 0x6, .fps_reg = 0x4E, .unk_3c = 0x4, .unk_50 = 0x1, .is_ldo = 0x1, .enable_delay_us = 50, .disable_delay_us = 4000, .fps_src = 0x3, .ramp_div = 0xC350 } },
    /* Cpu. */
    { 13, "max77621_cpu", 2,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 6250, .unk_1 = 0, .min_uv = 618750, .max_uv = 1175000, .volt_code = 0, .default_uv = 1000000 } },
    { .unk_50 = 0x1, .ramp_rate_uv_per_us = 12000, .enable_delay_us = 500, .disable_delay_us = 60000, .ctrl_reg1 = 0xB0, .ctrl_reg2 = 0xC2, .i2c_device_code = 0x3A000003, .gpio_name = "max77620_gpio5", .always_on = 0x1 } },
    /* Gpu. */
    { 14, "max77621_gpu", 2,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 6250, .unk_1 = 0, .min_uv = 618750, .max_uv = 1150000, .volt_code = 0, .default_uv = 1000000 } },
    { .unk_50 = 0x1, .ramp_rate_uv_per_us = 12000, .enable_delay_us = 500, .disable_delay_us = 60000, .ctrl_reg1 = 0xB0, .ctrl_reg2 = 0xC2, .i2c_device_code = 0x3A000004, .gpio_name = "max77620_gpio6" } },
    /* Cpu. */
    { 0, "max77812_cpu", 3,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 5000, .unk_1 = 0, .min_uv = 250000, .max_uv = 1525000, .volt_code = 0, .default_uv = 1000000 } },
    { .unk_50 = 0x1, .unk_54 = 0x2, .always_on = 0x1, .dvfs_idx = 0 } },
    /* Gpu. */
    { 1, "max77812_gpu", 3,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 5000, .unk_1 = 0, .min_uv = 250000, .max_uv = 1525000, .volt_code = 0, .default_uv = 800000 } },
    { .unk_50 = 0x1, .unk_54 = 0x2, .dvfs_idx = 0x1 } },
    /* Vddq. */
    { 2, "max77812_dram", 3,
    { .dvfs_pmic = { .unk_0 = 0, .step_uv = 5000, .unk_1 = 0, .min_uv = 250000, .max_uv = 1525000, .volt_code = 0, .default_uv = 600000 } },
    { .unk_50 = 0x1, .unk_54 = 0x2, .always_on = 0x1, .dvfs_idx = 0x2 } },
};
