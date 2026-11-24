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

constexpr ClkPllCfg Pllx0CfgT210[] = {
    { 19200000, 1000000000, 52, 1, 1, 0, 0 },
    {                                      },
};

constexpr ClkPllCfg Pllc0CfgT210[] = {
    { 38400000, 510000000, 79, 3, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Pllc2CfgT210[] = {
    { 38400000, 510000000, 79, 3, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Pllc3CfgT210[] = {
    { 38400000, 510000000, 79, 3, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Plla1CfgT210[] = {
    { 38400000, 510000000, 79, 3, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg PllaCfgT210[] = {
    { 38400000, 282240000, 44, 3, 2, 0, 62259 },
    { 38400000, 368640000, 57, 3, 2, 0, 819 },
    {                                         },
};

constexpr ClkPllCfg Plld0CfgT210[] = {
    { 38400000, 594000000, 30, 1, 2, 0, 3584 },
    {                                        },
};

constexpr ClkPllCfg Plld2CfgT210[] = {
    { 38400000, 594000000, 30, 1, 2, 0, 3584 },
    {                                        },
};

constexpr ClkPllCfg PlldpCfgT210[] = {
    { 38400000, 270000000, 28, 1, 4, 0, 62464 },
    {                                         },
};

constexpr ClkPllCfg Pllc40CfgT210[] = {
    { 38400000, 998400000, 104, 4, 1, 0, 0 },
    {                                      },
};

constexpr ClkPllCfg PllmCfgT210[] = {
    { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF },
};

constexpr ClkPllCfg PllmbCfgT210[] = {
    { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF },
};

constexpr ClkPllCfg Pllp0CfgT210[] = {
    { 38400000, 408000000, 85, 8, 1, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Pllrefe0CfgT210[] = {
    { 38400000, 624000000, 65, 4, 1, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Pllu0CfgT210[] = {
    { 38400000, 240000000, 25, 2, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Plle0CfgT210[] = {
    { 38400000, 100000000, 125, 2, 24, 0, 0 },
    {                                       },
};

constexpr ClkPllCfg UtmipllCfgT210[] = {
    { 38400000, 480000000, 25, 1, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllSdm PllaSdm  = { 0x2, 0x4000000,  0x1, 0x0 };
constexpr ClkPllSdm Plld0Sdm = { 0x0, 0x10000,    0x0, 0x0 };
constexpr ClkPllSdm Plld2Sdm = { 0x1, 0x80000000, 0x3, 0x0 };
constexpr ClkPllSdm PlldpSdm = { 0x1, 0x80000000, 0x3, 0x0 };

constexpr ClkPllParam Pllx0Param    = { 2700000000, 12000000, 800000000,  12000000, 38400000, 1350000000, 2700000000, 300, 0,         0x0, Pllx0CfgT210,    2, 0x0, 0x0,        0x0, 0x710004FCB0 };
constexpr ClkPllParam Pllc0Param    = { 1130000000, 12000000, 700000000,  12000000, 50000000, 600000000,  1200000000, 300, 0,         0x0, Pllc0CfgT210,    2, 0x0, 0x0,        0x0, 0x710004FDD0 };
constexpr ClkPllParam Pllc2Param    = { 1130000000, 12000000, 700000000,  12000000, 50000000, 600000000,  1200000000, 300, 0,         0x0, Pllc2CfgT210,    2, 0x0, 0x0,        0x0, 0x710004FDD0 };
constexpr ClkPllParam Pllc3Param    = { 1130000000, 12000000, 700000000,  12000000, 50000000, 600000000,  1200000000, 300, 0,         0x0, Pllc3CfgT210,    2, 0x0, 0x0,        0x0, 0x710004FDD0 };
constexpr ClkPllParam Plla1Param    = { 1130000000, 12000000, 700000000,  12000000, 50000000, 600000000,  1200000000, 300, 0,         0x0, Plla1CfgT210,    2, 0x0, 0x0,        0x0, 0x710004FDD0 };
constexpr ClkPllParam PllaParam     = { 1000000000, 12000000, 800000000,  12000000, 19200000, 500000000,  1000000000, 300, 0,         0x0, PllaCfgT210,     3, 0x2, 0x0,        0x0, 0x710004FEB0 };
constexpr ClkPllParam Plld0Param    = { 1500000000, 12000000, 800000000,  12000000, 38400000, 750000000,  1500000000, 300, 0,         0x0, Plld0CfgT210,    2, 0x1, 0x0,        0x0, 0x710004FF60 };
constexpr ClkPllParam Plld2Param    = { 1130000000, 12000000, 800000000,  12000000, 38400000, 750000000,  1500000000, 300, 0,         0x0, Plld2CfgT210,    2, 0x1, 0x0,        0x0, 0x7100050040 };
constexpr ClkPllParam PlldpParam    = { 1130000000, 12000000, 800000000,  12000000, 38400000, 750000000,  1500000000, 300, 270000000, 0x0, PlldpCfgT210,    2, 0x1, 0x0,        0x0, 0x7100050040 };
constexpr ClkPllParam Pllc40Param   = { 1080000000, 9600000,  800000000,  9600000,  19200000, 500000000,  1080000000, 300, 998400000, 0x0, Pllc40CfgT210,   2, 0x0, 0x0,        0x0, 0x7100050040 };
constexpr ClkPllParam PllmParam     = { 1866000000, 9600000,  500000000,  9600000,  19200000, 800000000,  1866000000, 300, 0,         0x0, PllmCfgT210,     1, 0x0, 0x0,        0x0, 0x7100050180 };
constexpr ClkPllParam PllmbParam    = { 1866000000, 9600000,  500000000,  9600000,  19200000, 800000000,  1866000000, 300, 0,         0x0, PllmbCfgT210,    1, 0x0, 0x0,        0x0, 0x7100050180 };
constexpr ClkPllParam Pllp0Param    = { 700000000,  9600000,  800000000,  9600000,  19200000, 350000000,  700000000,  300, 408000000, 0x0, Pllp0CfgT210,    2, 0x0, 0x0,        0x0, 0,     };
constexpr ClkPllParam Pllrefe0Param = { 700000000,  9600000,  800000000,  9600000,  19200000, 350000000,  700000000,  300, 624000000, 0x0, Pllrefe0CfgT210, 2, 0x0, 0x0,        0x0, 0x7100050220 };
constexpr ClkPllParam Pllu0Param    = { 700000000,  9600000,  800000000,  9600000,  19200000, 350000000,  700000000,  300, 240000000, 0x0, Pllu0CfgT210,    2, 0x0, 0x0,        0x0, 0x71000502D0 };
constexpr ClkPllParam Plle0Param    = { 100000000,  12000000, 800000000,  12000000, 38400000, 1600000000, 2500000000, 300, 100000000, 0x0, Plle0CfgT210,    2, 0x0, 0x23010021, 0x0, 0      };
constexpr ClkPllParam UtmipllParam  = { 500000000,  12000000, 1000000000, 12000000, 38400000, 500000000,  1000000000, 300, 480000000, 0x0, UtmipllCfgT210,  2, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam PllGpuParam   = { 921600000,  0,        0,          0,        0,        0,          0,          0,   0,         0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllc1Param    = { 1130000000, 0,        0,          0,        0,        0,          0,          0,   0,         0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllc43Param   = { 1080000000, 0,        0,          0,        0,        0,          0,          0,   0,         0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllp3Param    = { 700000000,  0,        0,          0,        0,        0,          0,          0,   102000000, 0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllp4Param    = { 700000000,  0,        0,          0,        0,        0,          0,          0,   102000000, 0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllp5Param    = { 700000000,  0,        0,          0,        0,        0,          0,          0,   204000000, 0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Plla0Param    = { 1000000000, 0,        0,          0,        0,        0,          0,          0,   0,         0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllrefe1Param = { 700000000,  0,        0,          0,        0,        0,          0,          0,   0,         0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllu1Param    = { 700000000,  0,        0,          0,        0,        0,          0,          0,   48000000,  0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllu2Param    = { 700000000,  0,        0,          0,        0,        0,          0,          0,   60000000,  0x0, nullptr,         0, 0x0, 0x0,        0x0, 0      };

constexpr ClkPllInfo PllInfoTableT210[] = {
    { "PLLX0",    ClkPllType_Pll,    224,  228,  0,    0, 0x100,    31, 30, 29, 27, {}, 0,  20, 0x1F00000,  8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllx0Param),    {  228, 1296, 1300, 1304, 1520, 1524, }, {}, nullptr,                  {}, },
    { "PLLC0",    ClkPllType_Pll,    128,  136,  0,    0, 0x1,      31, 30, 29, 26, {}, 0,  20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllc0Param),    {  136,  140, 1488, 1492,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLC2",    ClkPllType_Pll,    1256, 1260, 0,    0, 0x2,      31, 30, 29, 26, {}, 0,  20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllc2Param),    { 1260, 1264, 1268, 1272,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLC3",    ClkPllType_Pll,    1276, 1280, 0,    0, 0x4,      31, 30, 29, 26, {}, 0,  20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllc3Param),    { 1280, 1284, 1288, 1292,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLA1",    ClkPllType_Pll,    1700, 1704, 0,    0, 0x8000,   31, 30, 29, 26, {}, 0,  20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Plla1Param),    { 1704, 1708, 1712, 1716,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLA",     ClkPllType_Pll,    176,  188,  0,    0, 0x20,     31, 30, 29, 27, {}, 0,  20, 0x1F00000,  8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PllaParam),     {  188,  184, 1496,    0,    0,    0, }, {}, std::addressof(PllaSdm),  {}, },
    { "PLLD0",    ClkPllType_Pll,    208,  220,  0,    0, 0x40,     31, 30, 29, 27, {}, 0,  20, 0x700000,   11, 0x7F800, 0, 0xFF, 0, 21, 0, 0,  0x0,        0,  0,  std::addressof(Plld0Param),    {  220,  216,    0,    0,    0,    0, }, {}, std::addressof(Plld0Sdm), {}, },
    { "PLLD2",    ClkPllType_Pll,    1208, 1212, 0,    0, 0x80,     31, 30, 29, 27, {}, 0,  19, 0xF80000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Plld2Param),    { 1212, 1392, 1396, 1400,    0,    0, }, {}, std::addressof(Plld2Sdm), {}, },
    { "PLLDP",    ClkPllType_Pll,    1424, 1428, 0,    0, 0x1000,   31, 30, 29, 27, {}, 0,  19, 0xF80000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PlldpParam),    { 1428, 1432, 1436, 1440,    0,    0, }, {}, std::addressof(PlldpSdm), {}, },
    { "PLLC40",   ClkPllType_Pll,    1444, 1448, 0,    0, 0x2000,   31, 30, 29, 27, {}, 0,  19, 0xF80000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllc40Param),   { 1448,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLM",     ClkPllType_Pll,    144,  156,  0,    0, 0x8,      31, 30, 29, 27, {}, 0,  20, 0x1F00000,  8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PllmParam),     {  156,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLMB",    ClkPllType_Pll,    1512, 1516, 0,    0, 0x80000,  0,  30, 0,  27, {}, 0,  20, 0x1F00000,  8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PllmbParam),    { 1516,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLP0",    ClkPllType_Pll,    160,  172,  0,    0, 0x10,     31, 30, 29, 27, {}, 28, 20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllp0Param),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLREFE0", ClkPllType_Pll,    1220, 1224, 0,    0, 0x400,    31, 30, 29, 27, {}, 0,  16, 0x1F0000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllrefe0Param), { 1224,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLU0",    ClkPllType_Pll,    192,  204,  0,    0, 0x200,    31, 30, 29, 27, {}, 24, 16, 0x1F0000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllu0Param),    {  204,  200,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLE0",    ClkPllType_Pll,    232,  236,  0,    0, 0x800,    0,  31, 0,  11, {}, 0,  24, 0x1F000000, 8,  0xFF00,  0, 0xFF, 0, 0,  9, 0,  0x0,        0,  0,  std::addressof(Plle0Param),    {  236,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "UTMIPLL",  ClkPllType_Pll,    0,    0,    0,    0, 0x200000, 0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 0,  0x0,        0,  0,  std::addressof(UtmipllParam),  {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "GPU",      ClkPllType_Pll,    0,    0,    0,    0, 0x100000, 0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PllGpuParam),   {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLC1",    ClkPllType_PllOut, 0,    0,    132,  0, 0x20001,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllc1Param),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLC43",   ClkPllType_PllOut, 0,    0,    1508, 0, 0x20100,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllc43Param),   {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLP3",    ClkPllType_PllOut, 0,    0,    168,  0, 0x20010,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllp3Param),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLP4",    ClkPllType_PllOut, 0,    0,    168,  0, 0x20020,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 24, 0xFF000000, 17, 16, std::addressof(Pllp4Param),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLP5",    ClkPllType_PllOut, 0,    0,    1660, 0, 0x20080,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 24, 0xFF000000, 17, 16, std::addressof(Pllp5Param),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLA0",    ClkPllType_PllOut, 0,    0,    180,  0, 0x20040,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Plla0Param),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLREFE1", ClkPllType_PllOut, 0,    0,    1228, 0, 0x20800,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllrefe1Param), {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLU1",    ClkPllType_PllOut, 0,    0,    196,  0, 0x20200,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllu1Param),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
    { "PLLU2",    ClkPllType_PllOut, 0,    0,    196,  0, 0x20400,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 24, 0xFF000000, 17, 16, std::addressof(Pllu2Param),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                  {}, },
};

constinit ClkSystemInfo ClkSystemInfoTableT210[] = {
    { "SCLK", ClkSystemInfoType_Sclk, 37, nullptr, 408000,  0, nullptr, nullptr, },
    { "CCLK", ClkSystemInfoType_Cclk, 36, nullptr, 2000000, 0, nullptr, nullptr, },
    { "HCLK", ClkSystemInfoType_Hclk, 38, nullptr, 408000,  0, nullptr, nullptr, },
    { "PCLK", ClkSystemInfoType_Pclk, 39, nullptr, 204000,  0, nullptr, nullptr, },
    { "EMC",  ClkSystemInfoType_Emc,  41, nullptr, 1600000, 0, nullptr, nullptr, },
    { "ACLK", ClkSystemInfoType_Aclk, 40, nullptr, 844800,  0, nullptr, nullptr, },
};

constexpr ClkPllCfg Pllx0CfgT210B01[] = {
    { 38400000, 1000000000, 104, 2, 2, 0, 0 },
    {                                       },
};

constexpr ClkPllCfg Pllc0CfgT210B01[] = {
    { 38400000, 510000000, 53, 2, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Pllc2CfgT210B01[] = {
    { 38400000, 510000000, 53, 2, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Pllc3CfgT210B01[] = {
    { 38400000, 510000000, 53, 2, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Plla1CfgT210B01[] = {
    { 38400000, 510000000, 53, 2, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg PllaCfgT210B01[] = {
    { 38400000, 282240000, 29, 2, 2, 0, 64716 },
    { 38400000, 368640000, 38, 2, 2, 0, 64716 },
    {                                         },
};

constexpr ClkPllCfg Plld0CfgT210B01[] = {
    { 38400000, 594000000, 30, 1, 2, 0, 3584 },
    {                                        },
};

constexpr ClkPllCfg Plld2CfgT210B01[] = {
    { 38400000, 594000000, 30, 1, 2, 0, 3584 },
    {                                        },
};

constexpr ClkPllCfg PlldpCfgT210B01[] = {
    { 38400000, 270000000, 42, 1, 6, 0, 62976 },
    {                                         },
};

constexpr ClkPllCfg Pllc40CfgT210B01[] = {
    { 38400000, 998400000, 52, 2, 1, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg PllmCfgT210B01[] = {
    { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF },
};

constexpr ClkPllCfg PllmbCfgT210B01[] = {
    { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF },
};

constexpr ClkPllCfg Pllp0CfgT210B01[] = {
    { 38400000, 408000000, 85, 8, 1, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Pllrefe0CfgT210B01[] = {
    { 38400000, 624000000, 65, 4, 1, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Pllu0CfgT210B01[] = {
    { 38400000, 240000000, 25, 2, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllCfg Plle0CfgT210B01[] = {
    { 38400000, 100000000, 125, 2, 24, 0, 0 },
    {                                       },
};

constexpr ClkPllCfg UtmipllCfgT210B01[] = {
    { 38400000, 480000000, 25, 1, 2, 0, 0 },
    {                                     },
};

constexpr ClkPllSdm PllaSdmT210B01  = { 0x2, 0x4000000,  0x1, 0x0 };
constexpr ClkPllSdm Plld0SdmT210B01 = { 0x0, 0x10000,    0x0, 0x0 };
constexpr ClkPllSdm Plld2SdmT210B01 = { 0x1, 0x80000000, 0x3, 0x0 };
constexpr ClkPllSdm PlldpSdmT210B01 = { 0x1, 0x80000000, 0x3, 0x0 };
constexpr ClkPllSdm PllmSdmT210B01  = { 0x1, 0x80000000, 0x3, 0x0 };
constexpr ClkPllSdm PllmbSdmT210B01 = { 0x1, 0x80000000, 0x3, 0x0 };

constexpr ClkPllParam Pllx0ParamT210B01    = { 3000000000, 13500000, 800000000, 13500000, 38400000, 1300000000, 3000000000, 300, 0,         0x0, Pllx0CfgT210B01,    2, 0x2, 0x0,        0x0, 0x710004FD40 };
constexpr ClkPllParam Pllc0ParamT210B01    = { 1200000000, 19200000, 700000000, 19200000, 38400000, 600000000,  1200000000, 300, 0,         0x0, Pllc0CfgT210B01,    2, 0x2, 0x0,        0x0, 0x710004FE40 };
constexpr ClkPllParam Pllc2ParamT210B01    = { 1200000000, 19200000, 700000000, 19200000, 38400000, 600000000,  1200000000, 300, 0,         0x0, Pllc2CfgT210B01,    2, 0x2, 0x0,        0x0, 0x710004FE40 };
constexpr ClkPllParam Pllc3ParamT210B01    = { 1200000000, 19200000, 700000000, 19200000, 38400000, 600000000,  1200000000, 300, 0,         0x0, Pllc3CfgT210B01,    2, 0x2, 0x0,        0x0, 0x710004FE40 };
constexpr ClkPllParam Plla1ParamT210B01    = { 1200000000, 19200000, 700000000, 19200000, 38400000, 600000000,  1200000000, 300, 0,         0x0, Plla1CfgT210B01,    2, 0x2, 0x0,        0x0, 0x710004FE40 };
constexpr ClkPllParam PllaParamT210B01     = { 1000000000, 12000000, 800000000, 12000000, 38400000, 500000000,  1000000000, 300, 0,         0x0, PllaCfgT210B01,     3, 0x2, 0x0,        0x0, 0x710004FF10 };
constexpr ClkPllParam Plld0ParamT210B01    = { 1620000000, 13500000, 800000000, 13500000, 38400000, 800000000,  1620000000, 300, 0,         0x0, Plld0CfgT210B01,    2, 0x1, 0x0,        0x0, 0x710004FFD0 };
constexpr ClkPllParam Plld2ParamT210B01    = { 1500000000, 13500000, 800000000, 13500000, 38400000, 780000000,  1620000000, 300, 0,         0x0, Plld2CfgT210B01,    2, 0x1, 0x0,        0x0, 0x71000500E0 };
constexpr ClkPllParam PlldpParamT210B01    = { 1500000000, 13500000, 800000000, 13500000, 38400000, 780000000,  1620000000, 300, 270000000, 0x0, PlldpCfgT210B01,    2, 0x0, 0x0,        0x0, 0x71000500E0 };
constexpr ClkPllParam Pllc40ParamT210B01   = { 1000000000, 12000000, 800000000, 12000000, 38400000, 500000000,  1000000000, 300, 998400000, 0x0, Pllc40CfgT210B01,   2, 0x0, 0x0,        0x0, 0x71000500E0 };
constexpr ClkPllParam PllmParamT210B01     = { 2133000000, 19200000, 800000000, 19200000, 38400000, 1050000000, 2133000000, 300, 0,         0x0, PllmCfgT210B01,     1, 0x0, 0x0,        0x0, 0x71000501D0 };
constexpr ClkPllParam PllmbParamT210B01    = { 2133000000, 19200000, 800000000, 19200000, 38400000, 1050000000, 2133000000, 300, 0,         0x0, PllmbCfgT210B01,    1, 0x0, 0x0,        0x0, 0x71000501D0 };
constexpr ClkPllParam Pllp0ParamT210B01    = { 700000000,  9600000,  800000000, 9600000,  19200000, 350000000,  700000000,  300, 408000000, 0x0, Pllp0CfgT210B01,    2, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllrefe0ParamT210B01 = { 700000000,  9600000,  800000000, 9600000,  19200000, 350000000,  700000000,  300, 624000000, 0x0, Pllrefe0CfgT210B01, 2, 0x0, 0x0,        0x0, 0x7100050270 };
constexpr ClkPllParam Pllu0ParamT210B01    = { 700000000,  9600000,  800000000, 9600000,  19200000, 350000000,  700000000,  300, 240000000, 0x0, Pllu0CfgT210B01,    2, 0x0, 0x0,        0x0, 0x7100050320 };
constexpr ClkPllParam Plle0ParamT210B01    = { 100000000,  19200000, 800000000, 19200000, 38400000, 1250000000, 2500000000, 300, 100000000, 0x0, Plle0CfgT210B01,    2, 0x0, 0x20010025, 0x0, 0      };
constexpr ClkPllParam UtmipllParamT210B01  = { 500000000,  12000000, 800000000, 12000000, 38400000, 500000000,  1000000000, 300, 480000000, 0x0, UtmipllCfgT210B01,  2, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam PllGpuParamT210B01   = { 1300000000, 0,        0,         0,        0,        0,          0,          0,   0,         0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllc1ParamT210B01    = { 1500000000, 0,        0,         0,        0,        0,          0,          0,   0,         0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllc43ParamT210B01   = { 1000000000, 0,        0,         0,        0,        0,          0,          0,   0,         0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllp3ParamT210B01    = { 700000000,  0,        0,         0,        0,        0,          0,          0,   102000000, 0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllp4ParamT210B01    = { 700000000,  0,        0,         0,        0,        0,          0,          0,   102000000, 0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllp5ParamT210B01    = { 700000000,  0,        0,         0,        0,        0,          0,          0,   204000000, 0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Plla0ParamT210B01    = { 1000000000, 0,        0,         0,        0,        0,          0,          0,   0,         0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllrefe1ParamT210B01 = { 700000000,  0,        0,         0,        0,        0,          0,          0,   0,         0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllu1ParamT210B01    = { 700000000,  0,        0,         0,        0,        0,          0,          0,   48000000,  0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };
constexpr ClkPllParam Pllu2ParamT210B01    = { 700000000,  0,        0,         0,        0,        0,          0,          0,   60000000,  0x0, nullptr,            0, 0x0, 0x0,        0x0, 0      };

constexpr ClkPllInfo PllInfoTableT210B01[] = {
    { "PLLX0",    ClkPllType_Pll,    224,  228,  0,    0, 0x100,    31, 30, 29, 27, {}, 0,  20, 0x1F00000,  8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllx0ParamT210B01),    {  228, 1296, 1300, 1304, 1520, 1524, }, {}, nullptr,                         {}, },
    { "PLLC0",    ClkPllType_Pll,    128,  136,  0,    0, 0x1,      31, 30, 29, 26, {}, 0,  20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllc0ParamT210B01),    {  136,  140, 1488, 1492,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLC2",    ClkPllType_Pll,    1256, 1260, 0,    0, 0x2,      31, 30, 29, 26, {}, 0,  20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllc2ParamT210B01),    { 1260, 1264, 1268, 1272,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLC3",    ClkPllType_Pll,    1276, 1280, 0,    0, 0x4,      31, 30, 29, 26, {}, 0,  20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllc3ParamT210B01),    { 1280, 1284, 1288, 1292,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLA1",    ClkPllType_Pll,    1700, 1704, 0,    0, 0x8000,   31, 30, 29, 26, {}, 0,  20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Plla1ParamT210B01),    { 1704, 1708, 1712, 1716,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLA",     ClkPllType_Pll,    176,  188,  0,    0, 0x20,     31, 30, 29, 27, {}, 0,  20, 0x1F00000,  8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PllaParamT210B01),     {  188,  184, 1496,    0,    0,    0, }, {}, std::addressof(PllaSdmT210B01),  {}, },
    { "PLLD0",    ClkPllType_Pll,    208,  220,  0,    0, 0x40,     31, 30, 29, 27, {}, 0,  20, 0x700000,   11, 0x7F800, 0, 0xFF, 0, 21, 0, 0,  0x0,        0,  0,  std::addressof(Plld0ParamT210B01),    {  220,  216,    0,    0,    0,    0, }, {}, std::addressof(Plld0SdmT210B01), {}, },
    { "PLLD2",    ClkPllType_Pll,    1208, 1212, 0,    0, 0x80,     31, 30, 29, 27, {}, 0,  19, 0xF80000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Plld2ParamT210B01),    { 1212, 1392, 1396, 1400,    0,    0, }, {}, std::addressof(Plld2SdmT210B01), {}, },
    { "PLLDP",    ClkPllType_Pll,    1424, 1428, 0,    0, 0x1000,   31, 30, 29, 27, {}, 0,  19, 0xF80000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PlldpParamT210B01),    { 1428, 1432, 1436, 1440,    0,    0, }, {}, std::addressof(PlldpSdmT210B01), {}, },
    { "PLLC40",   ClkPllType_Pll,    1444, 1448, 0,    0, 0x2000,   31, 30, 29, 27, {}, 0,  19, 0xF80000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllc40ParamT210B01),   { 1448,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLM",     ClkPllType_Pll,    144,  156,  0,    0, 0x8,      31, 30, 29, 27, {}, 0,  20, 0x100000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PllmParamT210B01),     {  156, 1908, 1912, 1916,    0,    0, }, {}, std::addressof(PllmSdmT210B01),  {}, },
    { "PLLMB",    ClkPllType_Pll,    1512, 1516, 0,    0, 0x80000,  0,  30, 0,  27, {}, 0,  20, 0x100000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PllmbParamT210B01),    { 1516, 1920, 1924, 1928,    0,    0, }, {}, std::addressof(PllmbSdmT210B01), {}, },
    { "PLLP0",    ClkPllType_Pll,    160,  172,  0,    0, 0x10,     31, 30, 29, 27, {}, 28, 20, 0x1F00000,  10, 0x3FC00, 0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllp0ParamT210B01),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLREFE0", ClkPllType_Pll,    1220, 1224, 0,    0, 0x400,    31, 30, 29, 27, {}, 0,  16, 0x1F0000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllrefe0ParamT210B01), { 1224,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLU0",    ClkPllType_Pll,    192,  204,  0,    0, 0x200,    31, 30, 29, 27, {}, 24, 16, 0x1F0000,   8,  0xFF00,  0, 0xFF, 0, 0,  0, 0,  0x0,        0,  0,  std::addressof(Pllu0ParamT210B01),    {  204,  200,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLE0",    ClkPllType_Pll,    232,  236,  0,    0, 0x800,    0,  31, 0,  11, {}, 0,  24, 0x1F000000, 8,  0xFF00,  0, 0xFF, 0, 0,  9, 0,  0x0,        0,  0,  std::addressof(Plle0ParamT210B01),    {  236,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "UTMIPLL",  ClkPllType_Pll,    0,    0,    0,    0, 0x200000, 0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 0,  0x0,        0,  0,  std::addressof(UtmipllParamT210B01),  {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "GPU",      ClkPllType_Pll,    0,    0,    0,    0, 0x100000, 0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 0,  0x0,        0,  0,  std::addressof(PllGpuParamT210B01),   {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLC1",    ClkPllType_PllOut, 0,    0,    132,  0, 0x20001,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllc1ParamT210B01),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLC43",   ClkPllType_PllOut, 0,    0,    1508, 0, 0x20100,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllc43ParamT210B01),   {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLP3",    ClkPllType_PllOut, 0,    0,    168,  0, 0x20010,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllp3ParamT210B01),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLP4",    ClkPllType_PllOut, 0,    0,    168,  0, 0x20020,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 24, 0xFF000000, 17, 16, std::addressof(Pllp4ParamT210B01),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLP5",    ClkPllType_PllOut, 0,    0,    1660, 0, 0x20080,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 24, 0xFF000000, 17, 16, std::addressof(Pllp5ParamT210B01),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLA0",    ClkPllType_PllOut, 0,    0,    180,  0, 0x20040,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Plla0ParamT210B01),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLREFE1", ClkPllType_PllOut, 0,    0,    1228, 0, 0x20800,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllrefe1ParamT210B01), {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLU1",    ClkPllType_PllOut, 0,    0,    196,  0, 0x20200,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 8,  0xFF00,     1,  0,  std::addressof(Pllu1ParamT210B01),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
    { "PLLU2",    ClkPllType_PllOut, 0,    0,    196,  0, 0x20400,  0,  0,  0,  0,  {}, 0,  0,  0x0,        0,  0x0,     0, 0x0,  0, 0,  0, 24, 0xFF000000, 17, 16, std::addressof(Pllu2ParamT210B01),    {    0,    0,    0,    0,    0,    0, }, {}, nullptr,                         {}, },
};

constinit ClkSystemInfo ClkSystemInfoTableT210B01[] = {
    { "SCLK", ClkSystemInfoType_Sclk, 37, nullptr, 408000,  0, nullptr, nullptr, },
    { "CCLK", ClkSystemInfoType_Cclk, 36, nullptr, 2000000, 0, nullptr, nullptr, },
    { "HCLK", ClkSystemInfoType_Hclk, 38, nullptr, 408000,  0, nullptr, nullptr, },
    { "PCLK", ClkSystemInfoType_Pclk, 39, nullptr, 204000,  0, nullptr, nullptr, },
    { "EMC",  ClkSystemInfoType_Emc,  41, nullptr, 1600000, 0, nullptr, nullptr, },
    { "ACLK", ClkSystemInfoType_Aclk, 40, nullptr, 1190400, 0, nullptr, nullptr, },
};

constexpr ClkDeviceRegInfo ClkDeviceRegInfoTableT210[] = {
    { "I2S1",              0xFFFF, 0,    0x1D8,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  30,     24576,  { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "I2S2",              0xFFFF, 0,    0x100,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  11,     24576,  { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "I2S3",              0xFFFF, 0,    0x104,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  18,     24576,  { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "I2S4",              0xFFFF, 0,    0x3BC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  5,      24576,  { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "I2S5",              0xFFFF, 0,    0x3C0,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  6,      24576,  { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "SPDIF",             0xFFFF, 0,    0x108,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 24728,  { 4, 0, 0, 0, 21, 0, 3, 0 },    "SPDIF",     {}, },
    { "SPDIF_IN",          0xFFFF, 0,    0x10C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 408000, { 21, 0, 0, 0, 0, 3, 0, 0 },    nullptr,     {}, },
    { "AHUB",              0xFFFF, 0,    0x3D0,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  10,     98304,  { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "EXTPERIPH1",        0xFFFF, 0,    0x3EC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  24,     408000, { 4, 2, 21, 3, 0, 0, 0, 0 },    nullptr,     {}, },
    { "PWM",               0xFFFF, 0,    0x110,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  17,     48000,  { 21, 0, 0, 0, 2, 0, 3, 0 },    nullptr,     {}, },
    { "I2C1",              0xFFFF, 0,    0x124,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x300,  0x304,  0x320,  0x324,  12,     136000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C2",              0xFFFF, 0,    0x198,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x308,  0x30C,  0x328,  0x32C,  22,     136000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C3",              0xFFFF, 0,    0x1B8,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x310,  0x314,  0x330,  0x334,  3,      136000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C4",              0xFFFF, 0,    0x3C4,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x430,  0x434,  0x440,  0x444,  7,      136000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C5",              0xFFFF, 0,    0x128,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x308,  0x30C,  0x328,  0x32C,  15,     136000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C6",              0xFFFF, 0,    0x65C,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x290,  0x294,  0x284,  0x288,  6,      136000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SPI1",              0xFFFF, 0,    0x134,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x308,  0x30C,  0x328,  0x32C,  9,      65000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SPI2",              0xFFFF, 0,    0x118,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x308,  0x30C,  0x328,  0x32C,  12,     65000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SPI3",              0xFFFF, 0,    0x11C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x308,  0x30C,  0x328,  0x32C,  14,     65000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SPI4",              0xFFFF, 0,    0x1B4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x310,  0x314,  0x330,  0x334,  4,      65000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "QSPI",              0xFFFF, 0,    0x6C4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x2A8,  0x2AC,  0x29C,  0x2A0,  19,     163200, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "DISP1",             2,      0,    0x138,  0xE0000000, 29, 0x0,    0, {}, ClkDivType_None,       0x300,  0x304,  0x320,  0x324,  27,     665600, { 21, 0, 15, 0, 0, 16, 3, 0 },  nullptr,     {}, },
    { "DISP2",             3,      0,    0x13C,  0xE0000000, 29, 0x0,    0, {}, ClkDivType_None,       0x300,  0x304,  0x320,  0x324,  26,     665600, { 21, 0, 15, 0, 0, 16, 3, 0 },  nullptr,     {}, },
    { "SDMMC1",            0x1D,   0x40, 0x150,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  14,     204000, { 21, 0, 0, 13, 12, 0, 3, 11 }, nullptr,     {}, },
    { "SDMMC2",            0x1E,   0,    0x154,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x300,  0x304,  0x320,  0x324,  9,      204000, { 21, 13, 0, 0, 0, 12, 3, 0 },  nullptr,     { 0, 0, 0, 1, 1, 0, 0, 1, 0, 0 }, },
    { "SDMMC3",            0x1F,   0x40, 0x1BC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  5,      204000, { 21, 0, 0, 13, 12, 0, 3, 11 }, nullptr,     {}, },
    { "SDMMC4",            0x20,   0,    0x164,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x300,  0x304,  0x320,  0x324,  15,     204000, { 21, 13, 0, 0, 0, 12, 3, 0 },  nullptr,     { 0, 0, 0, 1, 1, 0, 0, 1, 0, 0 }, },
    { "SDMMC_LEGACY_TM",   0xFFFF, 0,    0x694,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x1000, 0x1000, 0x29C,  0x2A0,  1,      204000, { 23, 0, 0, 3, 21, 0, 0, 0 },   nullptr,     {}, },
    { "OWR",               0xFFFF, 0,    0x1CC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  7,      50000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "CSITE",             0xFFFF, 0,    0x1D4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  9,      204000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "TSEC",              0x16,   0,    0x1F4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  19,     408000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SE",                0xFFFF, 0,    0x42C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  31,     408000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "MSELECT",           0xFFFF, 0,    0x3B4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  3,      408000, { 21, 0, 0, 0, 0, 2, 3, 0 },    nullptr,     {}, },
    { "HDA2CODEC_2X",      0xFFFF, 0,    0x3E4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  15,     48000,  { 21, 0, 0, 0, 4, 0, 3, 0 },    nullptr,     {}, },
    { "ACTMON",            0xFFFF, 0,    0x3E8,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  23,     38400,  { 21, 0, 0, 0, 2, 0, 3, 0 },    nullptr,     {}, },
    { "I2C_SLOW",          0xFFFF, 0,    0x3FC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  17,     48000,  { 21, 0, 0, 0, 2, 0, 3, 0 },    nullptr,     {}, },
    { "SOR0",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x290,  0x294,  0x284,  0x288,  22,     540000, { 26, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "SOR1",              0xFFFF, 0x10, 0x410,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x290,  0x294,  0x284,  0x288,  23,     594000, { 21, 0, 15, 0, 0, 16, 3, 0 },  nullptr,     {}, },
    { "HDA",               7,      0,    0x428,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  29,     51000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "XUSB_CORE_HOST",    0x13,   0,    0x600,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 112000, { 3, 21, 0, 0, 0, 28, 0, 0 },   "XUSB_HOST", {}, },
    { "XUSB_FALCON",       0xFFFF, 0,    0x604,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 336000, { 3, 21, 0, 0, 0, 28, 0, 0 },   nullptr,     {}, },
    { "XUSB_FS",           0xFFFF, 0,    0x608,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 48000,  { 3, 0, 32, 0, 21, 0, 30, 0 },  nullptr,     {}, },
    { "XUSB_CORE_DEV",     0x14,   0,    0x60C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 112000, { 3, 21, 0, 0, 0, 28, 0, 0 },   "XUSB_DEV",  {}, },
    { "XUSB_SS_HOSTDEV",   0xFFFF, 0,    0x610,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 120000, { 3, 28, 2, 30, 0, 0, 0, 0 },   "XUSB_SS",   {}, },
    { "UARTA",             0xFFFF, 2,    0x178,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x300,  0x304,  0x320,  0x324,  6,      408000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "UARTB",             0xFFFF, 2,    0x17C,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x300,  0x304,  0x320,  0x324,  7,      408000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "UARTC",             0xFFFF, 2,    0x1A0,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x308,  0x30C,  0x328,  0x32C,  23,     408000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "UARTD",             0xFFFF, 2,    0x1C0,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x310,  0x314,  0x330,  0x334,  1,      408000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "HOST1X",            0xFFFF, 0,    0x180,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  28,     408000, { 0, 0, 0, 0, 21, 3, 0, 0 },    nullptr,     {}, },
    { "ENTROPY",           0xFFFF, 0,    0x628,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x438,  0x43C,  0x448,  0x44C,  21,     102000, { 21, 0, 3, 0, 2, 0, 0, 0 },    nullptr,     {}, },
    { "DSIA_LP",           0xFFFF, 0,    0x620,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x448,  0x44C,  19,     102000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "DVFS_REF",          0xFFFF, 0,    0x62C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 51000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "DVFS_SOC",          0xFFFF, 0,    0x630,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 51000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SOC_THERM",         0xFFFF, 0,    0x644,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  14,     136000, { 3, 0, 21, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "VIC",               0x12,   0,    0x678,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x290,  0x294,  0x284,  0x288,  18,     627200, { 0, 0, 21, 0, 9, 10, 3, 0 },   nullptr,     {}, },
    { "NVENC",             0xB,    0,    0x6A0,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  27,     716800, { 0, 9, 7, 10, 21, 0, 0, 3 },   nullptr,     {}, },
    { "NVJPG",             0x28,   0,    0x69C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  3,      627200, { 0, 9, 7, 10, 21, 0, 0, 3 },   nullptr,     {}, },
    { "NVDEC",             0x25,   0,    0x698,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  2,      716800, { 0, 9, 7, 10, 21, 0, 0, 3 },   nullptr,     {}, },
    { "TSECB",             0x2D,   0,    0x6D8,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  14,     627200, { 21, 9, 7, 10, 0, 0, 3, 0 },   nullptr,     {}, },
    { "APE",               0x26,   0,    0x6C0,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  6,      499200, { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "UARTAPE",           0xFFFF, 2,    0x710,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x1000, 0x1000, 0x29C,  0x2A0,  20,     204000, { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "DSI",               0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x308,  0x30C,  0x328,  0x32C,  16,     750000, { 15, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "DSIB",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x310,  0x314,  0x330,  0x334,  18,     750000, { 15, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "ADSP",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x2A8,  0x2AC,  0x29C,  0x2A0,  7,      844800, { 40, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "PCIE",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x310,  0x314,  0x330,  0x334,  6,      100000, { 18, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "MIPI_CAL",          0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x308,  0x30C,  0x328,  0x32C,  24,     102000, { 23, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "DPAUX",             0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x290,  0x294,  0x284,  0x288,  21,     24000,  { 26, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "DPAUX1",            0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x2A8,  0x2AC,  0x29C,  0x2A0,  15,     24000,  { 26, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "SOR_SAFE",          0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x2A8,  0x2AC,  0x29C,  0x2A0,  30,     24000,  { 26, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "USBD",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x300,  0x304,  0x320,  0x324,  22,     480000, { 35, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "USB2",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x308,  0x30C,  0x328,  0x32C,  26,     480000, { 35, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "APBDMA",            0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x308,  0x30C,  0x328,  0x32C,  2,      204000, { 39, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "CEC",               0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x438,  0x43C,  0x448,  0x44C,  8,      204000, { 39, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "USB2_TRK",          0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x2A8,  0x2AC,  0x29C,  0x2A0,  18,     9600,   { 45, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "MAUD",              0xFFFF, 0,    0x6D4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  10,     102000, { 21, 23, 3, 2, 4, 0, 0, 0 },   nullptr,     {}, },
    { "UART_FST_MIPI_CAL", 0xFFFF, 0,    0x66C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x290,  0x294,  0x284,  0x288,  17,     102000, { 23, 21, 0, 0, 0, 0, 3, 0 },   nullptr,     {}, },
};
static_assert(util::size(ClkDeviceRegInfoTableT210) == 76);

constexpr ClkDeviceRegInfo ClkDeviceRegInfoTableT210B01[] = {
    { "I2S1",              0xFFFF, 0,    0x1D8,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  30,     24576,   { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "I2S2",              0xFFFF, 0,    0x100,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  11,     24576,   { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "I2S3",              0xFFFF, 0,    0x104,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  18,     24576,   { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "I2S4",              0xFFFF, 0,    0x3BC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  5,      24576,   { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "I2S5",              0xFFFF, 0,    0x3C0,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  6,      24576,   { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "SPDIF",             0xFFFF, 0,    0x108,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 24576,   { 4, 0, 0, 0, 21, 0, 3, 0 },    "SPDIF",     {}, },
    { "SPDIF_IN",          0xFFFF, 0,    0x10C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 163200,  { 21, 0, 0, 0, 0, 3, 0, 0 },    nullptr,     {}, },
    { "AHUB",              0xFFFF, 0,    0x3D0,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  10,     98304,   { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "EXTPERIPH1",        0xFFFF, 0,    0x3EC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  24,     49152,   { 4, 2, 21, 3, 0, 0, 0, 0 },    nullptr,     {}, },
    { "EXTPERIPH2",        0xFFFF, 0,    0x3F0,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  25,     49152,   { 4, 2, 21, 3, 0, 0, 0, 0 },    nullptr,     {}, },
    { "PWM",               0xFFFF, 0,    0x110,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  17,     48000,   { 21, 0, 0, 0, 2, 0, 3, 0 },    nullptr,     {}, },
    { "I2C1",              0xFFFF, 0,    0x124,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x300,  0x304,  0x320,  0x324,  12,     136000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C2",              0xFFFF, 0,    0x198,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x308,  0x30C,  0x328,  0x32C,  22,     136000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C3",              0xFFFF, 0,    0x1B8,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x310,  0x314,  0x330,  0x334,  3,      136000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C4",              0xFFFF, 0,    0x3C4,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x430,  0x434,  0x440,  0x444,  7,      136000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C5",              0xFFFF, 0,    0x128,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x308,  0x30C,  0x328,  0x32C,  15,     136000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "I2C6",              0xFFFF, 0,    0x65C,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Integer16,  0x290,  0x294,  0x284,  0x288,  6,      136000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SPI1",              0xFFFF, 0,    0x134,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x308,  0x30C,  0x328,  0x32C,  9,      51000,   { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SPI2",              0xFFFF, 0,    0x118,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x308,  0x30C,  0x328,  0x32C,  12,     51000,   { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SPI3",              0xFFFF, 0,    0x11C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x308,  0x30C,  0x328,  0x32C,  14,     51000,   { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SPI4",              0xFFFF, 0,    0x1B4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x310,  0x314,  0x330,  0x334,  4,      51000,   { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "QSPI",              0xFFFF, 0,    0x6C4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x2A8,  0x2AC,  0x29C,  0x2A0,  19,     200000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "DISP1",             2,      0,    0x138,  0xE0000000, 29, 0x0,    0, {}, ClkDivType_None,       0x300,  0x304,  0x320,  0x324,  27,     665000,  { 21, 0, 15, 0, 0, 16, 3, 0 },  nullptr,     {}, },
    { "DISP2",             3,      0,    0x13C,  0xE0000000, 29, 0x0,    0, {}, ClkDivType_None,       0x300,  0x304,  0x320,  0x324,  26,     665000,  { 21, 0, 15, 0, 0, 16, 3, 0 },  nullptr,     {}, },
    { "SDMMC1",            0x1D,   0x40, 0x150,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  14,     204000,  { 21, 0, 0, 13, 12, 0, 3, 11 }, nullptr,     {}, },
    { "SDMMC2",            0x1E,   0,    0x154,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x300,  0x304,  0x320,  0x324,  9,      200000,  { 21, 13, 0, 0, 0, 12, 3, 0 },  nullptr,     { 0, 0, 0, 1, 1, 0, 0, 1, 0, 0 }, },
    { "SDMMC3",            0x1F,   0x40, 0x1BC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  5,      204000,  { 21, 0, 0, 13, 12, 0, 3, 11 }, nullptr,     {}, },
    { "SDMMC4",            0x20,   0,    0x164,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x300,  0x304,  0x320,  0x324,  15,     200000,  { 21, 13, 0, 0, 0, 12, 3, 0 },  nullptr,     { 0, 0, 0, 1, 1, 0, 0, 1, 0, 0 }, },
    { "SDMMC_LEGACY_TM",   0xFFFF, 0,    0x694,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x1000, 0x1000, 0x29C,  0x2A0,  1,      12000,   { 23, 0, 0, 3, 21, 0, 0, 0 },   nullptr,     {}, },
    { "OWR",               0xFFFF, 0,    0x1CC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  7,      50000,   { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "CSITE",             0xFFFF, 0,    0x1D4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  9,      204000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "TSEC",              0x16,   0,    0x1F4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x310,  0x314,  0x330,  0x334,  19,     408000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SE",                0xFFFF, 0,    0x42C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  31,     408000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "MSELECT",           0xFFFF, 0,    0x3B4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  3,      408000,  { 21, 0, 0, 0, 0, 2, 3, 0 },    nullptr,     {}, },
    { "HDA2CODEC_2X",      0xFFFF, 0,    0x3E4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  15,     48000,   { 21, 0, 0, 0, 4, 0, 3, 0 },    nullptr,     {}, },
    { "ACTMON",            0xFFFF, 0,    0x3E8,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  23,     38400,   { 21, 0, 0, 0, 2, 0, 3, 0 },    nullptr,     {}, },
    { "I2C_SLOW",          0xFFFF, 0,    0x3FC,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x310,  0x314,  0x330,  0x334,  17,     33,      { 21, 0, 0, 0, 2, 0, 3, 0 },    nullptr,     {}, },
    { "SOR1",              0xFFFF, 0x10, 0x410,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x290,  0x294,  0x284,  0x288,  23,     594000,  { 21, 0, 15, 0, 0, 16, 3, 0 },  nullptr,     {}, },
    { "HDA",               7,      0,    0x428,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x430,  0x434,  0x440,  0x444,  29,     102000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "XUSB_CORE_HOST",    0x13,   0,    0x600,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 112000,  { 3, 21, 0, 0, 0, 28, 0, 0 },   "XUSB_HOST", {}, },
    { "XUSB_FALCON",       0xFFFF, 0,    0x604,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 336000,  { 3, 21, 0, 0, 0, 28, 0, 0 },   nullptr,     {}, },
    { "XUSB_FS",           0xFFFF, 0,    0x608,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 48000,   { 3, 0, 32, 0, 21, 0, 30, 0 },  nullptr,     {}, },
    { "XUSB_CORE_DEV",     0x14,   0,    0x60C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 112000,  { 3, 21, 0, 0, 0, 28, 0, 0 },   "XUSB_DEV",  {}, },
    { "XUSB_SS_HOSTDEV",   0xFFFF, 0,    0x610,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 120000,  { 3, 28, 2, 30, 0, 0, 0, 0 },   "XUSB_SS",   {}, },
    { "UARTA",             0xFFFF, 2,    0x178,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x300,  0x304,  0x320,  0x324,  6,      408000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "UARTB",             0xFFFF, 2,    0x17C,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x300,  0x304,  0x320,  0x324,  7,      408000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "UARTC",             0xFFFF, 2,    0x1A0,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x308,  0x30C,  0x328,  0x32C,  23,     408000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "UARTD",             0xFFFF, 2,    0x1C0,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x310,  0x314,  0x330,  0x334,  1,      408000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "HOST1X",            0xFFFF, 0,    0x180,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x300,  0x304,  0x320,  0x324,  28,     408000,  { 0, 0, 0, 0, 21, 3, 0, 0 },    nullptr,     {}, },
    { "ENTROPY",           0xFFFF, 0,    0x628,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x438,  0x43C,  0x448,  0x44C,  21,     102000,  { 21, 0, 3, 0, 2, 0, 0, 0 },    nullptr,     {}, },
    { "DSIA_LP",           0xFFFF, 0,    0x620,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x448,  0x44C,  19,     102000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "DVFS_REF",          0xFFFF, 0,    0x62C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 51000,   { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "DVFS_SOC",          0xFFFF, 0,    0x630,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 51000,   { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "SOC_THERM",         0xFFFF, 0,    0x644,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Unk5,       0x310,  0x314,  0x330,  0x334,  14,     136000,  { 3, 0, 21, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "VIC",               0x12,   0,    0x678,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x290,  0x294,  0x284,  0x288,  18,     652800,  { 0, 0, 21, 0, 9, 10, 3, 0 },   nullptr,     {}, },
    { "NVENC",             0xB,    0,    0x6A0,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  27,     979200,  { 0, 9, 7, 10, 21, 0, 0, 3 },   nullptr,     {}, },
    { "NVJPG",             0x28,   0,    0x69C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  3,      652800,  { 0, 9, 7, 10, 21, 0, 0, 3 },   nullptr,     {}, },
    { "NVDEC",             0x25,   0,    0x698,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  2,      979200,  { 0, 9, 7, 10, 21, 0, 0, 3 },   nullptr,     {}, },
    { "TSECB",             0x2D,   0,    0x6D8,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  14,     652800,  { 21, 9, 7, 10, 0, 0, 3, 0 },   nullptr,     {}, },
    { "APE",               0x26,   0,    0x6C0,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  6,      998400,  { 4, 0, 0, 0, 21, 0, 3, 0 },    nullptr,     {}, },
    { "UARTAPE",           0xFFFF, 2,    0x710,  0xE0000000, 29, 0xFFFF, 0, {}, ClkDivType_Uart,       0x1000, 0x1000, 0x29C,  0x2A0,  20,     204000,  { 21, 0, 0, 0, 0, 0, 3, 0 },    nullptr,     {}, },
    { "DSI",               0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x308,  0x30C,  0x328,  0x32C,  16,     750000,  { 15, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "DSIB",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x310,  0x314,  0x330,  0x334,  18,     750000,  { 15, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "ADSP",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x2A8,  0x2AC,  0x29C,  0x2A0,  7,      1190400, { 40, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "PCIE",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x310,  0x314,  0x330,  0x334,  6,      100000,  { 18, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "MIPI_CAL",          0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x308,  0x30C,  0x328,  0x32C,  24,     102000,  { 23, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "DPAUX",             0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x290,  0x294,  0x284,  0x288,  21,     24000,   { 26, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "DPAUX1",            0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x2A8,  0x2AC,  0x29C,  0x2A0,  15,     24000,   { 26, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "SOR_SAFE",          0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x2A8,  0x2AC,  0x29C,  0x2A0,  30,     24000,   { 26, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "USBD",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x300,  0x304,  0x320,  0x324,  22,     480000,  { 35, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "USB2",              0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x308,  0x30C,  0x328,  0x32C,  26,     480000,  { 35, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "APBDMA",            0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x308,  0x30C,  0x328,  0x32C,  2,      204000,  { 39, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "CEC",               0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x438,  0x43C,  0x448,  0x44C,  8,      204000,  { 39, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "USB2_TRK",          0xFFFF, 0,    0x1000, 0x0,        0,  0x0,    0, {}, ClkDivType_None,       0x2A8,  0x2AC,  0x29C,  0x2A0,  18,     9600,    { 45, 0, 0, 0, 0, 0, 0, 0 },    nullptr,     {}, },
    { "MAUD",              0xFFFF, 0,    0x6D4,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x2A8,  0x2AC,  0x29C,  0x2A0,  10,     102000,  { 21, 23, 3, 2, 4, 0, 0, 0 },   nullptr,     {}, },
    { "UART_FST_MIPI_CAL", 0xFFFF, 0,    0x66C,  0xE0000000, 29, 0xFF,   0, {}, ClkDivType_Fractional, 0x290,  0x294,  0x284,  0x288,  17,     68000,   { 23, 21, 0, 0, 0, 0, 3, 0 },   nullptr,     {}, },
};
static_assert(util::size(ClkDeviceRegInfoTableT210B01) == 76);
