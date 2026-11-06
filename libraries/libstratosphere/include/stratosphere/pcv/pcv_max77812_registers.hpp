/*
 * Copyright (c) 2020 CTCaer
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

    constexpr inline u8 Max77812Phase31CpuI2cAddr  = 0x31; // High power GPU. 2 Outputs: 3-phase M1 + 1-phase M4.
    constexpr inline u8 Max77812Phase211CpuI2cAddr = 0x33; // Low  power GPU. 3 Outputs: 2-phase M1 + 1-phase M3 + 1-phase M4.

    constexpr inline u8 Max77812RsetReg         = 0x00;
    constexpr inline u8 Max77812IntSrcReg       = 0x01;
    constexpr inline u8 Max77812IntSrcMReg      = 0x02;
    constexpr inline u8 Max77812TopsysIntReg    = 0x03;
    constexpr inline u8 Max77812TopsysIntMReg   = 0x04;
    constexpr inline u8 Max77812TopsysStatReg   = 0x05;
    constexpr inline u8 Max77812EnCtrlReg       = 0x06;
    constexpr inline u8 Max77812EnCtrlEnable    = 1;
    constexpr inline u8 Max77812EnCtrlEnM1Shift = 0;
    constexpr inline u8 Max77812EnCtrlEnM1Mask  = (1 << Max77812EnCtrlEnM1Shift);
    constexpr inline u8 Max77812EnCtrlEnM2Shift = 2;
    constexpr inline u8 Max77812EnCtrlEnM2Mask  = (1 << Max77812EnCtrlEnM2Shift);
    constexpr inline u8 Max77812EnCtrlEnM3Shift = 4;
    constexpr inline u8 Max77812EnCtrlEnM3Mask  = (1 << Max77812EnCtrlEnM3Shift);
    constexpr inline u8 Max77812EnCtrlEnM4Shift = 6;
    constexpr inline u8 Max77812EnCtrlEnM4Mask  = (1 << Max77812EnCtrlEnM4Shift);
    constexpr inline u8 Max77812StupDly2Reg     = 0x07;
    constexpr inline u8 Max77812StupDly3Reg     = 0x08;
    constexpr inline u8 Max77812StupDly4Reg     = 0x09;
    constexpr inline u8 Max77812ShdnDly1Reg     = 0x0A;
    constexpr inline u8 Max77812ShdnDly2Reg     = 0x0B;
    constexpr inline u8 Max77812ShdnDly3Reg     = 0x0C;
    constexpr inline u8 Max77812ShdnDly4Reg     = 0x0D;
    constexpr inline u8 Max77812WdtrstbDebReg   = 0x0E;
    constexpr inline u8 Max77812GpiFuncReg      = 0x0F;
    constexpr inline u8 Max77812GpiDeb1Reg      = 0x10;
    constexpr inline u8 Max77812GpiDeb2Reg      = 0x11;
    constexpr inline u8 Max77812GpiPdCtrlReg    = 0x12;
    constexpr inline u8 Max77812ProtCfgReg      = 0x13;
    constexpr inline u8 Max77812VersionReg      = 0x14;
    constexpr inline u8 Max77812I2cCfgReg       = 0x15;
    constexpr inline u8 Max77812BuckIntReg      = 0x20;
    constexpr inline u8 Max77812BuckIntMReg     = 0x21;
    constexpr inline u8 Max77812BuckStatReg     = 0x22;
    constexpr inline u8 Max77812M1VoutReg       = 0x23; // GPU.
    constexpr inline u8 Max77812M2VoutReg       = 0x24;
    constexpr inline u8 Max77812M3VoutReg       = 0x25; // DRAM on PHASE211.
    constexpr inline u8 Max77812M4VoutReg       = 0x26; // CPU.
    constexpr inline u8 Max77812M1VoutDReg      = 0x27;
    constexpr inline u8 Max77812M2VoutDReg      = 0x28;
    constexpr inline u8 Max77812M3VoutDReg      = 0x29;
    constexpr inline u8 Max77812M4VoutDReg      = 0x2A;
    constexpr inline u8 Max77812M1VoutSReg      = 0x2B;
    constexpr inline u8 Max77812M2VoutSReg      = 0x2C;
    constexpr inline u8 Max77812M3VoutSReg      = 0x2D;
    constexpr inline u8 Max77812M4VoutSReg      = 0x2E;
    constexpr inline u8 Max77812M1CfgReg        = 0x2F; // HOS: M1_ILIM - 7.2A/4.8A.
    constexpr inline u8 Max77812M2CfgReg        = 0x30; // HOS: M2_ILIM - 7.2A/4.8A.
    constexpr inline u8 Max77812M3CfgReg        = 0x31; // HOS: M3_ILIM - 7.2A/4.8A.
    constexpr inline u8 Max77812M4CfgReg        = 0x32; // HOS: M4_ILIM - 7.2A/4.8A.
    constexpr inline u8 Max77812GlbCfg1Reg      = 0x33; // HOS: B_SD_SR/B_SS_SR - 5mV/us.
    constexpr inline u8 Max77812GlbCfg2Reg      = 0x34; // HOS: B_RD_SR/B_RU_SR - 5mV/us
    constexpr inline u8 Max77812GlbCfg3Reg      = 0x35;

    /*! Protected area and settings only for Max77812Es2Version */
    constexpr inline u8 Max77812GlbCfg4Reg      = 0x36; // QS: 0xBB.
    constexpr inline u8 Max77812GlbCfg5Reg      = 0x37; // QS: 0x39. ES2: Set to 0x3E.
    constexpr inline u8 Max77812GlbCfg6Reg      = 0x38; // QS: 0x88. ES2: Set to 0x90.
    constexpr inline u8 Max77812GlbCfg7Reg      = 0x39; // QS: 0x04.
    constexpr inline u8 Max77812GlbCfg8Reg      = 0x3A; // QS: 0x3A. ES2: Set to 0x3A.

    constexpr inline u8 Max77812ProtAccessReg   = 0xFD; // 0x00: Lock, 0x5A: Unlock.
    constexpr inline u8 Max77812UnknownReg      = 0xFE;

    constexpr inline u8 Max77812ProtAccessLock   = 0x00;
    constexpr inline u8 Max77812ProtAccessUnLock = 0x5A;

    constexpr inline u8 Max77812EnCtrlMaskReg(u8 n) { return BIT(n); }

    constexpr inline u8 Max77812IlimMask    = 0x70;

    constexpr inline u8 Max77812StartSlewRateMask    = 0x07;
    constexpr inline u8 Max77812ShdnSlewRateMask     = 0x70;
    constexpr inline u8 Max77812RampupSlewRateMask   = 0x07;
    constexpr inline u8 Max77812RampdownSlewRateMask = 0x70;
    constexpr inline u8 Max77812SlewRateShift        = 4;

    constexpr inline u8 Max77812OpActiveDischargeMask = BIT(7);
    constexpr inline u8 Max77812PeakCurrentLmtMask    = 0x70;
    constexpr inline u8 Max77812SwitchFreqMask        = 0x0C;
    constexpr inline u8 Max77812ForcedPwmMask         = BIT(1);
    constexpr inline u8 Max77812SlewRateCntrlMask     = BIT(0);
    constexpr inline u8 Max77812StartShdDelayMask     = 0x1F;
    constexpr inline u8 Max77812VersionMask           = 0x07;
    constexpr inline u8 Max77812Es2Version            = 0x04;
    constexpr inline u8 Max77812QsVersion             = 0x05;

    constexpr inline u8 Max77812BuckVoltMask          = 0xFF;

}
