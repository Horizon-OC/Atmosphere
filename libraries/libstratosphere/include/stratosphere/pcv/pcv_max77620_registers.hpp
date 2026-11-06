/*
 * Copyright (c) 2020 CTCaer
 * Copyright (c) 2016 NVIDIA CORPORATION. All rights reserved.
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

namespace ams::pcv {

    /* Max77620 PMIC registers */
    constexpr inline u8 Max77620PmicCnfgGlbl1Reg   = 0x00;
    constexpr inline u8 Max77620PmicCnfgGlbl2Reg   = 0x01;
    constexpr inline u8 Max77620PmicCnfgGlbl3Reg   = 0x02;
    constexpr inline u8 Max77620PmicCnfg132kReg    = 0x03;
    constexpr inline u8 Max77620PmicCnfgBbcReg     = 0x04;
    constexpr inline u8 Max77620PmicIrqTopReg      = 0x05;
    constexpr inline u8 Max77620PmicIntLbtReg      = 0x06;
    constexpr inline u8 Max77620PmicIrqSdReg       = 0x07;
    constexpr inline u8 Max77620PmicIrqLvl2L07Reg  = 0x08;
    constexpr inline u8 Max77620PmicIrqLvl2L8Reg   = 0x09;
    constexpr inline u8 Max77620PmicIrqLvl2GpioReg = 0x0A;
    constexpr inline u8 Max77620PmicOnOffIrqReg    = 0x0B;
    constexpr inline u8 Max77620PmicNvercReg       = 0x0C;
    constexpr inline u8 Max77620PmicIrqTopMReg     = 0x0D;
    constexpr inline u8 Max77620PmicIntEnLbtReg    = 0x0E;
    constexpr inline u8 Max77620PmicIrqMaskSdReg   = 0x0F;
    constexpr inline u8 Max77620PmicIrqMskL07Reg   = 0x10;
    constexpr inline u8 Max77620PmicIrqMskL8Reg    = 0x11;
    constexpr inline u8 Max77620PmicOnOffIrqMReg   = 0x12;
    constexpr inline u8 Max77620PmicStatLbtReg     = 0x13;
    constexpr inline u8 Max77620PmicStatSdReg      = 0x14;
    constexpr inline u8 Max77620PmicOnOffStatReg   = 0x15;

    /* Step-down regulators. */
    constexpr inline u8 Max77620PmicSd0Reg         = 0x16;
    constexpr inline u8 Max77620PmicSd1Reg         = 0x17;
    constexpr inline u8 Max77620PmicSd2Reg         = 0x18;
    constexpr inline u8 Max77620PmicSd3Reg         = 0x19;
    constexpr inline u8 Max77620PmicSd4Reg         = 0x1A;
    constexpr inline u8 Max77620PmicDvsSd0Reg      = 0x1B;
    constexpr inline u8 Max77620PmicDvsSd1Reg      = 0x1C;
    constexpr inline u8 Max77620PmicSd0CfgReg      = 0x1D;
    constexpr inline u8 Max77620PmicSd1CfgReg      = 0x1E;
    constexpr inline u8 Max77620PmicSd2CfgReg      = 0x1F;
    constexpr inline u8 Max77620PmicSd3CfgReg      = 0x20;
    constexpr inline u8 Max77620PmicSd4CfgReg      = 0x21;
    constexpr inline u8 Max77620PmicSdCfg2Reg      = 0x22;

    /* LDO regulators. */
    constexpr inline u8 Max77620PmicLdo0CfgReg     = 0x23;
    constexpr inline u8 Max77620PmicLdo0Cfg2Reg    = 0x24;
    constexpr inline u8 Max77620PmicLdo1CfgReg     = 0x25;
    constexpr inline u8 Max77620PmicLdo1Cfg2Reg    = 0x26;
    constexpr inline u8 Max77620PmicLdo2CfgReg     = 0x27;
    constexpr inline u8 Max77620PmicLdo2Cfg2Reg    = 0x28;
    constexpr inline u8 Max77620PmicLdo3CfgReg     = 0x29;
    constexpr inline u8 Max77620PmicLdo3Cfg2Reg    = 0x2A;
    constexpr inline u8 Max77620PmicLdo4CfgReg     = 0x2B;
    constexpr inline u8 Max77620PmicLdo4Cfg2Reg    = 0x2C;
    constexpr inline u8 Max77620PmicLdo5CfgReg     = 0x2D;
    constexpr inline u8 Max77620PmicLdo5Cfg2Reg    = 0x2E;
    constexpr inline u8 Max77620PmicLdo6CfgReg     = 0x2F;
    constexpr inline u8 Max77620PmicLdo6Cfg2Reg    = 0x30;
    constexpr inline u8 Max77620PmicLdo7CfgReg     = 0x31;
    constexpr inline u8 Max77620PmicLdo7Cfg2Reg    = 0x32;
    constexpr inline u8 Max77620PmicLdo8CfgReg     = 0x33;
    constexpr inline u8 Max77620PmicLdo8Cfg2Reg    = 0x34;
    constexpr inline u8 Max77620PmicLdoCfg3Reg     = 0x35;

    /* GPIO. */
    constexpr inline u8 Max77620PmicGpio0Reg       = 0x36;
    constexpr inline u8 Max77620PmicGpio1Reg       = 0x37;
    constexpr inline u8 Max77620PmicGpio2Reg       = 0x38;
    constexpr inline u8 Max77620PmicGpio3Reg       = 0x39;
    constexpr inline u8 Max77620PmicGpio4Reg       = 0x3A;
    constexpr inline u8 Max77620PmicGpio5Reg       = 0x3B;
    constexpr inline u8 Max77620PmicGpio6Reg       = 0x3C;
    constexpr inline u8 Max77620PmicGpio7Reg       = 0x3D;
    constexpr inline u8 Max77620PmicPueGpioReg     = 0x3E;
    constexpr inline u8 Max77620PmicPdeGpioReg     = 0x3F;
    constexpr inline u8 Max77620PmicAmeGpioReg     = 0x40;

    /* ON/OFF controller. */
    constexpr inline u8 Max77620PmicOnOffCnfg1Reg  = 0x41;
    constexpr inline u8 Max77620PmicOnOffCnfg2Reg  = 0x42;

    /* Flexible power sequencer. */
    constexpr inline u8 Max77620PmicFpsCfg0Reg     = 0x43;
    constexpr inline u8 Max77620PmicFpsCfg1Reg     = 0x44;
    constexpr inline u8 Max77620PmicFpsCfg2Reg     = 0x45;
    constexpr inline u8 Max77620PmicFpsLdo0Reg     = 0x46;
    constexpr inline u8 Max77620PmicFpsLdo1Reg     = 0x47;
    constexpr inline u8 Max77620PmicFpsLdo2Reg     = 0x48;
    constexpr inline u8 Max77620PmicFpsLdo3Reg     = 0x49;
    constexpr inline u8 Max77620PmicFpsLdo4Reg     = 0x4A;
    constexpr inline u8 Max77620PmicFpsLdo5Reg     = 0x4B;
    constexpr inline u8 Max77620PmicFpsLdo6Reg     = 0x4C;
    constexpr inline u8 Max77620PmicFpsLdo7Reg     = 0x4D;
    constexpr inline u8 Max77620PmicFpsLdo8Reg     = 0x4E;
    constexpr inline u8 Max77620PmicFpsSd0Reg      = 0x4F;
    constexpr inline u8 Max77620PmicFpsSd1Reg      = 0x50;
    constexpr inline u8 Max77620PmicFpsSd2Reg      = 0x51;
    constexpr inline u8 Max77620PmicFpsSd3Reg      = 0x52;
    constexpr inline u8 Max77620PmicFpsSd4Reg      = 0x53;
    constexpr inline u8 Max77620PmicFpsGpio1Reg    = 0x54;
    constexpr inline u8 Max77620PmicFpsGpio2Reg    = 0x55;
    constexpr inline u8 Max77620PmicFpsGpio3Reg    = 0x56;
    constexpr inline u8 Max77620PmicFpsRsoReg      = 0x57;

    /* Chip ID. */
    constexpr inline u8 Max77620PmicCid0Reg        = 0x58;
    constexpr inline u8 Max77620PmicCid1Reg        = 0x59;
    constexpr inline u8 Max77620PmicCid2Reg        = 0x5A;
    constexpr inline u8 Max77620PmicCid3Reg        = 0x5B;
    constexpr inline u8 Max77620PmicCid4Reg        = 0x5C;
    constexpr inline u8 Max77620PmicCid5Reg        = 0x5D;

    constexpr inline u8 Max77620PmicDvsSd4Reg      = 0x5E;

    /* IRQ masks. */
    constexpr inline u8 Max77620PmicIrqTopGlblMask  = BIT(7);
    constexpr inline u8 Max77620PmicIrqTopSdMask    = BIT(6);
    constexpr inline u8 Max77620PmicIrqTopLdoMask   = BIT(5);
    constexpr inline u8 Max77620PmicIrqTopGpioMask  = BIT(4);
    constexpr inline u8 Max77620PmicIrqTopRtcMask   = BIT(3);
    constexpr inline u8 Max77620PmicIrqTop32kMask   = BIT(2);
    constexpr inline u8 Max77620PmicIrqTopOnOffMask = BIT(1);

    /* ONOFFIRQ/ONOFFIRQM bits (power button, lid, AC adapter). */
    constexpr inline u8 Max77620PmicOnOffIrqMrWrnMask    = BIT(0); /* Manual reset warning. */
    constexpr inline u8 Max77620PmicOnOffIrqEn01SecMask  = BIT(1);
    constexpr inline u8 Max77620PmicOnOffIrqEn0FallMask  = BIT(2); /* Power button edge. */
    constexpr inline u8 Max77620PmicOnOffIrqEn0RiseMask  = BIT(3); /* Power button edge. */
    constexpr inline u8 Max77620PmicOnOffIrqLidFallMask  = BIT(4);
    constexpr inline u8 Max77620PmicOnOffIrqLidRiseMask  = BIT(5);
    constexpr inline u8 Max77620PmicOnOffIrqAcOkFallMask = BIT(6); /* AC adapter removed. */
    constexpr inline u8 Max77620PmicOnOffIrqAcOkRiseMask = BIT(7); /* AC adapter inserted. */

    /* Edges that signal the power button event. */
    constexpr inline u8 Max77620PmicOnOffIrqPowerButtonMask = Max77620PmicOnOffIrqEn0FallMask | Max77620PmicOnOffIrqEn0RiseMask;

    /* ONOFFCNFG1 bits. */
    constexpr inline u8 Max77620PmicOnOffCnfg1SftRstMask   = BIT(7); /* Trigger soft reset. */
    constexpr inline u8 Max77620PmicOnOffCnfg1MrtMask      = 0x38;   /* Manual reset time. */
    constexpr inline u8 Max77620PmicOnOffCnfg1MrtShift     = 3;
    constexpr inline u8 Max77620PmicOnOffCnfg1SlpEnMask    = BIT(2); /* Enter sleep. */
    constexpr inline u8 Max77620PmicOnOffCnfg1PwrOffMask   = BIT(1); /* Trigger power off. */

    /* ONOFFCNFG2 bits. */
    constexpr inline u8 Max77620PmicOnOffCnfg2SftRstWkMask = BIT(7); /* Wake after soft reset (reboot) */
    constexpr inline u8 Max77620PmicOnOffCnfg2WdRstWkMask  = BIT(6); /* Wake after watchdog reset. */
    constexpr inline u8 Max77620PmicOnOffCnfg2SlpLpmMask   = BIT(5); /* Low-power mode while asleep. */
    constexpr inline u8 Max77620PmicOnOffCnfg2WkAlarm1Mask = BIT(2); /* Wake on RTC alarm 1. */
    constexpr inline u8 Max77620PmicOnOffCnfg2WkAlarm2Mask = BIT(1); /* Wake on RTC alarm 2? */
    constexpr inline u8 Max77620PmicOnOffCnfg2WkEn0Mask    = BIT(0); /* Wake on power button */

    /* ONOFFSTAT bits. */
    constexpr inline u8 Max77620PmicOnOffStatLidMask  = BIT(0);
    constexpr inline u8 Max77620PmicOnOffStatAcOkMask = BIT(1);
    constexpr inline u8 Max77620PmicOnOffStatEn0Mask  = BIT(2); /* Power button held. */

    /* INTLBT/INTENLBT bits (low battery, thermal alarms, global mask). */
    constexpr inline u8 Max77620PmicIrqLbmMask      = BIT(3);
    constexpr inline u8 Max77620PmicIrqTjAlrm1Mask  = BIT(2);
    constexpr inline u8 Max77620PmicIrqTjAlrm2Mask  = BIT(1);
    constexpr inline u8 Max77620PmicGlblMMask       = BIT(0);

    /* NVERC bits. (reset/shutdown cause) */
    /* Unsure if these are correct. */
    constexpr inline u8 Max77620PmicNvercShutdownPinMask  = BIT(0);
    constexpr inline u8 Max77620PmicNvercSysWatchdogMask  = BIT(1);
    constexpr inline u8 Max77620PmicNvercHardResetMask    = BIT(2);
    constexpr inline u8 Max77620PmicNvercJunctionTempMask = BIT(3);
    constexpr inline u8 Max77620PmicNvercBatteryLowMask   = BIT(4);
    constexpr inline u8 Max77620PmicNvercBatteryOvloMask  = BIT(5);
    constexpr inline u8 Max77620PmicNvercBatteryUvloMask  = BIT(6);
    constexpr inline u8 Max77620PmicNvercResetInputMask   = BIT(7);

    /* Hardware protection events + reset input? */
    constexpr inline u8 NvercEnvironmentShutdownMask = Max77620PmicNvercJunctionTempMask | Max77620PmicNvercBatteryOvloMask | Max77620PmicNvercBatteryUvloMask | Max77620PmicNvercResetInputMask;
    /* User/external requested power-off? */
    constexpr inline u8 NvercUserShutdownMask        = Max77620PmicNvercShutdownPinMask | Max77620PmicNvercHardResetMask;

    /* Thermal flag alarms. */
    constexpr inline u8 Max77620PmicThermalFlagAlarm1 = BIT(0);
    constexpr inline u8 Max77620PmicThermalFlagAlarm2 = BIT(1);

    /* I2C address. */
    constexpr inline u8 Max77620PmicI2cAddress = 0x3C;
    constexpr inline u8 Max20024PmicRegMaxAdd  = 0x70;

    /* CNFGGLBL1 bits. */
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDacEnMask  = BIT(7);
    constexpr inline u8 Max77620PmicCnfgGlbl1MppLdMask    = BIT(6);
    constexpr inline u8 Max77620PmicCnfgGlbl1LbHystMask   = BIT(5) | BIT(4);
    constexpr inline u8 Max77620PmicCnfgGlbl1LbHyst100    = 0 << 4;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbHyst200    = 1 << 4;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbHyst300    = 2 << 4;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbHyst400    = 3 << 4;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDacMask    = 0x0E;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDac2700    = 0 << 1;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDac2800    = 1 << 1;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDac2900    = 2 << 1;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDac3000    = 3 << 1;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDac3100    = 4 << 1;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDac3200    = 5 << 1;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDac3300    = 6 << 1;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbDac3400    = 7 << 1;
    constexpr inline u8 Max77620PmicCnfgGlbl1LbRstEnMask  = BIT(0);

    /* CNFGGLBL3 (watchdog) bits. */
    constexpr inline u8 Max77620PmicCnfgGlbl3WdtcMask  = 0x3;
    constexpr inline u8 Max77620PmicCnfgGlbl3WdtOffC   = BIT(4);
    constexpr inline u8 Max77620PmicCnfgGlbl3WdtSlpC   = BIT(3);
    constexpr inline u8 Max77620PmicCnfgGlbl3WdtEn     = BIT(2);
    constexpr inline u8 Max77620PmicCnfgGlbl3TwdMask   = 0x3;
    constexpr inline u8 Max77620PmicCnfgGlbl3Twd2s     = 0x0;
    constexpr inline u8 Max77620PmicCnfgGlbl3Twd16s    = 0x1;
    constexpr inline u8 Max77620PmicCnfgGlbl3Twd64s    = 0x2;
    constexpr inline u8 Max77620PmicCnfgGlbl3Twd128s   = 0x3;

    /* CNFG1_32K bits. */
    constexpr inline u8 Max77620PmicCnfg132kOut0EnMask = BIT(2);

    /* CNFGBBC (backup battery charger) bits. */
    constexpr inline u8 Max77620PmicCnfgBbcEnableMask            = BIT(0);
    constexpr inline u8 Max77620PmicCnfgBbcCurrentMask           = 0x06;
    constexpr inline u8 Max77620PmicCnfgBbcCurrentShift          = 1;
    constexpr inline u8 Max77620PmicCnfgBbcVoltageMask           = 0x18;
    constexpr inline u8 Max77620PmicCnfgBbcVoltageShift          = 3;
    constexpr inline u8 Max77620PmicCnfgBbcLowCurrentDisableMask = BIT(5);
    constexpr inline u8 Max77620PmicCnfgBbcResistorMask          = 0xC0;
    constexpr inline u8 Max77620PmicCnfgBbcResistorShift         = 6;
    constexpr inline u8 Max77620PmicCnfgBbcResistor100           = 0 << Max77620PmicCnfgBbcResistorShift;
    constexpr inline u8 Max77620PmicCnfgBbcResistor1k            = 1 << Max77620PmicCnfgBbcResistorShift;
    constexpr inline u8 Max77620PmicCnfgBbcResistor3k            = 2 << Max77620PmicCnfgBbcResistorShift;
    constexpr inline u8 Max77620PmicCnfgBbcResistor6k            = 3 << Max77620PmicCnfgBbcResistorShift;

    /* Regulator voltage masks. */
    constexpr inline u8 Max77620PmicSdxVoltMask = 0xFF;
    constexpr inline u8 Max77620PmicSd0VoltMask = 0x3F;
    constexpr inline u8 Max77620PmicSd1VoltMask = 0x7F;
    constexpr inline u8 Max77620PmicLdoVoltMask = 0x3F;

    /* LDO CFG bits. */
    constexpr inline u8 Max77620PmicLdoPowerModeMask  = 0xC0;
    constexpr inline u8 Max77620PmicLdoPowerModeShift = 6;
    constexpr inline u8 Max77620PmicPowerModeNormal   = 3;
    constexpr inline u8 Max77620PmicPowerModeLpm      = 2;
    constexpr inline u8 Max77620PmicPowerModeGlpm     = 1;
    constexpr inline u8 Max77620PmicPowerModeDisable  = 0;

    /* LDO CFG2 bits. */
    constexpr inline u8 Max20024PmicLdoCfg2MpokMask    = BIT(2);
    constexpr inline u8 Max77620PmicLdoCfg2AdeMask     = BIT(1);
    constexpr inline u8 Max77620PmicLdoCfg2AdeDisable  = 0 << 1;
    constexpr inline u8 Max77620PmicLdoCfg2AdeEnable   = 1 << 1;
    constexpr inline u8 Max77620PmicLdoCfg2SsMask      = BIT(0);
    constexpr inline u8 Max77620PmicLdoCfg2SsFast      = BIT(0);
    constexpr inline u8 Max77620PmicLdoCfg2SsSlow      = 0;

    /* LDO CFG3 bits. */
    constexpr inline u8 Max77620PmicLdoCfg3Track4Mask  = BIT(5);
    constexpr inline u8 Max77620PmicLdoCfg3Track4Shift = 5;
    constexpr inline u8 Max77620PmicLdoSlewRateMask    = 0x1;

    /* SD CFG1 bits. */
    constexpr inline u8 Max77620PmicSdSrMask             = 0xC0;
    constexpr inline u8 Max77620PmicSdSrShift            = 6;
    constexpr inline u8 Max77620PmicSdPowerModeMask      = 0x30;
    constexpr inline u8 Max77620PmicSdPowerModeShift     = 4;
    constexpr inline u8 Max77620PmicSdCfg1AdeMask        = BIT(3);
    constexpr inline u8 Max77620PmicSdCfg1AdeDisable     = 0;
    constexpr inline u8 Max77620PmicSdCfg1AdeEnable      = BIT(3);
    constexpr inline u8 Max77620PmicSdFpwmMask           = 0x04;
    constexpr inline u8 Max77620PmicSdFpwmShift          = 2;
    constexpr inline u8 Max77620PmicSdFsradeMask         = 0x01;
    constexpr inline u8 Max77620PmicSdFsradeShift        = 0;
    constexpr inline u8 Max77620PmicSdCfg1FpwmSkip       = 0;
    constexpr inline u8 Max77620PmicSdCfg1FpwmFpwm       = BIT(2);
    constexpr inline u8 Max20024PmicSdCfg1MpokMask       = BIT(1);
    constexpr inline u8 Max77620PmicSdCfg1FsradeDisable  = 0;
    constexpr inline u8 Max77620PmicSdCfg1FsradeEnable   = BIT(0);

    /* SD CFG2 bits. */
    constexpr inline u8 Max77620PmicSdCfg2RovsEnSd1 = BIT(1);
    constexpr inline u8 Max77620PmicSdCfg2RovsEnSd0 = BIT(2);

    /* GPIO configuration bits. */
    constexpr inline u8 Max77620PmicGpioDrvMask         = BIT(0);
    constexpr inline u8 Max77620PmicGpioDrvPushPull     = BIT(0);
    constexpr inline u8 Max77620PmicGpioDrvOpenDrain    = 0;
    constexpr inline u8 Max77620PmicGpioDirMask         = BIT(1);
    constexpr inline u8 Max77620PmicGpioDirInput        = BIT(1);
    constexpr inline u8 Max77620PmicGpioDirOutput       = 0;
    constexpr inline u8 Max77620PmicGpioInputValMask    = BIT(2);
    constexpr inline u8 Max77620PmicGpioOutputValMask   = BIT(3);
    constexpr inline u8 Max77620PmicGpioOutputValHigh   = BIT(3);
    constexpr inline u8 Max77620PmicGpioOutputValLow    = 0;
    constexpr inline u8 Max77620PmicGpioIntMask         = 0x3 << 4;
    constexpr inline u8 Max77620PmicGpioIntFalling      = BIT(4);
    constexpr inline u8 Max77620PmicGpioIntRising       = BIT(5);
    constexpr inline u8 Max77620PmicGpioDbncMask        = 0x3 << 6;
    constexpr inline u8 Max77620PmicGpioDbncNone        = 0x0 << 6;
    constexpr inline u8 Max77620PmicGpioDbnc8ms         = 0x1 << 6;
    constexpr inline u8 Max77620PmicGpioDbnc16ms        = 0x2 << 6;
    constexpr inline u8 Max77620PmicGpioDbnc32ms        = 0x3 << 6;

    /* IRQ_LVL2_GPIO bits. */
    constexpr inline u8 Max77620PmicIrqLvl2GpioEdge0Mask = BIT(0);
    constexpr inline u8 Max77620PmicIrqLvl2GpioEdge1Mask = BIT(1);
    constexpr inline u8 Max77620PmicIrqLvl2GpioEdge2Mask = BIT(2);
    constexpr inline u8 Max77620PmicIrqLvl2GpioEdge3Mask = BIT(3);
    constexpr inline u8 Max77620PmicIrqLvl2GpioEdge4Mask = BIT(4);
    constexpr inline u8 Max77620PmicIrqLvl2GpioEdge5Mask = BIT(5);
    constexpr inline u8 Max77620PmicIrqLvl2GpioEdge6Mask = BIT(6);
    constexpr inline u8 Max77620PmicIrqLvl2GpioEdge7Mask = BIT(7);

    /* ONOFFCNFG1 bits (MAX20024). */
    constexpr inline u8 Max20024PmicOnOffCnfg1ClrSeMask = 0x18;

    /* FPS bits. */
    constexpr inline u8 Max77620PmicFpsSrcMask         = 0xC0;
    constexpr inline u8 Max77620PmicFpsSrcShift        = 6;
    constexpr inline u8 Max77620PmicFpsPuPeriodMask    = 0x38;
    constexpr inline u8 Max77620PmicFpsPuPeriodShift   = 3;
    constexpr inline u8 Max77620PmicFpsPdPeriodMask    = 0x07;
    constexpr inline u8 Max77620PmicFpsPdPeriodShift   = 0;
    constexpr inline u8 Max77620PmicFpsTimePeriodMask  = 0x38;
    constexpr inline u8 Max77620PmicFpsTimePeriodShift = 3;
    constexpr inline u8 Max77620PmicFpsEnSrcMask       = 0x06;
    constexpr inline u8 Max77620PmicFpsEnSrcShift      = 1;
    constexpr inline u8 Max77620PmicFpsEnFpsSwMask     = 0x01;
    constexpr inline u8 Max77620PmicFpsEnFpsSw         = 0x01;

    constexpr inline u32 Max77620PmicFpsCount = 3;

    constexpr inline u32 Max77620PmicFpsPeriodMinUs = 40;
    constexpr inline u32 Max20024PmicFpsPeriodMinUs = 20;
    constexpr inline u32 Max77620PmicFpsPeriodMaxUs = 2560;
    constexpr inline u32 Max20024PmicFpsPeriodMaxUs = 5120;

    enum Max77620PmicFpsSrc {
        Max77620PmicFpsSrc_0    = 0,
        Max77620PmicFpsSrc_1    = 1,
        Max77620PmicFpsSrc_2    = 2,
        Max77620PmicFpsSrc_None = 3,
        Max77620PmicFpsSrc_Def  = 4,
    };

    /* Chip ID. */
    constexpr inline u8 Max77620PmicCidDidmMask  = 0xF0;
    constexpr inline u8 Max77620PmicCidDidmShift = 4;

    constexpr inline u8 Max77620PmicGetCid5Didm(u8 v) { return (v >> 4) & 0xF; }
    constexpr inline u8 Max77620PmicGetCid5Dido(u8 v) { return v & 0xF; }

    enum Max77620PmicChipId {
        Max77620PmicChipId_Max77620 = 0,
        Max77620PmicChipId_Max20024 = 1,
    };

    /* Interrupt indices. */
    enum Max77620PmicIrq {
        Max77620PmicIrq_TopGlbl,    /* Low-Battery */
        Max77620PmicIrq_TopSd,      /* SD power fail */
        Max77620PmicIrq_TopLdo,     /* LDO power fail */
        Max77620PmicIrq_TopGpio,    /* TOP GPIO internal int to MAX77620 */
        Max77620PmicIrq_TopRtc,     /* RTC */
        Max77620PmicIrq_Top32k,     /* 32kHz oscillator */
        Max77620PmicIrq_TopOnOff,   /* ON/OFF oscillator */
        Max77620PmicIrq_LbtMBatLow, /* Low battery */
        Max77620PmicIrq_LbtTjAlrm1, /* Thermal alarm status, > 120C */
        Max77620PmicIrq_LbtTjAlrm2, /* Thermal alarm status, > 140C */
    };

    /* GPIO indices. */
    enum Max77620PmicGpio {
        Max77620PmicGpio_0,
        Max77620PmicGpio_1,
        Max77620PmicGpio_2,
        Max77620PmicGpio_3,
        Max77620PmicGpio_4,
        Max77620PmicGpio_5,
        Max77620PmicGpio_6,
        Max77620PmicGpio_7,
        Max77620PmicGpio_Count,
    };

}
