/*
 *
 * 888b     d888                   .d8888b.         wykys 2015
 * 8888b   d8888                  d88P  Y88b
 * 88888b.d88888                  888    888
 * 888Y88888P888  .d88b.  888d888 888         .d88b.  88888b.
 * 888 Y888P 888 d88""88b 888P"   888  88888 d8P  Y8b 888 "88b
 * 888  Y8P  888 888  888 888     888    888 88888888 888  888
 * 888   "   888 Y88..88P 888     Y88b  d88P Y8b.     888  888
 * 888       888  "Y88P"  888      "Y8888P88  "Y8888  888  888
 *
 *
 * knihovna pro generování hláskování
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SPELLING_TABLE_H_INCLUDED
#define SPELLING_TABLE

#define SPELLING_CHAR_NUM   51

#include "stype.h"

// délky čísel
#define LEN_AUDIO_0     7781
#define LEN_AUDIO_1     5859
#define LEN_AUDIO_2     5938
#define LEN_AUDIO_3     7371
#define LEN_AUDIO_4     7576
#define LEN_AUDIO_5     6143
#define LEN_AUDIO_6     6552
#define LEN_AUDIO_7     7576
#define LEN_AUDIO_8     6962
#define LEN_AUDIO_9     7166

// délky písmen
#define LEN_AUDIO_A     7985
#define LEN_AUDIO_B     8395
#define LEN_AUDIO_C     6962
#define LEN_AUDIO_D     7985
#define LEN_AUDIO_E     7576
#define LEN_AUDIO_F     8395
#define LEN_AUDIO_G     7781
#define LEN_AUDIO_H     6962
#define LEN_AUDIO_I     7576
#define LEN_AUDIO_J     7166
#define LEN_AUDIO_K     7985
#define LEN_AUDIO_L     9214
#define LEN_AUDIO_M     7781
#define LEN_AUDIO_N     9623
#define LEN_AUDIO_O     9419
#define LEN_AUDIO_P     6143
#define LEN_AUDIO_Q     6347
#define LEN_AUDIO_R     7781
#define LEN_AUDIO_S     8600
#define LEN_AUDIO_T     8804
#define LEN_AUDIO_U     7985
#define LEN_AUDIO_V     9828
#define LEN_AUDIO_W     10852
#define LEN_AUDIO_X     8600
#define LEN_AUDIO_Y     11057
#define LEN_AUDIO_Z     9214

// speciální znaky
#define LEN_AUDIO_Z1    8804
#define LEN_AUDIO_Z2    7576
#define LEN_AUDIO_Z3    9214
#define LEN_AUDIO_Z4    6962
#define LEN_AUDIO_Z5    7166
#define LEN_AUDIO_Z6    6757
#define LEN_AUDIO_Z7    8600
#define LEN_AUDIO_Z8    9419
#define LEN_AUDIO_Z9    10238
#define LEN_AUDIO_ZA    14333
#define LEN_AUDIO_ZB    11466
#define LEN_AUDIO_ZC    9623
#define LEN_AUDIO_ZD    9009
#define LEN_AUDIO_ZE    9214
#define LEN_AUDIO_ZF    8075

// vzorky čísel
const int16_t audio_0[LEN_AUDIO_0];
const int16_t audio_1[LEN_AUDIO_1];
const int16_t audio_2[LEN_AUDIO_2];
const int16_t audio_3[LEN_AUDIO_3];
const int16_t audio_4[LEN_AUDIO_4];
const int16_t audio_5[LEN_AUDIO_5];
const int16_t audio_6[LEN_AUDIO_6];
const int16_t audio_7[LEN_AUDIO_7];
const int16_t audio_8[LEN_AUDIO_8];
const int16_t audio_9[LEN_AUDIO_9];

// vzorky písmen
const int16_t audio_a[LEN_AUDIO_A];
const int16_t audio_b[LEN_AUDIO_B];
const int16_t audio_c[LEN_AUDIO_C];
const int16_t audio_d[LEN_AUDIO_D];
const int16_t audio_e[LEN_AUDIO_E];
const int16_t audio_f[LEN_AUDIO_F];
const int16_t audio_g[LEN_AUDIO_G];
const int16_t audio_h[LEN_AUDIO_H];
const int16_t audio_i[LEN_AUDIO_I];
const int16_t audio_j[LEN_AUDIO_J];
const int16_t audio_k[LEN_AUDIO_K];
const int16_t audio_l[LEN_AUDIO_L];
const int16_t audio_m[LEN_AUDIO_M];
const int16_t audio_n[LEN_AUDIO_N];
const int16_t audio_o[LEN_AUDIO_O];
const int16_t audio_p[LEN_AUDIO_P];
const int16_t audio_q[LEN_AUDIO_Q];
const int16_t audio_r[LEN_AUDIO_R];
const int16_t audio_s[LEN_AUDIO_S];
const int16_t audio_t[LEN_AUDIO_T];
const int16_t audio_u[LEN_AUDIO_U];
const int16_t audio_v[LEN_AUDIO_V];
const int16_t audio_w[LEN_AUDIO_W];
const int16_t audio_x[LEN_AUDIO_X];
const int16_t audio_y[LEN_AUDIO_Y];
const int16_t audio_z[LEN_AUDIO_Z];

// vzorky speciálních znaků
const int16_t audio_z1[LEN_AUDIO_Z1];
const int16_t audio_z2[LEN_AUDIO_Z2];
const int16_t audio_z3[LEN_AUDIO_Z3];
const int16_t audio_z4[LEN_AUDIO_Z4];
const int16_t audio_z5[LEN_AUDIO_Z5];
const int16_t audio_z6[LEN_AUDIO_Z6];
const int16_t audio_z7[LEN_AUDIO_Z7];
const int16_t audio_z8[LEN_AUDIO_Z8];
const int16_t audio_z9[LEN_AUDIO_Z9];
const int16_t audio_zA[LEN_AUDIO_ZA];
const int16_t audio_zB[LEN_AUDIO_ZB];
const int16_t audio_zC[LEN_AUDIO_ZC];
const int16_t audio_zD[LEN_AUDIO_ZD];
const int16_t audio_zE[LEN_AUDIO_ZE];
const int16_t audio_zF[LEN_AUDIO_ZF];

typedef struct
{
    int16_t *samples;
    uint32_t len;
} spelling_char_t;

const spelling_char_t SpellingTable[SPELLING_CHAR_NUM];

#endif // SPELLING_TABLE_H_INCLUDED
