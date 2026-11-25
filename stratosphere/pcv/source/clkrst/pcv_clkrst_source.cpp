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
#include "../pcv_hardware_type.hpp"
#include "pcv_clkrst_car.hpp"
#include "pcv_clkrst_pll_data.hpp"
#include "pcv_clkrst_source.hpp"

namespace ams::pcv::clkrst {

    #include "pcv_clkrst_clock_sources.inc"

    namespace {
        /* This is complete dogshit but I do not care. */
        constexpr u32 OscFreqKhz     = 38400;
        constexpr u32 ClkSFreqKhz    = 32;
        constexpr u32 PllP0FreqKhz   = 408000;
        constexpr u32 PllP2FreqKhz   = 204000;
        constexpr u32 PllP3FreqKhz   = 102000;
        constexpr u32 PllP4FreqKhz   = 102000;
        constexpr u32 PllP5FreqKhz   = 204000;
        constexpr u32 PllPauxFreqKhz = 24000;

        constexpr u32 SpareReg0ClkMDivisorMask = (0x3 << 2);
        constexpr u32 SpareReg0ClkMDivisorBy2  = (0x1 << 2);

        constexpr u32 OscCtrlPllRefDivMask = (0x3 << 26);

        constexpr u32 PllBaseBypass = BIT(31);
        constexpr u32 PllBaseEnable = BIT(30);

        constexpr u32 PllDivMShift = 0;
        constexpr u32 PllDivMMask  = 0xFF;
        constexpr u32 PllDivNMask  = 0xFF;
        constexpr u32 PllDivPMask  = 0x1F;

        struct PllBaseLayout {
            u32 divn_shift;
            u32 divp_shift;
            u32 divp_mask;
            u32 bypass_mask;
            u32 enable_mask;
        };

        constexpr PllBaseLayout PllcBaseLayout    = { .divn_shift = 10, .divp_shift = 20, .divp_mask = PllDivPMask, .bypass_mask = PllBaseBypass, .enable_mask = PllBaseEnable };
        constexpr PllBaseLayout PllmBaseLayout    = { .divn_shift = 8,  .divp_shift = 20, .divp_mask = PllDivPMask, .bypass_mask = 0,             .enable_mask = PllBaseEnable };
        constexpr PllBaseLayout PlldBaseLayout    = { .divn_shift = 11, .divp_shift = 20, .divp_mask = 0x7,         .bypass_mask = PllBaseBypass, .enable_mask = PllBaseEnable };
        constexpr PllBaseLayout Plld2BaseLayout   = { .divn_shift = 8,  .divp_shift = 19, .divp_mask = PllDivPMask, .bypass_mask = PllBaseBypass, .enable_mask = PllBaseEnable };
        constexpr PllBaseLayout PllrefeBaseLayout = { .divn_shift = 8,  .divp_shift = 16, .divp_mask = PllDivPMask, .bypass_mask = PllBaseBypass, .enable_mask = PllBaseEnable };
        constexpr PllBaseLayout PlleBaseLayout    = { .divn_shift = 8,  .divp_shift = 24, .divp_mask = PllDivPMask, .bypass_mask = 0,             .enable_mask = BIT(31)       };
        constexpr PllBaseLayout PlluBaseLayout    = { .divn_shift = 8,  .divp_shift = 16, .divp_mask = PllDivPMask, .bypass_mask = PllBaseBypass, .enable_mask = PllBaseEnable };
        constexpr PllBaseLayout PlldpBaseLayout   = { .divn_shift = 8,  .divp_shift = 19, .divp_mask = PllDivPMask, .bypass_mask = PllBaseBypass, .enable_mask = PllBaseEnable };
        constexpr PllBaseLayout Pllc4BaseLayout   = { .divn_shift = 8,  .divp_shift = 19, .divp_mask = PllDivPMask, .bypass_mask = PllBaseBypass, .enable_mask = PllBaseEnable };
        constexpr PllBaseLayout PllaBaseLayout    = { .divn_shift = 8,  .divp_shift = 20, .divp_mask = PllDivPMask, .bypass_mask = PllBaseBypass, .enable_mask = PllBaseEnable };
        constexpr PllBaseLayout Plla1BaseLayout   = { .divn_shift = 10, .divp_shift = 20, .divp_mask = PllDivPMask, .bypass_mask = PllBaseBypass, .enable_mask = PllBaseEnable };

        constexpr u32 PllpBaseDivMBit0 = BIT(0);

        constexpr u32 PllOut1Enable     = BIT(0) | BIT(1);
        constexpr u32 PllOut1Override   = BIT(2);
        constexpr u32 PllOut1RatioShift = 8;
        constexpr u32 PllOut1RatioMask  = 0xFF;
        constexpr u32 PllOutBypass      = BIT(16);
        constexpr u32 PllOut2Enable     = BIT(16) | BIT(17);
        constexpr u32 PllOut2Override   = BIT(18);

        constexpr u32 PllU1Divisor  = 5;
        constexpr u32 PllU2Divisor  = 4;
        constexpr u32 PllC41Divisor = 3;
        constexpr u32 PllC42Divisor = 5;

        constexpr u32 UtmipPllCfg0DivMShift                = 8;
        constexpr u32 UtmipPllCfg0DivMMask                 = 0xFF;
        constexpr u32 UtmipPllCfg0DivNShift                = 16;
        constexpr u32 UtmipPllCfg0DivNMask                 = 0xFF;
        constexpr u32 UtmipPllCfg1ForcePllEnablePowerdown  = BIT(14);
        constexpr u32 UtmipPllDivP                         = 1;

        constexpr u32 ClkSourceDivisorMask = 0xFF;

        constexpr u32 PexSataUsbRxBypDivisorMask = 0xFF;
        constexpr u32 PexSataUsbRxBypEnable      = BIT(8);

        constexpr u32 BurstPolicyStateShift = 28;
        constexpr u32 CclkgSourceMask       = 0xF;
        constexpr u32 SclkSourceMask        = 0x7;
        constexpr u32 AclkSourceMask        = 0xF;

        constexpr u32 AclkSourcePllA1Undivided = 8;
        constexpr u32 AclkSourcePllAUndivided  = 15;

        constexpr u32 SuperDividerEnable        = BIT(31);
        constexpr u32 SuperDividerDividendShift = 8;
        constexpr u32 SuperDividerDividendMask  = 0xFF;
        constexpr u32 SuperDividerDivisorShift  = 0;
        constexpr u32 SuperDividerDivisorMask   = 0xFF;
        constexpr u32 SuperAclkDividerShift     = 16;
        constexpr u32 SuperAclkDividerMask      = 0xFF;

        constexpr u32 SystemRateHclkDisable = BIT(7);
        constexpr u32 SystemRateAhbRateShift = 4;
        constexpr u32 SystemRateAhbRateMask  = 0x3;
        constexpr u32 SystemRatePclkDisable = BIT(3);
        constexpr u32 SystemRateApbRateShift = 0;
        constexpr u32 SystemRateApbRateMask  = 0x3;

        enum BurstPolicyState : u32 {
            BurstPolicyState_Stdby = 0,
            BurstPolicyState_Idle  = 1,
            BurstPolicyState_Run   = 2,
            BurstPolicyState_Irq   = 4,
            BurstPolicyState_Fiq   = 8,
        };

        constexpr ClkSourceId CclkgSources[16] = {
            ClkSourceId_ClkM,    ClkSourceId_Invalid, ClkSourceId_ClkS,    ClkSourceId_Invalid,
            ClkSourceId_PllP0,   ClkSourceId_PllP4,   ClkSourceId_Invalid, ClkSourceId_Invalid,
            ClkSourceId_PllX0,   ClkSourceId_DvfsClk, ClkSourceId_Invalid, ClkSourceId_Invalid,
            ClkSourceId_Invalid, ClkSourceId_Invalid, ClkSourceId_PllX0,   ClkSourceId_DvfsClk,
        };

        constexpr ClkSourceId SclkSources[8] = {
            ClkSourceId_ClkM,  ClkSourceId_PllC1,  ClkSourceId_PllC43, ClkSourceId_PllP0,
            ClkSourceId_PllP2, ClkSourceId_PllC41, ClkSourceId_ClkS,   ClkSourceId_PllC42,
        };

        constexpr ClkSourceId AclkSources[16] = {
            ClkSourceId_PllA1,   ClkSourceId_PllC0,   ClkSourceId_PllP0,   ClkSourceId_PllA0,
            ClkSourceId_PllC2,   ClkSourceId_PllC3,   ClkSourceId_ClkM,    ClkSourceId_PllA,
            ClkSourceId_PllA1,   ClkSourceId_Invalid, ClkSourceId_Invalid, ClkSourceId_Invalid,
            ClkSourceId_Invalid, ClkSourceId_Invalid, ClkSourceId_Invalid, ClkSourceId_PllA,
        };

        struct PllBaseValues {
            u32 divm;
            u32 divn;
            u32 divp;
            bool bypass;
            bool enable;
        };

        PllBaseValues ReadPllBase(u32 reg_offset, const PllBaseLayout &layout) {
            const u32 value = ReadCarReg(reg_offset);

            return PllBaseValues {
                .divm   = (value >> PllDivMShift)      & PllDivMMask,
                .divn   = (value >> layout.divn_shift) & PllDivNMask,
                .divp   = (value >> layout.divp_shift) & layout.divp_mask,
                .bypass = (value & layout.bypass_mask) != 0,
                .enable = (value & layout.enable_mask) != 0,
            };
        }

        u32 CalcSimplePllFreq(u32 ref_khz, const PllBaseValues &pll) {
            if (pll.bypass) {
                return ref_khz;
            }

            if (!pll.enable || pll.divm == 0 || pll.divn == 0) {
                return 0;
            }

            return ref_khz / pll.divm * pll.divn / GetPllPDivider(pll.divp);
        }

        u32 CalcPllFreq(size_t pll_index, u32 ref_khz, const PllBaseValues &pll, bool shift_pdiv) {
            return clkrst::CalcPllFreq(pll_index, ref_khz, pll.divm, pll.divn, pll.divp, pll.bypass, pll.enable, shift_pdiv);
        }

        void UpdateBurstPolicySourceShift(u32 state, u32 &source_shift) {
            switch (state) {
                case BurstPolicyState_Idle: source_shift = 0;  break;
                case BurstPolicyState_Run:  source_shift = 4;  break;
                case BurstPolicyState_Irq:  source_shift = 8;  break;
                case BurstPolicyState_Fiq:  source_shift = 12; break;
                default: break;
            }
        }

        void ReloadOscClocks() {
            SetNodeFreq(ClkSourceId_Osc,  OscFreqKhz);
            SetNodeFreq(ClkSourceId_ClkS, ClkSFreqKhz);

            AMS_ABORT_UNLESS((ReadCarReg(CLK_RST_CONTROLLER_SPARE_REG0) & SpareReg0ClkMDivisorMask) == SpareReg0ClkMDivisorBy2);
            SetNodeFreq(ClkSourceId_ClkM, CommonDivMN32(OscFreqKhz, 1, 2, false, true));

            AMS_ABORT_UNLESS((ReadCarReg(CLK_RST_CONTROLLER_OSC_CTRL) & OscCtrlPllRefDivMask) == 0);
            SetNodeFreq(ClkSourceId_PllRef, CalcFreqShift(OscFreqKhz, 0, false, true));

            const u32 usb2_hsic_trk = ReadCarReg(CLK_RST_CONTROLLER_CLK_SOURCE_USB2_HSIC_TRK);
            SetNodeFreq(ClkSourceId_UsbTrk, CalcFreqFromDivider71(OscFreqKhz, usb2_hsic_trk & ClkSourceDivisorMask, false, true));
        }

        void ReloadPllC(u32 pll_ref_khz) {
            SetNodeFreq(ClkSourceId_PllC0, CalcSimplePllFreq(pll_ref_khz, ReadPllBase(CLK_RST_CONTROLLER_PLLC_BASE, PllcBaseLayout)));

            {
                const u32 pllc_out = ReadCarReg(CLK_RST_CONTROLLER_PLLC_OUT);
                const u32 ratio    = (pllc_out >> PllOut1RatioShift) & PllOut1RatioMask;
                SetNodeFreq(ClkSourceId_PllC1, CalcFreqFromDivider71(GetNodeFreq(ClkSourceId_PllC0), ratio, (pllc_out & PllOutBypass) != 0, (pllc_out & PllOut1Enable) == PllOut1Enable));
            }

            SetNodeFreq(ClkSourceId_PllC2, CalcSimplePllFreq(pll_ref_khz, ReadPllBase(CLK_RST_CONTROLLER_PLLC2_BASE, PllcBaseLayout)));
            SetNodeFreq(ClkSourceId_PllC3, CalcSimplePllFreq(pll_ref_khz, ReadPllBase(CLK_RST_CONTROLLER_PLLC3_BASE, PllcBaseLayout)));
        }

        void ReloadPllM(u32 pll_ref_khz) {
            const auto pllm_base = ReadPllBase(CLK_RST_CONTROLLER_PLLM_BASE, PllmBaseLayout);
            if (IsMariko()) {
                SetNodeFreq(ClkSourceId_PllM, CalcPllFreq(FindPllIndex("PLLM"), pll_ref_khz, pllm_base, false));
            } else {
                SetNodeFreq(ClkSourceId_PllM, CalcSimplePllFreq(pll_ref_khz, pllm_base));
            }

            const auto pllmb_base = ReadPllBase(CLK_RST_CONTROLLER_PLLMB_BASE, PllmBaseLayout);
            if (IsMariko()) {
                SetNodeFreq(ClkSourceId_PllMB, CalcPllFreq(FindPllIndex("PLLMB"), pll_ref_khz, pllmb_base, false));
            } else {
                SetNodeFreq(ClkSourceId_PllMB, CalcSimplePllFreq(pll_ref_khz, pllmb_base));
            }
        }

        void ReloadPllD(u32 pll_ref_khz) {
            const u32 plld_khz = CalcPllFreq(FindPllIndex("PLLD0"), pll_ref_khz, ReadPllBase(CLK_RST_CONTROLLER_PLLD_BASE, PlldBaseLayout), true);
            SetNodeFreq(ClkSourceId_PllD0, CalcFreqShift(plld_khz, 1, false, true));

            SetNodeFreq(ClkSourceId_PllD2, CalcPllFreq(FindPllIndex("PLLD2"), pll_ref_khz, ReadPllBase(CLK_RST_CONTROLLER_PLLD2_BASE, Plld2BaseLayout), false));
        }

        void ReloadPllRefe(u32 pll_ref_khz) {
            const auto pllrefe_base = ReadPllBase(CLK_RST_CONTROLLER_PLLREFE_BASE, PllrefeBaseLayout);
            SetNodeFreq(ClkSourceId_PllREFE0, CalcSimplePllFreq(pll_ref_khz, pllrefe_base));
            SetNodeFreq(ClkSourceId_PllREFEv, GetNodeFreq(ClkSourceId_PllREFE0) * GetPllPDivider(pllrefe_base.divp));

            const u32 pllrefe_out = ReadCarReg(CLK_RST_CONTROLLER_PLLREFE_OUT);
            const u32 ratio       = (pllrefe_out >> PllOut1RatioShift) & PllOut1RatioMask;
            SetNodeFreq(ClkSourceId_PllREFE1, CalcFreqFromDivider71(GetNodeFreq(ClkSourceId_PllREFEv), ratio, (pllrefe_out & PllOutBypass) != 0, (pllrefe_out & PllOut1Enable) == PllOut1Enable));
        }

        void ReloadPllE(u32 pll_ref_khz) {
            SetNodeFreq(ClkSourceId_PllE0, CalcSimplePllFreq(pll_ref_khz, ReadPllBase(CLK_RST_CONTROLLER_PLLE_BASE, PlleBaseLayout)));
        }

        void ReloadPllU(u32 pll_ref_khz) {
            const auto pllu_base = ReadPllBase(CLK_RST_CONTROLLER_PLLU_BASE, PlluBaseLayout);
            SetNodeFreq(ClkSourceId_PllU0, CalcSimplePllFreq(pll_ref_khz, pllu_base));
            SetNodeFreq(ClkSourceId_PllUv, GetNodeFreq(ClkSourceId_PllU0) * GetPllPDivider(pllu_base.divp));

            {
                const u32 pllu_outa = ReadCarReg(CLK_RST_CONTROLLER_PLLU_OUTA);
                AMS_ABORT_UNLESS((pllu_outa & PllOut1Override) == 0);
                AMS_UNUSED(ReadCarReg(CLK_RST_CONTROLLER_PLLU_MISC1));
                SetNodeFreq(ClkSourceId_PllU1, (pllu_outa & PllOut1Enable) == PllOut1Enable ? GetNodeFreq(ClkSourceId_PllU0) / PllU1Divisor : 0);
            }

            {
                const u32 pllu_outa = ReadCarReg(CLK_RST_CONTROLLER_PLLU_OUTA);
                AMS_ABORT_UNLESS((pllu_outa & PllOut2Override) == 0);
                AMS_UNUSED(ReadCarReg(CLK_RST_CONTROLLER_PLLU_MISC1));
                SetNodeFreq(ClkSourceId_PllU2, (pllu_outa & PllOut2Enable) == PllOut2Enable ? GetNodeFreq(ClkSourceId_PllU0) / PllU2Divisor : 0);
            }
        }

        void ReloadPllDp(u32 pll_ref_khz) {
            SetNodeFreq(ClkSourceId_PllDP, CalcPllFreq(FindPllIndex("PLLDP"), pll_ref_khz, ReadPllBase(CLK_RST_CONTROLLER_PLLDP_BASE, PlldpBaseLayout), false));
        }

        void ReloadPllC4(u32 pll_ref_khz) {
            const auto pllc4_base = ReadPllBase(CLK_RST_CONTROLLER_PLLC4_BASE, Pllc4BaseLayout);
            SetNodeFreq(ClkSourceId_PllC40, CalcSimplePllFreq(pll_ref_khz, pllc4_base));

            const u32 pllc4_vco_khz = GetNodeFreq(ClkSourceId_PllC40) * GetPllPDivider(pllc4_base.divp);
            SetNodeFreq(ClkSourceId_PllC41, pllc4_vco_khz / PllC41Divisor);
            SetNodeFreq(ClkSourceId_PllC42, pllc4_vco_khz / PllC42Divisor);

            const u32 pllc4_out = ReadCarReg(CLK_RST_CONTROLLER_PLLC4_OUT);
            const u32 ratio     = (pllc4_out >> PllOut1RatioShift) & PllOut1RatioMask;
            SetNodeFreq(ClkSourceId_PllC43, CalcFreqFromDivider71(GetNodeFreq(ClkSourceId_PllC40), ratio, (pllc4_out & PllOutBypass) != 0, (pllc4_out & PllOut1Enable) == PllOut1Enable));
        }

        void ReloadPllP() {
            AMS_ABORT_UNLESS((ReadCarReg(CLK_RST_CONTROLLER_PLLP_BASE) & PllpBaseDivMBit0) == 0);
            SetNodeFreq(ClkSourceId_PllP0, PllP0FreqKhz);
            SetNodeFreq(ClkSourceId_PllP2, PllP2FreqKhz);

            {
                const u32 pllp_outa = ReadCarReg(CLK_RST_CONTROLLER_PLLP_OUTA);
                AMS_ABORT_UNLESS((pllp_outa & PllOut1Override) == 0);
                AMS_UNUSED(ReadCarReg(CLK_RST_CONTROLLER_PLLP_OUTB));
                SetNodeFreq(ClkSourceId_PllP3, (pllp_outa & PllOut1Enable) == PllOut1Enable ? PllP3FreqKhz : 0);
            }

            {
                const u32 pllp_outa = ReadCarReg(CLK_RST_CONTROLLER_PLLP_OUTA);
                AMS_ABORT_UNLESS((pllp_outa & PllOut2Override) == 0);
                AMS_UNUSED(ReadCarReg(CLK_RST_CONTROLLER_PLLP_OUTB));
                SetNodeFreq(ClkSourceId_PllP4, (pllp_outa & PllOut2Enable) == PllOut2Enable ? PllP4FreqKhz : 0);
            }

            {
                const u32 pllp_outc = ReadCarReg(CLK_RST_CONTROLLER_PLLP_OUTC);
                AMS_ABORT_UNLESS((pllp_outc & PllOut2Override) == 0);
                AMS_UNUSED(ReadCarReg(CLK_RST_CONTROLLER_PLLP_MISC1));
                SetNodeFreq(ClkSourceId_PllP5, (pllp_outc & PllOut2Enable) == PllOut2Enable ? PllP5FreqKhz : 0);
            }

            SetNodeFreq(ClkSourceId_PllPaux, PllPauxFreqKhz);
        }

        void ReloadUphyMgmt() {
            const u32 pex_sata_usb_rx_byp = ReadCarReg(CLK_RST_CONTROLLER_CLK_SOURCE_PEX_SATA_USB_RX_BYP);
            const u32 divisor             = pex_sata_usb_rx_byp & PexSataUsbRxBypDivisorMask;
            SetNodeFreq(ClkSourceId_UphyMgmt, CalcFreqFromDivider71(PllP0FreqKhz, divisor, false, (pex_sata_usb_rx_byp & PexSataUsbRxBypEnable) != 0));
        }

        void ReloadPllA(u32 pll_ref_khz) {
            SetNodeFreq(ClkSourceId_PllA, CalcPllFreq(FindPllIndex("PLLA"), pll_ref_khz, ReadPllBase(CLK_RST_CONTROLLER_PLLA_BASE, PllaBaseLayout), false));

            {
                const u32 plla_out = ReadCarReg(CLK_RST_CONTROLLER_PLLA_OUT);
                const u32 ratio    = (plla_out >> PllOut1RatioShift) & PllOut1RatioMask;
                SetNodeFreq(ClkSourceId_PllA0, CalcFreqFromDivider71(GetNodeFreq(ClkSourceId_PllA), ratio, false, (plla_out & PllOut1Enable) == PllOut1Enable));
            }

            SetNodeFreq(ClkSourceId_PllA1, CalcSimplePllFreq(pll_ref_khz, ReadPllBase(CLK_RST_CONTROLLER_PLLA1_BASE, Plla1BaseLayout)));
        }

        void ReloadUtmiPll(u32 pll_ref_khz) {
            const bool enable    = (ReadCarReg(CLK_RST_CONTROLLER_UTMIP_PLL_CFG1) & UtmipPllCfg1ForcePllEnablePowerdown) == 0;
            const u32 utmip_cfg0 = ReadCarReg(CLK_RST_CONTROLLER_UTMIP_PLL_CFG0);

            const PllBaseValues utmip_pll = {
                .divm   = (utmip_cfg0 >> UtmipPllCfg0DivMShift) & UtmipPllCfg0DivMMask,
                .divn   = (utmip_cfg0 >> UtmipPllCfg0DivNShift) & UtmipPllCfg0DivNMask,
                .divp   = UtmipPllDivP,
                .bypass = false,
                .enable = enable,
            };
            SetNodeFreq(ClkSourceId_UtmiPll, CalcSimplePllFreq(pll_ref_khz, utmip_pll));
        }

        void ReloadCpuBus(u32 &source_shift) {
            const u32 cclkg_burst_policy = ReadCarReg(CLK_RST_CONTROLLER_CCLKG_BURST_POLICY);
            const u32 state              = cclkg_burst_policy >> BurstPolicyStateShift;

            u32 cpu_bus_khz = GetNodeFreq(ClkSourceId_ClkS);
            if (state != BurstPolicyState_Stdby) {
                UpdateBurstPolicySourceShift(state, source_shift);
                const u32 source_khz    = GetNodeFreq(CclkgSources[(cclkg_burst_policy >> source_shift) & CclkgSourceMask]);
                const u32 super_divider = ReadCarReg(CLK_RST_CONTROLLER_SUPER_CCLKG_DIVIDER);
                const u32 dividend      = ((super_divider >> SuperDividerDividendShift) & SuperDividerDividendMask) + 1;
                const u32 divisor       = ((super_divider >> SuperDividerDivisorShift) & SuperDividerDivisorMask) + 1;
                const bool enable       = (super_divider & SuperDividerEnable) != 0;
                cpu_bus_khz = CommonDivMN32(source_khz, dividend, divisor, !enable, enable);
            }

            SetNodeFreq(ClkSourceId_CpuBus, cpu_bus_khz);
        }

        void ReloadSystemBus(u32 &source_shift) {
            const u32 sclk_burst_policy = ReadCarReg(CLK_RST_CONTROLLER_SCLK_BURST_POLICY);
            const u32 state             = sclk_burst_policy >> BurstPolicyStateShift;

            u32 source_khz = GetNodeFreq(ClkSourceId_ClkS);
            if (state != BurstPolicyState_Stdby) {
                UpdateBurstPolicySourceShift(state, source_shift);
                source_khz = GetNodeFreq(SclkSources[(sclk_burst_policy >> source_shift) & SclkSourceMask]);
            }

            const u32 sys_divisor = ReadCarReg(CLK_RST_CONTROLLER_CLK_SOURCE_SYS) & ClkSourceDivisorMask;
            const u32 sys_khz     = CalcFreqFromDivider71(source_khz, sys_divisor, false, true);

            const u32 super_divider = ReadCarReg(CLK_RST_CONTROLLER_SUPER_SCLK_DIVIDER);
            const u32 dividend      = ((super_divider >> SuperDividerDividendShift) & SuperDividerDividendMask) + 1;
            const u32 divisor       = ((super_divider >> SuperDividerDivisorShift) & SuperDividerDivisorMask) + 1;
            const bool enable       = (super_divider & SuperDividerEnable) != 0;
            SetNodeFreq(ClkSourceId_SystemBus, CommonDivMN32(sys_khz, dividend, divisor, !enable, enable));
        }

        void ReloadAhbApb() {
            const u32 system_rate = ReadCarReg(CLK_RST_CONTROLLER_CLK_SYSTEM_RATE);

            const u32 ahb_divisor   = ((system_rate >> SystemRateAhbRateShift) & SystemRateAhbRateMask) + 1;
            const bool hclk_disable = (system_rate & SystemRateHclkDisable) != 0;
            SetNodeFreq(ClkSourceId_Ahb, CommonDivMN32(GetNodeFreq(ClkSourceId_SystemBus), 1, ahb_divisor, hclk_disable, !hclk_disable));

            const u32 apb_divisor   = ((system_rate >> SystemRateApbRateShift) & SystemRateApbRateMask) + 1;
            const bool pclk_disable = (system_rate & SystemRatePclkDisable) != 0;
            SetNodeFreq(ClkSourceId_Apb, CommonDivMN32(GetNodeFreq(ClkSourceId_Ahb), 1, apb_divisor, pclk_disable, !pclk_disable));
        }

        void ReloadAclk(u32 &source_shift) {
            const u32 aclk_burst_policy = ReadCarReg(CLK_RST_CONTROLLER_ACLK_BURST_POLICY);
            const u32 state             = aclk_burst_policy >> BurstPolicyStateShift;

            u32 source     = 0;
            u32 source_khz = GetNodeFreq(ClkSourceId_ClkM);
            if (state != BurstPolicyState_Stdby) {
                UpdateBurstPolicySourceShift(state, source_shift);
                source     = (aclk_burst_policy >> source_shift) & AclkSourceMask;
                source_khz = GetNodeFreq(AclkSources[source]);
            }

            const u32 super_divider = ReadCarReg(CLK_RST_CONTROLLER_SUPER_ACLK_DIVIDER);
            if (source != AclkSourcePllA1Undivided && source != AclkSourcePllAUndivided) {
                source_khz = CalcFreqFromDivider71(source_khz, (super_divider >> SuperAclkDividerShift) & SuperAclkDividerMask, false, true);
            }

            const u32 dividend = ((super_divider >> SuperDividerDividendShift) & SuperDividerDividendMask) + 1;
            const u32 divisor  = ((super_divider >> SuperDividerDivisorShift) & SuperDividerDivisorMask) + 1;
            const bool enable  = (super_divider & SuperDividerEnable) != 0;
            SetNodeFreq(ClkSourceId_Aclk, CommonDivMN32(source_khz, dividend, divisor, !enable, enable));
        }
    }

    ClkSourceNode &GetSourceNode(ClkSourceId id) {
        AMS_ABORT_UNLESS(id < ClkSourceId_Count);
        return g_clk_source_node_table[id];
    }

    void SetNodeFreq(ClkSourceId id, u32 khz) {
        auto &node = GetSourceNode(id);

        node.freq_khz = khz;
        if (khz != 0) {
            node.last_freq_khz = khz;
        }
    }

    u32 GetNodeFreq(ClkSourceId id) {
        return GetSourceNode(id).freq_khz;
    }

    void ReloadSourceClocks() {
        /* Welcome to this bullshit. */
        /* Start with osc clocks. */
        ReloadOscClocks();

        /* We use this ref for reloading the others. */
        const u32 pll_ref_khz = GetNodeFreq(ClkSourceId_PllRef);

        /* Enjoy suffering. */
        ReloadPllC(pll_ref_khz);
        ReloadPllM(pll_ref_khz);
        ReloadPllD(pll_ref_khz);
        ReloadPllRefe(pll_ref_khz);
        ReloadPllE(pll_ref_khz);
        ReloadPllU(pll_ref_khz);
        ReloadPllDp(pll_ref_khz);
        ReloadPllC4(pll_ref_khz);
        ReloadPllP();

        /* Reload the ugly mogment. */
        if (IsMariko()) {
            ReloadUphyMgmt();
        }

        /* Two more plls */
        ReloadPllA(pll_ref_khz);
        ReloadUtmiPll(pll_ref_khz);

        /* Buses and stuff */
        u32 source_shift = 0;
        ReloadCpuBus(source_shift);
        ReloadSystemBus(source_shift);
        ReloadAhbApb();
        ReloadAclk(source_shift);

        /* Get therapy. */
    }

}
