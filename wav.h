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
 * knihovna pro práci s wav soubory
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

#ifndef WAV_H_INCLUDED
#define WAV_H_INCLUDED

#define BSWAP 1
#if BSWAP == 1
	#define BSWAP16(n)	__builtin_bswap16((n))
	#define BSWAP32(n)	__builtin_bswap32((n))
#else
	#define BSWAP16(n)	( ((n) >> 8 & 0x00FF) | ((n) << 8 & 0xFF00) )
	#define BSWAP32(n)	( ((n) >> 24 & 0x000000FF) | ((n) >> 8 & 0x0000FF00) | ((n) << 8 & 0x00FF0000) | ((n) << 24 & 0xFF000000))
#endif // BSWAP

#define SAMPLE_RATE 8000

#include "stype.h"

typedef struct
{
	uint8_t	 ChungID[4];
	uint32_t ChungSize;
	uint8_t	 Format[4];
} riff_t;

typedef struct
{
	uint8_t  SubChung1ID[4];
	uint32_t SubChung1Size;
	uint16_t AudioFormat;
	uint16_t NumChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;
	uint16_t BlockAlign;
	uint16_t BitsPerSample;
} fmt_t;

typedef struct
{
	uint8_t  SubChung2ID[4];
	uint32_t SubChung2Size;
	int16_t *samples;
} data_t;

typedef struct
{
	riff_t	RIFF;
	fmt_t	fmt;
	data_t	data;
} wav_t;

int8_t CreateMorseWav(int8_t *file_name, int8_t *vstup, uint32_t len, double t_space, double t_chars, uint16_t ToneF);

#endif // WAV_H_INCLUDED
