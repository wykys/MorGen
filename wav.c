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

#include <stdio.h>
#include "wav.h"
#include "morse.h"

int8_t CreateMorseWav(int8_t *file_name, int8_t *vstup, uint32_t len, double t_space, double t_chars, uint16_t ToneF)
{
	FILE *fw;
    wav_t wav;

	// hlavička
    wav.RIFF.ChungID[0] = 'R';
    wav.RIFF.ChungID[1] = 'I';
    wav.RIFF.ChungID[2] = 'F';
    wav.RIFF.ChungID[3] = 'F';

    wav.RIFF.Format[0] = 'W';
    wav.RIFF.Format[1] = 'A';
    wav.RIFF.Format[2] = 'V';
    wav.RIFF.Format[3] = 'E';

    // fmt
    wav.fmt.SubChung1ID[0] = 'f';
    wav.fmt.SubChung1ID[1] = 'm';
    wav.fmt.SubChung1ID[2] = 't';
    wav.fmt.SubChung1ID[3] = ' ';
    wav.fmt.SubChung1Size = 16;
    wav.fmt.AudioFormat = 1; // pro PCM
    wav.fmt.NumChannels = 1; // mono
    wav.fmt.SampleRate = SAMPLE_RATE;
    wav.fmt.BitsPerSample = 16;
    wav.fmt.BlockAlign = wav.fmt.NumChannels * wav.fmt.BitsPerSample / 8; // počet Bytů na vzorek ze všech kanálů
    wav.fmt.ByteRate = SAMPLE_RATE * wav.fmt.BlockAlign; // počet B za s

    // data
    wav.data.SubChung2ID[0] = 'd';
    wav.data.SubChung2ID[1] = 'a';
    wav.data.SubChung2ID[2] = 't';
    wav.data.SubChung2ID[3] = 'a';
    wav.data.samples = NULL;

    len = CreateSamples(&wav, vstup, len, t_space, t_chars, ToneF, SAMPLE_RATE);
    if (!len)
		return -1;

    wav.data.SubChung2Size = len;
    wav.RIFF.ChungSize = 36 + len;

    if ((fw = fopen(file_name, "wb")) != NULL)
	{
		fwrite(&wav.RIFF, 12, 1, fw);
		fwrite(&wav.fmt, 24, 1, fw);
		fwrite(&wav.data, 8, 1, fw);
		fwrite(wav.data.samples, len, 1, fw);

		fclose(fw);
	}
	else
	{
		free(wav.data.samples);
		printf("\nSoubor se nepodarilo vytvorit.\n\n");
		return -1;
	}

	free(wav.data.samples);
	return 0;
}
