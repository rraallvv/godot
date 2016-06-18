/*************************************************************************/
/*  ucaps.h                                                              */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2016 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#ifndef UCAPS_H
#define UCAPS_H

//satan invented unicode?
#define CAPS_LEN 666

static const int caps_table[CAPS_LEN][2]={
{0x0061,0x0041},
{0x0062,0x0042},
{0x0063,0x0043},
{0x0064,0x0044},
{0x0065,0x0045},
{0x0066,0x0046},
{0x0067,0x0047},
{0x0068,0x0048},
{0x0069,0x0049},
{0x006A,0x004A},
{0x006B,0x004B},
{0x006C,0x004C},
{0x006D,0x004D},
{0x006E,0x004E},
{0x006F,0x004F},
{0x0070,0x0050},
{0x0071,0x0051},
{0x0072,0x0052},
{0x0073,0x0053},
{0x0074,0x0054},
{0x0075,0x0055},
{0x0076,0x0056},
{0x0077,0x0057},
{0x0078,0x0058},
{0x0079,0x0059},
{0x007A,0x005A},
{0x00E0,0x00C0},
{0x00E1,0x00C1},
{0x00E2,0x00C2},
{0x00E3,0x00C3},
{0x00E4,0x00C4},
{0x00E5,0x00C5},
{0x00E6,0x00C6},
{0x00E7,0x00C7},
{0x00E8,0x00C8},
{0x00E9,0x00C9},
{0x00EA,0x00CA},
{0x00EB,0x00CB},
{0x00EC,0x00CC},
{0x00ED,0x00CD},
{0x00EE,0x00CE},
{0x00EF,0x00CF},
{0x00F0,0x00D0},
{0x00F1,0x00D1},
{0x00F2,0x00D2},
{0x00F3,0x00D3},
{0x00F4,0x00D4},
{0x00F5,0x00D5},
{0x00F6,0x00D6},
{0x00F8,0x00D8},
{0x00F9,0x00D9},
{0x00FA,0x00DA},
{0x00FB,0x00DB},
{0x00FC,0x00DC},
{0x00FD,0x00DD},
{0x00FE,0x00DE},
{0x00FF,0x0178},
{0x0101,0x0100},
{0x0103,0x0102},
{0x0105,0x0104},
{0x0107,0x0106},
{0x0109,0x0108},
{0x010B,0x010A},
{0x010D,0x010C},
{0x010F,0x010E},
{0x0111,0x0110},
{0x0113,0x0112},
{0x0115,0x0114},
{0x0117,0x0116},
{0x0119,0x0118},
{0x011B,0x011A},
{0x011D,0x011C},
{0x011F,0x011E},
{0x0121,0x0120},
{0x0123,0x0122},
{0x0125,0x0124},
{0x0127,0x0126},
{0x0129,0x0128},
{0x012B,0x012A},
{0x012D,0x012C},
{0x012F,0x012E},
{0x0131,0x0049},
{0x0133,0x0132},
{0x0135,0x0134},
{0x0137,0x0136},
{0x013A,0x0139},
{0x013C,0x013B},
{0x013E,0x013D},
{0x0140,0x013F},
{0x0142,0x0141},
{0x0144,0x0143},
{0x0146,0x0145},
{0x0148,0x0147},
{0x014B,0x014A},
{0x014D,0x014C},
{0x014F,0x014E},
{0x0151,0x0150},
{0x0153,0x0152},
{0x0155,0x0154},
{0x0157,0x0156},
{0x0159,0x0158},
{0x015B,0x015A},
{0x015D,0x015C},
{0x015F,0x015E},
{0x0161,0x0160},
{0x0163,0x0162},
{0x0165,0x0164},
{0x0167,0x0166},
{0x0169,0x0168},
{0x016B,0x016A},
{0x016D,0x016C},
{0x016F,0x016E},
{0x0171,0x0170},
{0x0173,0x0172},
{0x0175,0x0174},
{0x0177,0x0176},
{0x017A,0x0179},
{0x017C,0x017B},
{0x017E,0x017D},
{0x0183,0x0182},
{0x0185,0x0184},
{0x0188,0x0187},
{0x018C,0x018B},
{0x0192,0x0191},
{0x0199,0x0198},
{0x01A1,0x01A0},
{0x01A3,0x01A2},
{0x01A5,0x01A4},
{0x01A8,0x01A7},
{0x01AD,0x01AC},
{0x01B0,0x01AF},
{0x01B4,0x01B3},
{0x01B6,0x01B5},
{0x01B9,0x01B8},
{0x01BD,0x01BC},
{0x01C6,0x01C4},
{0x01C9,0x01C7},
{0x01CC,0x01CA},
{0x01CE,0x01CD},
{0x01D0,0x01CF},
{0x01D2,0x01D1},
{0x01D4,0x01D3},
{0x01D6,0x01D5},
{0x01D8,0x01D7},
{0x01DA,0x01D9},
{0x01DC,0x01DB},
{0x01DF,0x01DE},
{0x01E1,0x01E0},
{0x01E3,0x01E2},
{0x01E5,0x01E4},
{0x01E7,0x01E6},
{0x01E9,0x01E8},
{0x01EB,0x01EA},
{0x01ED,0x01EC},
{0x01EF,0x01EE},
{0x01F3,0x01F1},
{0x01F5,0x01F4},
{0x01FB,0x01FA},
{0x01FD,0x01FC},
{0x01FF,0x01FE},
{0x0201,0x0200},
{0x0203,0x0202},
{0x0205,0x0204},
{0x0207,0x0206},
{0x0209,0x0208},
{0x020B,0x020A},
{0x020D,0x020C},
{0x020F,0x020E},
{0x0211,0x0210},
{0x0213,0x0212},
{0x0215,0x0214},
{0x0217,0x0216},
{0x0253,0x0181},
{0x0254,0x0186},
{0x0257,0x018A},
{0x0258,0x018E},
{0x0259,0x018F},
{0x025B,0x0190},
{0x0260,0x0193},
{0x0263,0x0194},
{0x0268,0x0197},
{0x0269,0x0196},
{0x026F,0x019C},
{0x0272,0x019D},
{0x0275,0x019F},
{0x0283,0x01A9},
{0x0288,0x01AE},
{0x028A,0x01B1},
{0x028B,0x01B2},
{0x0292,0x01B7},
{0x03AC,0x0386},
{0x03AD,0x0388},
{0x03AE,0x0389},
{0x03AF,0x038A},
{0x03B1,0x0391},
{0x03B2,0x0392},
{0x03B3,0x0393},
{0x03B4,0x0394},
{0x03B5,0x0395},
{0x03B6,0x0396},
{0x03B7,0x0397},
{0x03B8,0x0398},
{0x03B9,0x0399},
{0x03BA,0x039A},
{0x03BB,0x039B},
{0x03BC,0x039C},
{0x03BD,0x039D},
{0x03BE,0x039E},
{0x03BF,0x039F},
{0x03C0,0x03A0},
{0x03C1,0x03A1},
{0x03C3,0x03A3},
{0x03C4,0x03A4},
{0x03C5,0x03A5},
{0x03C6,0x03A6},
{0x03C7,0x03A7},
{0x03C8,0x03A8},
{0x03C9,0x03A9},
{0x03CA,0x03AA},
{0x03CB,0x03AB},
{0x03CC,0x038C},
{0x03CD,0x038E},
{0x03CE,0x038F},
{0x03E3,0x03E2},
{0x03E5,0x03E4},
{0x03E7,0x03E6},
{0x03E9,0x03E8},
{0x03EB,0x03EA},
{0x03ED,0x03EC},
{0x03EF,0x03EE},
{0x0430,0x0410},
{0x0431,0x0411},
{0x0432,0x0412},
{0x0433,0x0413},
{0x0434,0x0414},
{0x0435,0x0415},
{0x0436,0x0416},
{0x0437,0x0417},
{0x0438,0x0418},
{0x0439,0x0419},
{0x043A,0x041A},
{0x043B,0x041B},
{0x043C,0x041C},
{0x043D,0x041D},
{0x043E,0x041E},
{0x043F,0x041F},
{0x0440,0x0420},
{0x0441,0x0421},
{0x0442,0x0422},
{0x0443,0x0423},
{0x0444,0x0424},
{0x0445,0x0425},
{0x0446,0x0426},
{0x0447,0x0427},
{0x0448,0x0428},
{0x0449,0x0429},
{0x044A,0x042A},
{0x044B,0x042B},
{0x044C,0x042C},
{0x044D,0x042D},
{0x044E,0x042E},
{0x044F,0x042F},
{0x0451,0x0401},
{0x0452,0x0402},
{0x0453,0x0403},
{0x0454,0x0404},
{0x0455,0x0405},
{0x0456,0x0406},
{0x0457,0x0407},
{0x0458,0x0408},
{0x0459,0x0409},
{0x045A,0x040A},
{0x045B,0x040B},
{0x045C,0x040C},
{0x045E,0x040E},
{0x045F,0x040F},
{0x0461,0x0460},
{0x0463,0x0462},
{0x0465,0x0464},
{0x0467,0x0466},
{0x0469,0x0468},
{0x046B,0x046A},
{0x046D,0x046C},
{0x046F,0x046E},
{0x0471,0x0470},
{0x0473,0x0472},
{0x0475,0x0474},
{0x0477,0x0476},
{0x0479,0x0478},
{0x047B,0x047A},
{0x047D,0x047C},
{0x047F,0x047E},
{0x0481,0x0480},
{0x0491,0x0490},
{0x0493,0x0492},
{0x0495,0x0494},
{0x0497,0x0496},
{0x0499,0x0498},
{0x049B,0x049A},
{0x049D,0x049C},
{0x049F,0x049E},
{0x04A1,0x04A0},
{0x04A3,0x04A2},
{0x04A5,0x04A4},
{0x04A7,0x04A6},
{0x04A9,0x04A8},
{0x04AB,0x04AA},
{0x04AD,0x04AC},
{0x04AF,0x04AE},
{0x04B1,0x04B0},
{0x04B3,0x04B2},
{0x04B5,0x04B4},
{0x04B7,0x04B6},
{0x04B9,0x04B8},
{0x04BB,0x04BA},
{0x04BD,0x04BC},
{0x04BF,0x04BE},
{0x04C2,0x04C1},
{0x04C4,0x04C3},
{0x04C8,0x04C7},
{0x04CC,0x04CB},
{0x04D1,0x04D0},
{0x04D3,0x04D2},
{0x04D5,0x04D4},
{0x04D7,0x04D6},
{0x04D9,0x04D8},
{0x04DB,0x04DA},
{0x04DD,0x04DC},
{0x04DF,0x04DE},
{0x04E1,0x04E0},
{0x04E3,0x04E2},
{0x04E5,0x04E4},
{0x04E7,0x04E6},
{0x04E9,0x04E8},
{0x04EB,0x04EA},
{0x04EF,0x04EE},
{0x04F1,0x04F0},
{0x04F3,0x04F2},
{0x04F5,0x04F4},
{0x04F9,0x04F8},
{0x0561,0x0531},
{0x0562,0x0532},
{0x0563,0x0533},
{0x0564,0x0534},
{0x0565,0x0535},
{0x0566,0x0536},
{0x0567,0x0537},
{0x0568,0x0538},
{0x0569,0x0539},
{0x056A,0x053A},
{0x056B,0x053B},
{0x056C,0x053C},
{0x056D,0x053D},
{0x056E,0x053E},
{0x056F,0x053F},
{0x0570,0x0540},
{0x0571,0x0541},
{0x0572,0x0542},
{0x0573,0x0543},
{0x0574,0x0544},
{0x0575,0x0545},
{0x0576,0x0546},
{0x0577,0x0547},
{0x0578,0x0548},
{0x0579,0x0549},
{0x057A,0x054A},
{0x057B,0x054B},
{0x057C,0x054C},
{0x057D,0x054D},
{0x057E,0x054E},
{0x057F,0x054F},
{0x0580,0x0550},
{0x0581,0x0551},
{0x0582,0x0552},
{0x0583,0x0553},
{0x0584,0x0554},
{0x0585,0x0555},
{0x0586,0x0556},
{0x10D0,0x10A0},
{0x10D1,0x10A1},
{0x10D2,0x10A2},
{0x10D3,0x10A3},
{0x10D4,0x10A4},
{0x10D5,0x10A5},
{0x10D6,0x10A6},
{0x10D7,0x10A7},
{0x10D8,0x10A8},
{0x10D9,0x10A9},
{0x10DA,0x10AA},
{0x10DB,0x10AB},
{0x10DC,0x10AC},
{0x10DD,0x10AD},
{0x10DE,0x10AE},
{0x10DF,0x10AF},
{0x10E0,0x10B0},
{0x10E1,0x10B1},
{0x10E2,0x10B2},
{0x10E3,0x10B3},
{0x10E4,0x10B4},
{0x10E5,0x10B5},
{0x10E6,0x10B6},
{0x10E7,0x10B7},
{0x10E8,0x10B8},
{0x10E9,0x10B9},
{0x10EA,0x10BA},
{0x10EB,0x10BB},
{0x10EC,0x10BC},
{0x10ED,0x10BD},
{0x10EE,0x10BE},
{0x10EF,0x10BF},
{0x10F0,0x10C0},
{0x10F1,0x10C1},
{0x10F2,0x10C2},
{0x10F3,0x10C3},
{0x10F4,0x10C4},
{0x10F5,0x10C5},
{0x1E01,0x1E00},
{0x1E03,0x1E02},
{0x1E05,0x1E04},
{0x1E07,0x1E06},
{0x1E09,0x1E08},
{0x1E0B,0x1E0A},
{0x1E0D,0x1E0C},
{0x1E0F,0x1E0E},
{0x1E11,0x1E10},
{0x1E13,0x1E12},
{0x1E15,0x1E14},
{0x1E17,0x1E16},
{0x1E19,0x1E18},
{0x1E1B,0x1E1A},
{0x1E1D,0x1E1C},
{0x1E1F,0x1E1E},
{0x1E21,0x1E20},
{0x1E23,0x1E22},
{0x1E25,0x1E24},
{0x1E27,0x1E26},
{0x1E29,0x1E28},
{0x1E2B,0x1E2A},
{0x1E2D,0x1E2C},
{0x1E2F,0x1E2E},
{0x1E31,0x1E30},
{0x1E33,0x1E32},
{0x1E35,0x1E34},
{0x1E37,0x1E36},
{0x1E39,0x1E38},
{0x1E3B,0x1E3A},
{0x1E3D,0x1E3C},
{0x1E3F,0x1E3E},
{0x1E41,0x1E40},
{0x1E43,0x1E42},
{0x1E45,0x1E44},
{0x1E47,0x1E46},
{0x1E49,0x1E48},
{0x1E4B,0x1E4A},
{0x1E4D,0x1E4C},
{0x1E4F,0x1E4E},
{0x1E51,0x1E50},
{0x1E53,0x1E52},
{0x1E55,0x1E54},
{0x1E57,0x1E56},
{0x1E59,0x1E58},
{0x1E5B,0x1E5A},
{0x1E5D,0x1E5C},
{0x1E5F,0x1E5E},
{0x1E61,0x1E60},
{0x1E63,0x1E62},
{0x1E65,0x1E64},
{0x1E67,0x1E66},
{0x1E69,0x1E68},
{0x1E6B,0x1E6A},
{0x1E6D,0x1E6C},
{0x1E6F,0x1E6E},
{0x1E71,0x1E70},
{0x1E73,0x1E72},
{0x1E75,0x1E74},
{0x1E77,0x1E76},
{0x1E79,0x1E78},
{0x1E7B,0x1E7A},
{0x1E7D,0x1E7C},
{0x1E7F,0x1E7E},
{0x1E81,0x1E80},
{0x1E83,0x1E82},
{0x1E85,0x1E84},
{0x1E87,0x1E86},
{0x1E89,0x1E88},
{0x1E8B,0x1E8A},
{0x1E8D,0x1E8C},
{0x1E8F,0x1E8E},
{0x1E91,0x1E90},
{0x1E93,0x1E92},
{0x1E95,0x1E94},
{0x1EA1,0x1EA0},
{0x1EA3,0x1EA2},
{0x1EA5,0x1EA4},
{0x1EA7,0x1EA6},
{0x1EA9,0x1EA8},
{0x1EAB,0x1EAA},
{0x1EAD,0x1EAC},
{0x1EAF,0x1EAE},
{0x1EB1,0x1EB0},
{0x1EB3,0x1EB2},
{0x1EB5,0x1EB4},
{0x1EB7,0x1EB6},
{0x1EB9,0x1EB8},
{0x1EBB,0x1EBA},
{0x1EBD,0x1EBC},
{0x1EBF,0x1EBE},
{0x1EC1,0x1EC0},
{0x1EC3,0x1EC2},
{0x1EC5,0x1EC4},
{0x1EC7,0x1EC6},
{0x1EC9,0x1EC8},
{0x1ECB,0x1ECA},
{0x1ECD,0x1ECC},
{0x1ECF,0x1ECE},
{0x1ED1,0x1ED0},
{0x1ED3,0x1ED2},
{0x1ED5,0x1ED4},
{0x1ED7,0x1ED6},
{0x1ED9,0x1ED8},
{0x1EDB,0x1EDA},
{0x1EDD,0x1EDC},
{0x1EDF,0x1EDE},
{0x1EE1,0x1EE0},
{0x1EE3,0x1EE2},
{0x1EE5,0x1EE4},
{0x1EE7,0x1EE6},
{0x1EE9,0x1EE8},
{0x1EEB,0x1EEA},
{0x1EED,0x1EEC},
{0x1EEF,0x1EEE},
{0x1EF1,0x1EF0},
{0x1EF3,0x1EF2},
{0x1EF5,0x1EF4},
{0x1EF7,0x1EF6},
{0x1EF9,0x1EF8},
{0x1F00,0x1F08},
{0x1F01,0x1F09},
{0x1F02,0x1F0A},
{0x1F03,0x1F0B},
{0x1F04,0x1F0C},
{0x1F05,0x1F0D},
{0x1F06,0x1F0E},
{0x1F07,0x1F0F},
{0x1F10,0x1F18},
{0x1F11,0x1F19},
{0x1F12,0x1F1A},
{0x1F13,0x1F1B},
{0x1F14,0x1F1C},
{0x1F15,0x1F1D},
{0x1F20,0x1F28},
{0x1F21,0x1F29},
{0x1F22,0x1F2A},
{0x1F23,0x1F2B},
{0x1F24,0x1F2C},
{0x1F25,0x1F2D},
{0x1F26,0x1F2E},
{0x1F27,0x1F2F},
{0x1F30,0x1F38},
{0x1F31,0x1F39},
{0x1F32,0x1F3A},
{0x1F33,0x1F3B},
{0x1F34,0x1F3C},
{0x1F35,0x1F3D},
{0x1F36,0x1F3E},
{0x1F37,0x1F3F},
{0x1F40,0x1F48},
{0x1F41,0x1F49},
{0x1F42,0x1F4A},
{0x1F43,0x1F4B},
{0x1F44,0x1F4C},
{0x1F45,0x1F4D},
{0x1F51,0x1F59},
{0x1F53,0x1F5B},
{0x1F55,0x1F5D},
{0x1F57,0x1F5F},
{0x1F60,0x1F68},
{0x1F61,0x1F69},
{0x1F62,0x1F6A},
{0x1F63,0x1F6B},
{0x1F64,0x1F6C},
{0x1F65,0x1F6D},
{0x1F66,0x1F6E},
{0x1F67,0x1F6F},
{0x1F80,0x1F88},
{0x1F81,0x1F89},
{0x1F82,0x1F8A},
{0x1F83,0x1F8B},
{0x1F84,0x1F8C},
{0x1F85,0x1F8D},
{0x1F86,0x1F8E},
{0x1F87,0x1F8F},
{0x1F90,0x1F98},
{0x1F91,0x1F99},
{0x1F92,0x1F9A},
{0x1F93,0x1F9B},
{0x1F94,0x1F9C},
{0x1F95,0x1F9D},
{0x1F96,0x1F9E},
{0x1F97,0x1F9F},
{0x1FA0,0x1FA8},
{0x1FA1,0x1FA9},
{0x1FA2,0x1FAA},
{0x1FA3,0x1FAB},
{0x1FA4,0x1FAC},
{0x1FA5,0x1FAD},
{0x1FA6,0x1FAE},
{0x1FA7,0x1FAF},
{0x1FB0,0x1FB8},
{0x1FB1,0x1FB9},
{0x1FD0,0x1FD8},
{0x1FD1,0x1FD9},
{0x1FE0,0x1FE8},
{0x1FE1,0x1FE9},
{0x24D0,0x24B6},
{0x24D1,0x24B7},
{0x24D2,0x24B8},
{0x24D3,0x24B9},
{0x24D4,0x24BA},
{0x24D5,0x24BB},
{0x24D6,0x24BC},
{0x24D7,0x24BD},
{0x24D8,0x24BE},
{0x24D9,0x24BF},
{0x24DA,0x24C0},
{0x24DB,0x24C1},
{0x24DC,0x24C2},
{0x24DD,0x24C3},
{0x24DE,0x24C4},
{0x24DF,0x24C5},
{0x24E0,0x24C6},
{0x24E1,0x24C7},
{0x24E2,0x24C8},
{0x24E3,0x24C9},
{0x24E4,0x24CA},
{0x24E5,0x24CB},
{0x24E6,0x24CC},
{0x24E7,0x24CD},
{0x24E8,0x24CE},
{0x24E9,0x24CF},
{0xFF41,0xFF21},
{0xFF42,0xFF22},
{0xFF43,0xFF23},
{0xFF44,0xFF24},
{0xFF45,0xFF25},
{0xFF46,0xFF26},
{0xFF47,0xFF27},
{0xFF48,0xFF28},
{0xFF49,0xFF29},
{0xFF4A,0xFF2A},
{0xFF4B,0xFF2B},
{0xFF4C,0xFF2C},
{0xFF4D,0xFF2D},
{0xFF4E,0xFF2E},
{0xFF4F,0xFF2F},
{0xFF50,0xFF30},
{0xFF51,0xFF31},
{0xFF52,0xFF32},
{0xFF53,0xFF33},
{0xFF54,0xFF34},
{0xFF55,0xFF35},
{0xFF56,0xFF36},
{0xFF57,0xFF37},
{0xFF58,0xFF38},
{0xFF59,0xFF39},
{0xFF5A,0xFF3A},
};

static const int reverse_caps_table[CAPS_LEN-1][2]={
{0x41,0x61},
{0x42,0x62},
{0x43,0x63},
{0x44,0x64},
{0x45,0x65},
{0x46,0x66},
{0x47,0x67},
{0x48,0x68},
{0x49,0x69},
{0x4a,0x6a},
{0x4b,0x6b},
{0x4c,0x6c},
{0x4d,0x6d},
{0x4e,0x6e},
{0x4f,0x6f},
{0x50,0x70},
{0x51,0x71},
{0x52,0x72},
{0x53,0x73},
{0x54,0x74},
{0x55,0x75},
{0x56,0x76},
{0x57,0x77},
{0x58,0x78},
{0x59,0x79},
{0x5a,0x7a},
{0xc0,0xe0},
{0xc1,0xe1},
{0xc2,0xe2},
{0xc3,0xe3},
{0xc4,0xe4},
{0xc5,0xe5},
{0xc6,0xe6},
{0xc7,0xe7},
{0xc8,0xe8},
{0xc9,0xe9},
{0xca,0xea},
{0xcb,0xeb},
{0xcc,0xec},
{0xcd,0xed},
{0xce,0xee},
{0xcf,0xef},
{0xd0,0xf0},
{0xd1,0xf1},
{0xd2,0xf2},
{0xd3,0xf3},
{0xd4,0xf4},
{0xd5,0xf5},
{0xd6,0xf6},
{0xd8,0xf8},
{0xd9,0xf9},
{0xda,0xfa},
{0xdb,0xfb},
{0xdc,0xfc},
{0xdd,0xfd},
{0xde,0xfe},
{0x178,0xff},
{0x100,0x101},
{0x102,0x103},
{0x104,0x105},
{0x106,0x107},
{0x108,0x109},
{0x10a,0x10b},
{0x10c,0x10d},
{0x10e,0x10f},
{0x110,0x111},
{0x112,0x113},
{0x114,0x115},
{0x116,0x117},
{0x118,0x119},
{0x11a,0x11b},
{0x11c,0x11d},
{0x11e,0x11f},
{0x120,0x121},
{0x122,0x123},
{0x124,0x125},
{0x126,0x127},
{0x128,0x129},
{0x12a,0x12b},
{0x12c,0x12d},
{0x12e,0x12f},
//{0x49,0x131},
{0x132,0x133},
{0x134,0x135},
{0x136,0x137},
{0x139,0x13a},
{0x13b,0x13c},
{0x13d,0x13e},
{0x13f,0x140},
{0x141,0x142},
{0x143,0x144},
{0x145,0x146},
{0x147,0x148},
{0x14a,0x14b},
{0x14c,0x14d},
{0x14e,0x14f},
{0x150,0x151},
{0x152,0x153},
{0x154,0x155},
{0x156,0x157},
{0x158,0x159},
{0x15a,0x15b},
{0x15c,0x15d},
{0x15e,0x15f},
{0x160,0x161},
{0x162,0x163},
{0x164,0x165},
{0x166,0x167},
{0x168,0x169},
{0x16a,0x16b},
{0x16c,0x16d},
{0x16e,0x16f},
{0x170,0x171},
{0x172,0x173},
{0x174,0x175},
{0x176,0x177},
{0x179,0x17a},
{0x17b,0x17c},
{0x17d,0x17e},
{0x182,0x183},
{0x184,0x185},
{0x187,0x188},
{0x18b,0x18c},
{0x191,0x192},
{0x198,0x199},
{0x1a0,0x1a1},
{0x1a2,0x1a3},
{0x1a4,0x1a5},
{0x1a7,0x1a8},
{0x1ac,0x1ad},
{0x1af,0x1b0},
{0x1b3,0x1b4},
{0x1b5,0x1b6},
{0x1b8,0x1b9},
{0x1bc,0x1bd},
{0x1c4,0x1c6},
{0x1c7,0x1c9},
{0x1ca,0x1cc},
{0x1cd,0x1ce},
{0x1cf,0x1d0},
{0x1d1,0x1d2},
{0x1d3,0x1d4},
{0x1d5,0x1d6},
{0x1d7,0x1d8},
{0x1d9,0x1da},
{0x1db,0x1dc},
{0x1de,0x1df},
{0x1e0,0x1e1},
{0x1e2,0x1e3},
{0x1e4,0x1e5},
{0x1e6,0x1e7},
{0x1e8,0x1e9},
{0x1ea,0x1eb},
{0x1ec,0x1ed},
{0x1ee,0x1ef},
{0x1f1,0x1f3},
{0x1f4,0x1f5},
{0x1fa,0x1fb},
{0x1fc,0x1fd},
{0x1fe,0x1ff},
{0x200,0x201},
{0x202,0x203},
{0x204,0x205},
{0x206,0x207},
{0x208,0x209},
{0x20a,0x20b},
{0x20c,0x20d},
{0x20e,0x20f},
{0x210,0x211},
{0x212,0x213},
{0x214,0x215},
{0x216,0x217},
{0x181,0x253},
{0x186,0x254},
{0x18a,0x257},
{0x18e,0x258},
{0x18f,0x259},
{0x190,0x25b},
{0x193,0x260},
{0x194,0x263},
{0x197,0x268},
{0x196,0x269},
{0x19c,0x26f},
{0x19d,0x272},
{0x19f,0x275},
{0x1a9,0x283},
{0x1ae,0x288},
{0x1b1,0x28a},
{0x1b2,0x28b},
{0x1b7,0x292},
{0x386,0x3ac},
{0x388,0x3ad},
{0x389,0x3ae},
{0x38a,0x3af},
{0x391,0x3b1},
{0x392,0x3b2},
{0x393,0x3b3},
{0x394,0x3b4},
{0x395,0x3b5},
{0x396,0x3b6},
{0x397,0x3b7},
{0x398,0x3b8},
{0x399,0x3b9},
{0x39a,0x3ba},
{0x39b,0x3bb},
{0x39c,0x3bc},
{0x39d,0x3bd},
{0x39e,0x3be},
{0x39f,0x3bf},
{0x3a0,0x3c0},
{0x3a1,0x3c1},
{0x3a3,0x3c3},
{0x3a4,0x3c4},
{0x3a5,0x3c5},
{0x3a6,0x3c6},
{0x3a7,0x3c7},
{0x3a8,0x3c8},
{0x3a9,0x3c9},
{0x3aa,0x3ca},
{0x3ab,0x3cb},
{0x38c,0x3cc},
{0x38e,0x3cd},
{0x38f,0x3ce},
{0x3e2,0x3e3},
{0x3e4,0x3e5},
{0x3e6,0x3e7},
{0x3e8,0x3e9},
{0x3ea,0x3eb},
{0x3ec,0x3ed},
{0x3ee,0x3ef},
{0x410,0x430},
{0x411,0x431},
{0x412,0x432},
{0x413,0x433},
{0x414,0x434},
{0x415,0x435},
{0x416,0x436},
{0x417,0x437},
{0x418,0x438},
{0x419,0x439},
{0x41a,0x43a},
{0x41b,0x43b},
{0x41c,0x43c},
{0x41d,0x43d},
{0x41e,0x43e},
{0x41f,0x43f},
{0x420,0x440},
{0x421,0x441},
{0x422,0x442},
{0x423,0x443},
{0x424,0x444},
{0x425,0x445},
{0x426,0x446},
{0x427,0x447},
{0x428,0x448},
{0x429,0x449},
{0x42a,0x44a},
{0x42b,0x44b},
{0x42c,0x44c},
{0x42d,0x44d},
{0x42e,0x44e},
{0x42f,0x44f},
{0x401,0x451},
{0x402,0x452},
{0x403,0x453},
{0x404,0x454},
{0x405,0x455},
{0x406,0x456},
{0x407,0x457},
{0x408,0x458},
{0x409,0x459},
{0x40a,0x45a},
{0x40b,0x45b},
{0x40c,0x45c},
{0x40e,0x45e},
{0x40f,0x45f},
{0x460,0x461},
{0x462,0x463},
{0x464,0x465},
{0x466,0x467},
{0x468,0x469},
{0x46a,0x46b},
{0x46c,0x46d},
{0x46e,0x46f},
{0x470,0x471},
{0x472,0x473},
{0x474,0x475},
{0x476,0x477},
{0x478,0x479},
{0x47a,0x47b},
{0x47c,0x47d},
{0x47e,0x47f},
{0x480,0x481},
{0x490,0x491},
{0x492,0x493},
{0x494,0x495},
{0x496,0x497},
{0x498,0x499},
{0x49a,0x49b},
{0x49c,0x49d},
{0x49e,0x49f},
{0x4a0,0x4a1},
{0x4a2,0x4a3},
{0x4a4,0x4a5},
{0x4a6,0x4a7},
{0x4a8,0x4a9},
{0x4aa,0x4ab},
{0x4ac,0x4ad},
{0x4ae,0x4af},
{0x4b0,0x4b1},
{0x4b2,0x4b3},
{0x4b4,0x4b5},
{0x4b6,0x4b7},
{0x4b8,0x4b9},
{0x4ba,0x4bb},
{0x4bc,0x4bd},
{0x4be,0x4bf},
{0x4c1,0x4c2},
{0x4c3,0x4c4},
{0x4c7,0x4c8},
{0x4cb,0x4cc},
{0x4d0,0x4d1},
{0x4d2,0x4d3},
{0x4d4,0x4d5},
{0x4d6,0x4d7},
{0x4d8,0x4d9},
{0x4da,0x4db},
{0x4dc,0x4dd},
{0x4de,0x4df},
{0x4e0,0x4e1},
{0x4e2,0x4e3},
{0x4e4,0x4e5},
{0x4e6,0x4e7},
{0x4e8,0x4e9},
{0x4ea,0x4eb},
{0x4ee,0x4ef},
{0x4f0,0x4f1},
{0x4f2,0x4f3},
{0x4f4,0x4f5},
{0x4f8,0x4f9},
{0x531,0x561},
{0x532,0x562},
{0x533,0x563},
{0x534,0x564},
{0x535,0x565},
{0x536,0x566},
{0x537,0x567},
{0x538,0x568},
{0x539,0x569},
{0x53a,0x56a},
{0x53b,0x56b},
{0x53c,0x56c},
{0x53d,0x56d},
{0x53e,0x56e},
{0x53f,0x56f},
{0x540,0x570},
{0x541,0x571},
{0x542,0x572},
{0x543,0x573},
{0x544,0x574},
{0x545,0x575},
{0x546,0x576},
{0x547,0x577},
{0x548,0x578},
{0x549,0x579},
{0x54a,0x57a},
{0x54b,0x57b},
{0x54c,0x57c},
{0x54d,0x57d},
{0x54e,0x57e},
{0x54f,0x57f},
{0x550,0x580},
{0x551,0x581},
{0x552,0x582},
{0x553,0x583},
{0x554,0x584},
{0x555,0x585},
{0x556,0x586},
{0x10a0,0x10d0},
{0x10a1,0x10d1},
{0x10a2,0x10d2},
{0x10a3,0x10d3},
{0x10a4,0x10d4},
{0x10a5,0x10d5},
{0x10a6,0x10d6},
{0x10a7,0x10d7},
{0x10a8,0x10d8},
{0x10a9,0x10d9},
{0x10aa,0x10da},
{0x10ab,0x10db},
{0x10ac,0x10dc},
{0x10ad,0x10dd},
{0x10ae,0x10de},
{0x10af,0x10df},
{0x10b0,0x10e0},
{0x10b1,0x10e1},
{0x10b2,0x10e2},
{0x10b3,0x10e3},
{0x10b4,0x10e4},
{0x10b5,0x10e5},
{0x10b6,0x10e6},
{0x10b7,0x10e7},
{0x10b8,0x10e8},
{0x10b9,0x10e9},
{0x10ba,0x10ea},
{0x10bb,0x10eb},
{0x10bc,0x10ec},
{0x10bd,0x10ed},
{0x10be,0x10ee},
{0x10bf,0x10ef},
{0x10c0,0x10f0},
{0x10c1,0x10f1},
{0x10c2,0x10f2},
{0x10c3,0x10f3},
{0x10c4,0x10f4},
{0x10c5,0x10f5},
{0x1e00,0x1e01},
{0x1e02,0x1e03},
{0x1e04,0x1e05},
{0x1e06,0x1e07},
{0x1e08,0x1e09},
{0x1e0a,0x1e0b},
{0x1e0c,0x1e0d},
{0x1e0e,0x1e0f},
{0x1e10,0x1e11},
{0x1e12,0x1e13},
{0x1e14,0x1e15},
{0x1e16,0x1e17},
{0x1e18,0x1e19},
{0x1e1a,0x1e1b},
{0x1e1c,0x1e1d},
{0x1e1e,0x1e1f},
{0x1e20,0x1e21},
{0x1e22,0x1e23},
{0x1e24,0x1e25},
{0x1e26,0x1e27},
{0x1e28,0x1e29},
{0x1e2a,0x1e2b},
{0x1e2c,0x1e2d},
{0x1e2e,0x1e2f},
{0x1e30,0x1e31},
{0x1e32,0x1e33},
{0x1e34,0x1e35},
{0x1e36,0x1e37},
{0x1e38,0x1e39},
{0x1e3a,0x1e3b},
{0x1e3c,0x1e3d},
{0x1e3e,0x1e3f},
{0x1e40,0x1e41},
{0x1e42,0x1e43},
{0x1e44,0x1e45},
{0x1e46,0x1e47},
{0x1e48,0x1e49},
{0x1e4a,0x1e4b},
{0x1e4c,0x1e4d},
{0x1e4e,0x1e4f},
{0x1e50,0x1e51},
{0x1e52,0x1e53},
{0x1e54,0x1e55},
{0x1e56,0x1e57},
{0x1e58,0x1e59},
{0x1e5a,0x1e5b},
{0x1e5c,0x1e5d},
{0x1e5e,0x1e5f},
{0x1e60,0x1e61},
{0x1e62,0x1e63},
{0x1e64,0x1e65},
{0x1e66,0x1e67},
{0x1e68,0x1e69},
{0x1e6a,0x1e6b},
{0x1e6c,0x1e6d},
{0x1e6e,0x1e6f},
{0x1e70,0x1e71},
{0x1e72,0x1e73},
{0x1e74,0x1e75},
{0x1e76,0x1e77},
{0x1e78,0x1e79},
{0x1e7a,0x1e7b},
{0x1e7c,0x1e7d},
{0x1e7e,0x1e7f},
{0x1e80,0x1e81},
{0x1e82,0x1e83},
{0x1e84,0x1e85},
{0x1e86,0x1e87},
{0x1e88,0x1e89},
{0x1e8a,0x1e8b},
{0x1e8c,0x1e8d},
{0x1e8e,0x1e8f},
{0x1e90,0x1e91},
{0x1e92,0x1e93},
{0x1e94,0x1e95},
{0x1ea0,0x1ea1},
{0x1ea2,0x1ea3},
{0x1ea4,0x1ea5},
{0x1ea6,0x1ea7},
{0x1ea8,0x1ea9},
{0x1eaa,0x1eab},
{0x1eac,0x1ead},
{0x1eae,0x1eaf},
{0x1eb0,0x1eb1},
{0x1eb2,0x1eb3},
{0x1eb4,0x1eb5},
{0x1eb6,0x1eb7},
{0x1eb8,0x1eb9},
{0x1eba,0x1ebb},
{0x1ebc,0x1ebd},
{0x1ebe,0x1ebf},
{0x1ec0,0x1ec1},
{0x1ec2,0x1ec3},
{0x1ec4,0x1ec5},
{0x1ec6,0x1ec7},
{0x1ec8,0x1ec9},
{0x1eca,0x1ecb},
{0x1ecc,0x1ecd},
{0x1ece,0x1ecf},
{0x1ed0,0x1ed1},
{0x1ed2,0x1ed3},
{0x1ed4,0x1ed5},
{0x1ed6,0x1ed7},
{0x1ed8,0x1ed9},
{0x1eda,0x1edb},
{0x1edc,0x1edd},
{0x1ede,0x1edf},
{0x1ee0,0x1ee1},
{0x1ee2,0x1ee3},
{0x1ee4,0x1ee5},
{0x1ee6,0x1ee7},
{0x1ee8,0x1ee9},
{0x1eea,0x1eeb},
{0x1eec,0x1eed},
{0x1eee,0x1eef},
{0x1ef0,0x1ef1},
{0x1ef2,0x1ef3},
{0x1ef4,0x1ef5},
{0x1ef6,0x1ef7},
{0x1ef8,0x1ef9},
{0x1f08,0x1f00},
{0x1f09,0x1f01},
{0x1f0a,0x1f02},
{0x1f0b,0x1f03},
{0x1f0c,0x1f04},
{0x1f0d,0x1f05},
{0x1f0e,0x1f06},
{0x1f0f,0x1f07},
{0x1f18,0x1f10},
{0x1f19,0x1f11},
{0x1f1a,0x1f12},
{0x1f1b,0x1f13},
{0x1f1c,0x1f14},
{0x1f1d,0x1f15},
{0x1f28,0x1f20},
{0x1f29,0x1f21},
{0x1f2a,0x1f22},
{0x1f2b,0x1f23},
{0x1f2c,0x1f24},
{0x1f2d,0x1f25},
{0x1f2e,0x1f26},
{0x1f2f,0x1f27},
{0x1f38,0x1f30},
{0x1f39,0x1f31},
{0x1f3a,0x1f32},
{0x1f3b,0x1f33},
{0x1f3c,0x1f34},
{0x1f3d,0x1f35},
{0x1f3e,0x1f36},
{0x1f3f,0x1f37},
{0x1f48,0x1f40},
{0x1f49,0x1f41},
{0x1f4a,0x1f42},
{0x1f4b,0x1f43},
{0x1f4c,0x1f44},
{0x1f4d,0x1f45},
{0x1f59,0x1f51},
{0x1f5b,0x1f53},
{0x1f5d,0x1f55},
{0x1f5f,0x1f57},
{0x1f68,0x1f60},
{0x1f69,0x1f61},
{0x1f6a,0x1f62},
{0x1f6b,0x1f63},
{0x1f6c,0x1f64},
{0x1f6d,0x1f65},
{0x1f6e,0x1f66},
{0x1f6f,0x1f67},
{0x1f88,0x1f80},
{0x1f89,0x1f81},
{0x1f8a,0x1f82},
{0x1f8b,0x1f83},
{0x1f8c,0x1f84},
{0x1f8d,0x1f85},
{0x1f8e,0x1f86},
{0x1f8f,0x1f87},
{0x1f98,0x1f90},
{0x1f99,0x1f91},
{0x1f9a,0x1f92},
{0x1f9b,0x1f93},
{0x1f9c,0x1f94},
{0x1f9d,0x1f95},
{0x1f9e,0x1f96},
{0x1f9f,0x1f97},
{0x1fa8,0x1fa0},
{0x1fa9,0x1fa1},
{0x1faa,0x1fa2},
{0x1fab,0x1fa3},
{0x1fac,0x1fa4},
{0x1fad,0x1fa5},
{0x1fae,0x1fa6},
{0x1faf,0x1fa7},
{0x1fb8,0x1fb0},
{0x1fb9,0x1fb1},
{0x1fd8,0x1fd0},
{0x1fd9,0x1fd1},
{0x1fe8,0x1fe0},
{0x1fe9,0x1fe1},
{0x24b6,0x24d0},
{0x24b7,0x24d1},
{0x24b8,0x24d2},
{0x24b9,0x24d3},
{0x24ba,0x24d4},
{0x24bb,0x24d5},
{0x24bc,0x24d6},
{0x24bd,0x24d7},
{0x24be,0x24d8},
{0x24bf,0x24d9},
{0x24c0,0x24da},
{0x24c1,0x24db},
{0x24c2,0x24dc},
{0x24c3,0x24dd},
{0x24c4,0x24de},
{0x24c5,0x24df},
{0x24c6,0x24e0},
{0x24c7,0x24e1},
{0x24c8,0x24e2},
{0x24c9,0x24e3},
{0x24ca,0x24e4},
{0x24cb,0x24e5},
{0x24cc,0x24e6},
{0x24cd,0x24e7},
{0x24ce,0x24e8},
{0x24cf,0x24e9},
{0xff21,0xff41},
{0xff22,0xff42},
{0xff23,0xff43},
{0xff24,0xff44},
{0xff25,0xff45},
{0xff26,0xff46},
{0xff27,0xff47},
{0xff28,0xff48},
{0xff29,0xff49},
{0xff2a,0xff4a},
{0xff2b,0xff4b},
{0xff2c,0xff4c},
{0xff2d,0xff4d},
{0xff2e,0xff4e},
{0xff2f,0xff4f},
{0xff30,0xff50},
{0xff31,0xff51},
{0xff32,0xff52},
{0xff33,0xff53},
{0xff34,0xff54},
{0xff35,0xff55},
{0xff36,0xff56},
{0xff37,0xff57},
{0xff38,0xff58},
{0xff39,0xff59},
{0xff3a,0xff5a}
};

static int _find_upper(int ch)  {


	int low = 0;
	int high = CAPS_LEN -1;
	int middle;

	while( low <= high )
	{
		middle = ( low  + high ) / 2;

		if( ch < caps_table[ middle][0] ) {
			high = middle - 1; //search low end of array
		} else if ( caps_table[middle][0] < ch) {
			low = middle + 1; //search high end of array
		} else {
			return caps_table[middle][1];
		}
	}

	return ch;
}


static int _find_lower(int ch)  {


	int low = 0;
	int high = CAPS_LEN -2;
	int middle;

	while( low <= high )
	{
		middle = ( low  + high ) / 2;

		if( ch < reverse_caps_table[ middle][0] ) {
			high = middle - 1; //search low end of array
		} else if ( reverse_caps_table[middle][0] < ch) {
			low = middle + 1; //search high end of array
		} else {
			return reverse_caps_table[middle][1];
		}
	}

	return ch;
}
#endif
