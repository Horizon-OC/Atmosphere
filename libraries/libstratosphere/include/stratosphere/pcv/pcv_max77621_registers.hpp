/*
 * Copyright (c) 2018 naehrwert
 * Copyright (c) 2019-2020 CTCaer
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

namespace ams::pcv {

    constexpr inline u8 Max77621CpuI2cAddr = 0x1B;
    constexpr inline u8 Max77621GpuI2cAddr = 0x1C;

    constexpr inline u8 Max77621VoutReg     = 0x00;
    constexpr inline u8 Max77621VoutDvsReg  = 0x01;
    constexpr inline u8 Max77621Control1Reg = 0x02;
    constexpr inline u8 Max77621Control2Reg = 0x03;
    constexpr inline u8 Max77621ChipId1Reg  = 0x04;
    constexpr inline u8 Max77621ChipId2Reg  = 0x05;

    /* Max77621VoutDvcDvs */
    constexpr inline u8 Max77621DvcDvsVoltMask    = 0x7F;
    constexpr inline u8 Max77621DvcDvsEnableShift = 7;
    constexpr inline u8 Max77621DvcDvsEnableMask  = (1 << Max77621DvcDvsEnableShift);

    /* Max77621Vout */
    constexpr inline u8 Max77621VoutDisable    = 0;
    constexpr inline u8 Max77621VoutEnable     = 1;
    constexpr inline u8 Max77621VoutEnableMask = (Max77621VoutEnable << Max77621DvcDvsEnableShift);

    /* Max77621Control1 */
    constexpr inline u8 Max77621Ramp12mVPerUs  = 0x0;
    constexpr inline u8 Max77621Ramp25mVPerUs  = 0x1;
    constexpr inline u8 Max77621Ramp50mVPerUs  = 0x2;
    constexpr inline u8 Max77621Ramp200mVPerUs = 0x3;
    constexpr inline u8 Max77621RampMask       = 0x3;

    constexpr inline u8 Max77621FreqShift9Per = BIT(2);
    constexpr inline u8 Max77621BiasEnable    = BIT(3);
    constexpr inline u8 Max77621AdEnable      = BIT(4);
    constexpr inline u8 Max77621NfsrEnable    = BIT(5);
    constexpr inline u8 Max77621FpwmEnM       = BIT(6);
    constexpr inline u8 Max77621SnsEnable     = BIT(7);

    /* Max77621Control2 */
    constexpr inline u8 Max77621InductorMin30Per  = 0;
    constexpr inline u8 Max77621InductorNominal   = 1;
    constexpr inline u8 Max77621InductorPlus30Per = 2;
    constexpr inline u8 Max77621InductorPlus60Per = 3;
    constexpr inline u8 Max77621InductorMask      = 3;

    constexpr inline u8 Max77621CkkadvTrip75mVPerUs  = (0  << 2);
    constexpr inline u8 Max77621CkkadvTrip150mVPerUs = (1u << 2);
    constexpr inline u8 Max77621CkkadvTripDisable    = (3u << 2);
    constexpr inline u8 Max77621CkkadvTripMask       = (3u << 2);

    constexpr inline u8 Max77621FtEnable     = BIT(4);
    constexpr inline u8 Max77621DischEnable  = BIT(5);
    constexpr inline u8 Max77621WdtmrEnable  = BIT(6);
    constexpr inline u8 Max77621TJunction120 = BIT(7);

    constexpr inline u8 Max77621CpuCtrl1PorDefault = Max77621Ramp50mVPerUs;
    constexpr inline u8 Max77621CpuCtrl1HosDefault = (Max77621AdEnable | Max77621NfsrEnable | Max77621SnsEnable  | Max77621Ramp12mVPerUs);
    constexpr inline u8 Max77621CpuCtrl2PorDefault = (Max77621TJunction120 | Max77621FtEnable | Max77621CkkadvTripDisable | Max77621InductorNominal);
    constexpr inline u8 Max77621CpuCtrl2HosDefault = (Max77621TJunction120 | Max77621WdtmrEnable | Max77621CkkadvTrip75mVPerUs | Max77621InductorNominal);

    constexpr inline u8 Max77621CtrlHosCfg = 0;

}
