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
 * knihovna pro práci s morse kódem
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

#ifndef MORSE_H_INCLUDED
#define MORSE_H_INCLUDED

#define MORSE_CHAR_NUM  51

#include "stype.h"
#include "wav.h"

typedef struct
{
    int8_t symbol;
    int8_t code[7];
    uint8_t dot;
    uint8_t dash;
    double time;
    uint32_t samples;
} mor_char_t;

mor_char_t MorseTable[MORSE_CHAR_NUM];

void MorseTableShow(void);
uint32_t DataLoad(const int8_t *file_name, int8_t **vstup);
double DotTime(uint16_t wpm);
void MorseTableCodeTime(double t_space, double t_chars, uint16_t Fs);
uint8_t GetIndexFromMorseTable(int8_t symbol);
uint32_t SampleSize(int8_t *text, uint32_t text_len, uint32_t s_char_space, uint32_t s_word_space);
uint32_t CreateSamples(wav_t *wav_p, int8_t *text, uint32_t text_len, double t_space, double t_chars, uint16_t ToneF, uint16_t Fs);

#endif // MORSE_H_INCLUDED
