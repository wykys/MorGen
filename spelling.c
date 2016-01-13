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

#include <stdio.h>
#include "spelling_table.h"
#include "morse.h"
#include "wav.h"


// Vrátí kolik Bytů zaberou vzorky
uint32_t SpellingSampleSize(int8_t *text, uint32_t text_len, uint32_t s_char_space, uint32_t s_word_space)
{
    uint32_t i, index, samples_len = 0;

    for (i=0; i < text_len; i++)
    {
        index = GetIndexFromMorseTable(text[i]);
        samples_len += SpellingTable[index].len;

        if ((i+1) % 5)
        {
            samples_len += s_char_space;
        }
        else
        {
            samples_len += s_word_space;
        }
    }
    return samples_len * sizeof(int16_t);
}

// vygeneruje vzorky pro tvorbu wav souboru spelování se vstupního textu
uint32_t CreateSpellingSamples(wav_t *wav_p, int8_t *text, uint32_t text_len, double t_space, uint16_t Fs)
{
    double Ts = (double) 1 / Fs;
    double time;

    uint32_t s_char_space = 3 * t_space / Ts;
    uint32_t s_word_space = 7 * t_space / Ts;

    uint32_t samples_len, i, j, s, samp_index;
    int16_t *samples;
    uint8_t index;

    samples_len = SpellingSampleSize(text, text_len, s_char_space, s_word_space);

    samples = (int16_t *)malloc(samples_len);
    if (samples == NULL)
    {
        printf("\nNepodarilo se alokovat pamet.\n\n");
        return 0;
    }

    // generování vzorkù
    for (samp_index=0, i=0; i < text_len; i++)
    {
        printf("%c", text[i]);
        index = GetIndexFromMorseTable(text[i]);
        for (j=0; j < SpellingTable[index].len; j++, samp_index++)
        {
            samples[samp_index] = SpellingTable[index].samples[j];
        }
        // mezera mezi symboly
        if ((i+1) % 5)
        {
            printf(" ");
            for (s=0; s < s_char_space; s++, samp_index++)
                samples[samp_index] = 0;
        }
        // mezera mezi slovy
        else
        {
            if ((i+1) % 25 == 0)
                printf("\n");
            else
                printf("    ");
            for (s=0; s < s_word_space; s++, samp_index++)
                samples[samp_index] = 0;
        }
    }
    printf("\n\n");
    printf("Hlaskovani bude trvat: %.3lf s.\n", (double) (samples_len/sizeof(int16_t)) * Ts);

    wav_p->data.samples = samples;
    return samples_len;
}
