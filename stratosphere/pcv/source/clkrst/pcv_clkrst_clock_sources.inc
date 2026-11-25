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

#define CLK_NODE(ID, NAME, PARENT) { ID, NAME, PARENT, 0, 0, 0 }

constinit ClkSourceNode g_clk_source_node_table[ClkSourceId_Count] = {
    CLK_NODE(ClkSourceId_Invalid,   "Invalid",   "None"),
    CLK_NODE(ClkSourceId_Osc,       "OSC",       "OSC"),
    CLK_NODE(ClkSourceId_ClkS,      "ClkS",      "ClkS"),
    CLK_NODE(ClkSourceId_ClkM,      "ClkM",      "OSC"),
    CLK_NODE(ClkSourceId_PllA0,     "PllA0",     "PllA"),
    CLK_NODE(ClkSourceId_PllA,      "PllA",      "PllRef"),
    CLK_NODE(ClkSourceId_PllA1,     "PllA1",     "PllRef"),
    CLK_NODE(ClkSourceId_PllC0,     "PllC0",     "PllRef"),
    CLK_NODE(ClkSourceId_PllC1,     "PllC1",     "PllC0"),
    CLK_NODE(ClkSourceId_PllC2,     "PllC2",     "PllRef"),
    CLK_NODE(ClkSourceId_PllC3,     "PllC3",     "PllRef"),
    CLK_NODE(ClkSourceId_PllC40,    "PllC40",    "PllRef"),
    CLK_NODE(ClkSourceId_PllC41,    "PllC41",    "PllC40"),
    CLK_NODE(ClkSourceId_PllC42,    "PllC42",    "PllC40"),
    CLK_NODE(ClkSourceId_PllC43,    "PllC43",    "PllC40"),
    CLK_NODE(ClkSourceId_PllD0,     "PllD0",     "PllRef"),
    CLK_NODE(ClkSourceId_PllD2,     "PllD2",     "PllRef"),
    CLK_NODE(ClkSourceId_PllDP,     "PllDP",     "PllRef"),
    CLK_NODE(ClkSourceId_PllE0,     "PllE0",     "PllRef"),
    CLK_NODE(ClkSourceId_PllM,      "PllM",      "PllRef"),
    CLK_NODE(ClkSourceId_PllMB,     "PllMB",     "PllRef"),
    CLK_NODE(ClkSourceId_PllP0,     "PllP0",     "PllRef"),
    CLK_NODE(ClkSourceId_PllP2,     "PllP2",     "PllP0"),
    CLK_NODE(ClkSourceId_PllP3,     "PllP3",     "PllP0"),
    CLK_NODE(ClkSourceId_PllP4,     "PllP4",     "PllP0"),
    CLK_NODE(ClkSourceId_PllP5,     "PllP5",     "PllP0"),
    CLK_NODE(ClkSourceId_PllPaux,   "PllPaux",   "PllP0"),
    CLK_NODE(ClkSourceId_PllREFEv,  "PllREFEv",  "PllRef"),
    CLK_NODE(ClkSourceId_PllREFE0,  "PllREFE0",  "PllRef"),
    CLK_NODE(ClkSourceId_PllREFE1,  "PllREFE1",  "PllREFEv"),
    CLK_NODE(ClkSourceId_PllUv,     "PllUv",     "PllRef"),
    CLK_NODE(ClkSourceId_PllU0,     "PllU0",     "PllRef"),
    CLK_NODE(ClkSourceId_PllU1,     "PllU1",     "PllU0"),
    CLK_NODE(ClkSourceId_PllU2,     "PllU2",     "PllU0"),
    CLK_NODE(ClkSourceId_PllX0,     "PllX0",     "PllRef"),
    CLK_NODE(ClkSourceId_UtmiPll,   "UTMIPll",   "PllRef"),
    CLK_NODE(ClkSourceId_CpuBus,    "CpuBus",    "Special"),
    CLK_NODE(ClkSourceId_SystemBus, "SystemBus", "Special"),
    CLK_NODE(ClkSourceId_Ahb,       "Ahb",       "Special"),
    CLK_NODE(ClkSourceId_Apb,       "Apb",       "Special"),
    CLK_NODE(ClkSourceId_Aclk,      "Aclk",      "Special"),
    CLK_NODE(ClkSourceId_Mclk,      "Mclk",      "Special"),
    CLK_NODE(ClkSourceId_PllRef,    "PllRef",    "OSC"),
    CLK_NODE(ClkSourceId_DvfsClk,   "DvfsClk",   "PllRef"),
    CLK_NODE(ClkSourceId_Gpu,       "GPU",       "PllRef"),
    CLK_NODE(ClkSourceId_UsbTrk,    "UsbTrk",    "OSC"),
    CLK_NODE(ClkSourceId_UphyMgmt,  "UphyMgmt",  "PllP0"),
};
#undef CLK_NODE
