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
#include "pcv_rgltr_max77812_init.hpp"
#include "pcv_rgltr_volt_max77812.hpp"
#include "../pcv_i2c.hpp"

namespace ams::pcv::rgltr {

    namespace {

        i2c::I2cSession g_session;

        DeviceCode GetMax77812DeviceCode() {
            const RegulatorVariant variant = GetRegulatorVariant();
            if (variant == RegulatorVariant_Mariko_Max77812_B) {
                return i2c::DeviceCode_Max77812_2;
            } else {
                AMS_ABORT_UNLESS(variant == RegulatorVariant_Mariko_Max77812_A);

                /* Type A. */
                return i2c::DeviceCode_Max77812_3;
            }
        }

        struct PmicInitRegs {
            u8 reg;
            u8 mask;
            u8 value;
        };

        constexpr u8 Es2InitMask = 0xFF;

        constinit PmicInitRegs es2_init_regs[] = {
            { Max77812ProtAccessReg, Es2InitMask, Max77812ProtAccessUnLock, },
            { Max77812GlbCfg5Reg,    Es2InitMask, 0x3E,                     },
            { Max77812GlbCfg6Reg,    Es2InitMask, 0x90,                     },
            { Max77812GlbCfg8Reg,    Es2InitMask, 0x3A,                     },
            { Max77812ProtAccessReg, Es2InitMask, Max77812ProtAccessLock,   },
        };

        constexpr u8 IlimConfig  = 0x70;
        constexpr u8 BsdSrConfig = 0x20;
        constexpr u8 BssSrConfig = 0x02;

        constinit PmicInitRegs common_init_regs[] = {
            { Max77812M1CfgReg,   Max77812IlimMask,          IlimConfig,  },
            { Max77812M2CfgReg,   Max77812IlimMask,          IlimConfig,  },
            { Max77812M3CfgReg,   Max77812IlimMask,          IlimConfig,  },
            { Max77812M4CfgReg,   Max77812IlimMask,          IlimConfig,  },
            { Max77812GlbCfg1Reg, Max77812ShdnSlewRateMask,  BsdSrConfig, },
            { Max77812GlbCfg1Reg, Max77812StartSlewRateMask, BssSrConfig, },
            { Max77812GlbCfg2Reg, Max77812ShdnSlewRateMask,  BsdSrConfig, },
            { Max77812GlbCfg2Reg, Max77812StartSlewRateMask, BssSrConfig, },
        };

        enum PmicType : u32 {
            PmicType_Main        = 1, /* Main pmic (Max77620) */
            PmicType_Erista_Dvfs = 2, /* Erista dvfs pmic, Max77621. */
            PmicType_Mariko_Dvfs = 3, /* Mariko dvfs pmic, Max77812. */
        };

        enum DvfsIdx : u32 {
            DvfsIdx_Cpu  = 0,
            DvfsIdx_Gpu  = 1,
            DvfsIdx_Vddq = 2,
        };

        enum MasterIdx : s32 {
            MasterIdx_Cpu     = 3,
            MasterIdx_Gpu     = 0,
            MasterIdx_Vddq    = 2,
            MasterIdx_Invalid = -1,
        };

        struct MasterCfg {
            u8 en_mask;
            u8 lpm_mask;
            u8 shdn_dly_reg;
            u8 pokn_mask;
            u8 pokn_int_mask;
            u8 vout_reg;
            u8 vout_d_reg;
            u8 vout_s_reg;
            u8 cfg_reg;
        };

        constexpr size_t MasterCount = 4;

        constexpr MasterCfg GpuCfg = {
            .en_mask        = 0x01,
            .lpm_mask       = 0x02,
            .shdn_dly_reg   = 0x0A,
            .pokn_mask      = 0x01,
            .pokn_int_mask  = 0x01,
            .vout_reg       = Max77812M1VoutReg,
            .vout_d_reg     = Max77812M1VoutDReg,
            .vout_s_reg     = Max77812M1VoutSReg,
            .cfg_reg        = Max77812M1CfgReg,
        };

        constexpr MasterCfg M2Cfg = {
            .en_mask        = 0x04,
            .lpm_mask       = 0x08,
            .shdn_dly_reg   = 0x0b,
            .pokn_mask      = 0x02,
            .pokn_int_mask  = 0x02,
            .vout_reg       = Max77812M2VoutReg, /* NOTE: Nintendo almost certainly has a typo here by using m3 vout. */
            .vout_d_reg     = Max77812M2VoutDReg,
            .vout_s_reg     = Max77812M2VoutSReg,
            .cfg_reg        = Max77812M2CfgReg,
        };

        constexpr MasterCfg VddqCfg = {
            .en_mask        = 0x10,
            .lpm_mask       = 0x20,
            .shdn_dly_reg   = 0x0C,
            .pokn_mask      = 0x04,
            .pokn_int_mask  = 0x04,
            .vout_reg       = Max77812M3VoutReg,
            .vout_d_reg     = Max77812M3VoutDReg,
            .vout_s_reg     = Max77812M3VoutSReg,
            .cfg_reg        = Max77812M3CfgReg,
        };

        constexpr MasterCfg CpuCfg = {
            .en_mask        = 0x40,
            .lpm_mask       = 0x80,
            .shdn_dly_reg   = 0x0D,
            .pokn_mask      = 0x08,
            .pokn_int_mask  = 0x08,
            .vout_reg       = Max77812M4VoutReg,
            .vout_d_reg     = Max77812M4VoutDReg,
            .vout_s_reg     = Max77812M4VoutSReg,
            .cfg_reg        = Max77812M4CfgReg,
        };

        constexpr MasterCfg MasterConfig[MasterCount] = { GpuCfg, M2Cfg, VddqCfg, CpuCfg, };

        Slew g_slew;

        void WriteEs2InitRegs() {
            for (size_t i = 0; i < util::size(es2_init_regs); ++i) {
                /* Read the register */
                u8 register_value;
                if (R_FAILED(I2cRead(g_session, es2_init_regs[i].reg, register_value))) {
                    continue;
                }

                /* Set the bits. */
                register_value &= ~es2_init_regs[i].mask;
                register_value |= (es2_init_regs[i].value & es2_init_regs[i].mask);

                R_DISCARD(I2cWrite(g_session, es2_init_regs[i].reg, register_value));
            }
        }

        void WriteCommonInitRegs() {
            for (size_t i = 0; i < util::size(common_init_regs); ++i) {
                /* Read access registers. */
                {
                    u8 dummy;
                    R_DISCARD(I2cRead(g_session, Max77812ProtAccessReg, dummy));
                }

                u8 register_value;
                if (R_FAILED(I2cRead(g_session, common_init_regs[i].reg, register_value))) {
                    continue;
                }

                register_value &= ~common_init_regs[i].mask;
                register_value |= (common_init_regs[i].value & common_init_regs[i].mask);

                R_DISCARD(I2cWrite(g_session, common_init_regs[i].reg, register_value));

                /* Sure nintendo read it again. */
                R_DISCARD(I2cRead(g_session, common_init_regs[i].reg, register_value));
            }
        }

        MasterIdx GetMasterIdx(Regulator &regulator) {
            switch (regulator.dvfs_idx) {
                case DvfsIdx_Cpu: return MasterIdx_Cpu;
                case DvfsIdx_Gpu: return MasterIdx_Gpu;
                case DvfsIdx_Vddq:
                    if (GetRegulatorVariant() == RegulatorVariant_Mariko_Max77812_A) {
                        /* Prototype does not have a vddq master. */
                        return MasterIdx_Invalid;
                    } else {
                        return MasterIdx_Vddq;
                    }
                default:
                    return MasterIdx_Invalid;
            }
        }

        bool ConfigureMaster(Regulator &regulator) {
            const MasterIdx master_idx = GetMasterIdx(regulator);

            if (master_idx == MasterIdx_Invalid) {
                return false;
            }

            regulator.selected_master = static_cast<u32>(master_idx);

            /* Copy the master's register set into the regulator. */
            const MasterCfg &master = MasterConfig[master_idx];
            regulator.master_en_mask = master.en_mask;
            regulator.lpm_mask       = master.lpm_mask;
            regulator.shdn_dly_reg   = master.shdn_dly_reg;
            regulator.pokn_mask      = master.pokn_mask;
            regulator.pokn_int_mask  = master.pokn_int_mask;
            regulator.vout_reg       = master.vout_reg;
            regulator.vout_d_reg     = master.vout_d_reg;
            regulator.vout_s_reg     = master.vout_s_reg;
            regulator.master_cfg_reg = master.cfg_reg;

            return true;
        }

        /* NOTE: Nintendo uses 0 for index 7, but datasheet specifies 60mV/µs. */
        constexpr u32 SlewUvPerUs[] = {
            1250, 2500, 5000, 10000, 20000, 40000, 60000, 0,
        };

        Result ConfigureSlew() {
            u8 slew_reg_value;
            R_TRY(I2cRead(g_session, Max77812GlbCfg1Reg, slew_reg_value));
            /* Nintendo rereads this again and discards the result^ */

            u8 start_slew_code =  slew_reg_value & Max77812StartSlewRateMask;
            u8 shdn_slew_code  = (slew_reg_value & Max77812ShdnSlewRateMask) >> Max77812SlewRateShift;

            g_slew.start_per_us = SlewUvPerUs[start_slew_code];
            g_slew.shdn_per_us  = SlewUvPerUs[shdn_slew_code];

            return ResultSuccess();
        }

        Result ConfigureRamp() {
            u8 ramp_reg_value;
            R_TRY(I2cRead(g_session, Max77812GlbCfg2Reg, ramp_reg_value));
            /* Again nintendo rereads and discards the result on success^ */

            u8 ramp_up_code   = ramp_reg_value  & Max77812RampupSlewRateMask;
            u8 ramp_down_code = (ramp_reg_value & Max77812RampdownSlewRateMask) >> Max77812SlewRateShift;

            g_slew.ramp_up_per_us   = SlewUvPerUs[ramp_up_code];
            g_slew.ramp_down_per_us = SlewUvPerUs[ramp_down_code];

            return ResultSuccess();
        }

        void SetupDvfsPhases() {
            for (size_t i = 0; i < RegulatorCount; ++i) {
                Regulator &regulator = GetRegulator(i);

                /* Skip main and erista pmic, and anything already set up. */
                if (regulator.type != PmicType_Mariko_Dvfs || regulator.is_initialized) {
                    continue;
                }

                /* Set the session. */
                regulator.session = std::addressof(g_session);

                /* Skip on an invalid master (beefy pmic variant doesn't map vddq). */
                if (!ConfigureMaster(regulator)) {
                    continue;
                }

                /* Configure start and shutdown slew. */
                if (R_FAILED(ConfigureSlew())) {
                    continue;
                }

                /* Configure ramp up and ramp down. */
                if (R_FAILED(ConfigureRamp())) {
                    continue;
                }

                if (regulator.always_on) {
                    /* Already enabled. */
                    regulator.enable_count = 1;
                } else {
                    /* Apply voltages. */
                    u8 volt_reg = regulator.vout_reg;

                    if (regulator.use_vout_d) {
                        volt_reg = regulator.vout_d_reg;
                    }

                    R_DISCARD(SetVoltageMax77812Reg(i, regulator.dvfs_pmic.default_uv, volt_reg));
                }

                regulator.is_initialized = true;
            }
        }

    }

    void InitializeMax77812() {
        const DeviceCode device_code = GetMax77812DeviceCode();
        R_ABORT_UNLESS(i2c::OpenSession(std::addressof(g_session), device_code));

        /* Read the version. */
        u8 out_version;
        R_DISCARD(I2cRead(g_session, Max77812VersionReg, out_version));

        out_version &= Max77812VersionMask;

        /* Clear any pending topsys interrupt. */
        {
            u8 dummy;
            R_DISCARD(I2cRead(g_session, Max77812TopsysIntReg, dummy));
        }

        /* Write es2 specific init regs. */
        if (out_version == Max77812Es2Version) {
            WriteEs2InitRegs();
        }

        WriteCommonInitRegs();

        /* Perform the rest of the setup. */
        SetupDvfsPhases();
    }

    Slew &GetSlew() {
        return g_slew;
    }

    void InitializeMax77621() { /* ... */ }

}
