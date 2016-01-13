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

#include <math.h>
#include <stdio.h>
#include "morse.h"

// tabulka symbolù kódù a jejich délek
mor_char_t MorseTable[MORSE_CHAR_NUM] = {
    { '0',  "-----",    0, 5, 0, 0 }, //  0
    { '1',  ".----",    1, 4, 0, 0 }, //  1
    { '2',  "..---",    2, 3, 0, 0 }, //  2
    { '3',  "...--",    3, 2, 0, 0 }, //  3
    { '4',  "....-",    4, 1, 0, 0 }, //  4
    { '5',  ".....",    5, 0, 0, 0 }, //  5
    { '6',  "-....",    4, 1, 0, 0 }, //  6
    { '7',  "--...",    3, 2, 0, 0 }, //  7
    { '8',  "---..",    2, 3, 0, 0 }, //  8
    { '9',  "----.",    1, 4, 0, 0 }, //  9
    { 'A',  ".-",       1, 1, 0, 0 }, // 10
    { 'B',  "-...",     3, 1, 0, 0 }, // 11
    { 'C',  "-.-.",     2, 2, 0, 0 }, // 12
    { 'D',  "-..",      2, 1, 0, 0 }, // 13
    { 'E',  ".",        1, 0, 0, 0 }, // 14
    { 'F',  "..-.",     3, 1, 0, 0 }, // 15
    { 'G',  "--.",      1, 2, 0, 0 }, // 16
    { 'H',  "....",     4, 0, 0, 0 }, // 17
    { 'I',  "..",       2, 0, 0, 0 }, // 18
    { 'J',  ".---",     1, 3, 0, 0 }, // 19
    { 'K',  "-.-",      1, 2, 0, 0 }, // 20
    { 'L',  ".-..",     3, 1, 0, 0 }, // 21
    { 'M',  "--",       0, 2, 0, 0 }, // 22
    { 'N',  "-.",       1, 1, 0, 0 }, // 23
    { 'O',  "---",      0, 3, 0, 0 }, // 24
    { 'P',  ".--.",     2, 2, 0, 0 }, // 25
    { 'Q',  "--.-",     1, 3, 0, 0 }, // 26
    { 'R',  ".-.",      2, 1, 0, 0 }, // 27
    { 'S',  "...",      3, 0, 0, 0 }, // 28
    { 'T',  "-",        0, 1, 0, 0 }, // 29
    { 'U',  "..-",      2, 1, 0, 0 }, // 30
    { 'V',  "...-",     3, 1, 0, 0 }, // 31
    { 'W',  ".--",      1, 2, 0, 0 }, // 32
    { 'X',  "-..-",     2, 2, 0, 0 }, // 33
    { 'Y',  "-.--",     1, 3, 0, 0 }, // 34
    { 'Z',  "--..",     2, 2, 0, 0 }, // 35
    { '?',  "..--..",   4, 2, 0, 0 }, // 36
    { ',',  "--..--",   2, 4, 0, 0 }, // 37
    { '!',  "--...-",   3, 3, 0, 0 }, // 38
    { '.',  ".-.-.-",   3, 3, 0, 0 }, // 39
    { ';',  "-.-.-.",   3, 3, 0, 0 }, // 40
    { '/',  "-..-.",    3, 2, 0, 0 }, // 41
    { '=',  "-...-",    3, 2, 0, 0 }, // 42
    { '-',  "-....-",   4, 2, 0, 0 }, // 43
    { '\t', ".----.",   2, 4, 0, 0 }, // 44
    { '(',  "-.--.",    2, 3, 0, 0 }, // 45
    { ')',  "-.--.-",   2, 4, 0, 0 }, // 46
    { '\"', ".-..-.",   4, 2, 0, 0 }, // 47
    { ':',  "---...",   3, 3, 0, 0 }, // 48
    { '_',  "..--.-",   3, 3, 0, 0 }, // 49
    { '@',  ".--.-.",   3, 3, 0, 0 }  // 50
};

// zobrazí tabulku morseovy abecedy
void MorseTableShow(void)
{MorseTable[44].symbol = ' ';
    uint8_t i;

    MorseTable[44].symbol = ' ';
    for (i=0; i < MORSE_CHAR_NUM; i++)
    {
        printf("\t%c %7s\t%lf s\t%8u samples\n", MorseTable[i].symbol, MorseTable[i].code, MorseTable[i].time, MorseTable[i].samples);
    }
    MorseTable[44].symbol = '\t';
    putchar('\n');
}

// naète data ze souboru
uint32_t DataLoad(const int8_t *file_name, int8_t **vstup)
{
    FILE *fr;
    uint32_t i, len = 0;
    int8_t *data;

    if ((fr = fopen(file_name, "rt")) != NULL)
    {
        // zjistíme velikost souboru
        fseek(fr, 0, SEEK_END);
        len = ftell(fr);
        fseek(fr, 0, SEEK_SET);
        clearerr(fr); // zruší EOF s toho jak sem šel na konec souboru

        if ((data = (int8_t *)malloc(len+1)) != NULL)
        {
            for (i=0; (data[i] = fgetc(fr)) != EOF; i++)
            {
                if (data[i] >= 'a' && data[i] <= 'z')
                    data[i] -= 'a'-'A';
                else if (data[i] >= 'A' && data[i] <= 'Z')
                    ;
                else if (data[i] >= '0' && data[i] <= '9')
                    ;
                else if (data[i] == '?' || data[i] == ',' || data[i] == '!'  || \
                         data[i] == '.' || data[i] == ';' || data[i] == '/'  || \
                         data[i] == '=' || data[i] == '-' || data[i] == '\t' || \
                         data[i] == '(' || data[i] == ')' || data[i] == '\"' || \
                         data[i] == ':' || data[i] == '_' || data[i] == '@' )
                    ;
                else
                    i--;
            }
            data[i] = '\0';
            *vstup = data;
        }
        else
        {
            printf("\nNepodarilo se alokovat pamet.\n\n");
            return 0;
        }
        fclose(fr);
    }
    else
    {
        printf("\nSoubor se nepodarilo otevrit.\n\n");
        return 0;
    }
    len = i;
    return len;
}

// s WPS vypoèítá èas základní jednotky (teèky)
double DotTime(uint16_t wpm)
{
    return (double) 60 / (22 * wpm);
}

// spoèítá doby trvání morseových kódù a doplní je do tabulky
void MorseTableCodeTime(double t_space, double t_chars, uint16_t Fs)
{
    uint8_t i;
    uint32_t samples;
    double time;
    double Ts = (double) 1 / Fs;

    uint32_t s_dot = t_chars / Ts;
    uint32_t s_space = t_space / Ts;
    uint32_t s_dash = 3 * t_chars / Ts;

    for (i=0; i < MORSE_CHAR_NUM; i++)
    {
        time = 0;
        time += MorseTable[i].dot * t_chars;
        time += MorseTable[i].dash * t_chars * 3; // èárka je 3 * delší než teèka
        time += (MorseTable[i].dot + MorseTable[i].dash - 1) * t_space;

        samples = 0;
        samples += MorseTable[i].dot * s_dot;
        samples += MorseTable[i].dash * s_dash; // èárka je 3 * delší než teèka
        samples += (MorseTable[i].dot + MorseTable[i].dash - 1) * s_space;

        MorseTable[i].time = time;
        MorseTable[i].samples = samples;
    }
}

// vrátí, na kterém indexu v MorseTable se hledaný symbol nachází
uint8_t GetIndexFromMorseTable(int8_t symbol)
{
    uint8_t index;

    if (symbol >= 'A' && symbol <= 'Z') index = symbol - 'A' + 10;
    else if (symbol == '?')             index = 36;
    else if (symbol == ',')             index = 37;
    else if (symbol == '!')             index = 38;
    else if (symbol == '.')             index = 39;
    else if (symbol == ';')             index = 40;
    else if (symbol == '/')             index = 41;
    else if (symbol == '=')             index = 42;
    else if (symbol == '-')             index = 43;
    else if (symbol == '\t')            index = 44;
    else if (symbol == '(')             index = 45;
    else if (symbol == ')')             index = 46;
    else if (symbol == '\"')            index = 47;
    else if (symbol == ':')             index = 48;
    else if (symbol == '_')             index = 49;
    else if (symbol == '@')             index = 50;
    else                                index = symbol - '0';

    return index;
}

// Vrátí kolik Bytù zaberou vzorky
uint32_t SampleSize(int8_t *text, uint32_t text_len, uint32_t s_char_space, uint32_t s_word_space)
{
    uint32_t i, index, samples_len = 0;

    printf("Vstup: %s\n", text);

    for (i=0; i < text_len; i++)
    {
        index = GetIndexFromMorseTable(text[i]);
        printf("%7s  ", MorseTable[index].code);
        samples_len += MorseTable[index].samples;

        if ((i+1) % 5)
        {
            samples_len += s_char_space;
            printf("\t");
        }
        else
        {
            samples_len += s_word_space;
            printf("\n");
        }
    }
    printf("\n\n");
    return samples_len * sizeof(int16_t);
}

// vygeneruje vzorky pro tvorbu wav souboru se vstupního textu
uint32_t CreateSamples(wav_t *wav_p, int8_t *text, uint32_t text_len, double t_space, double t_chars, uint16_t ToneF, uint16_t Fs)
{
    double Ts = (double) 1 / Fs;
    double time;

    uint32_t s_dot = t_chars / Ts;
    uint32_t s_dash = 3 * t_chars / Ts;

    uint32_t s_space = t_space / Ts;
    uint32_t s_char_space = 3 * t_space / Ts;
    uint32_t s_word_space = 7 * t_space / Ts;

    uint32_t samples_len, i, j, s, samp_index;
    int16_t *samples;
    uint8_t index;

    samples_len = SampleSize(text, text_len, s_char_space, s_word_space);
    samples = (int16_t *)malloc(samples_len);
    if (samples == NULL)
    {
        printf("\nNepodarilo se alokovat pamet.\n\n");
        return 0;
    }

    // generování vzorkù
    for (samp_index=0, i=0; i < text_len; i++)
    {
        index = GetIndexFromMorseTable(text[i]);
        for (j=0; MorseTable[index].code[j] != '\0'; j++)
        {
            if (MorseTable[index].code[j] == '.')
            {
                for (time=0, s=0; s < s_dot; s++, samp_index++, time += Ts)
                    samples[samp_index] = 27000 * sin(2 * M_PI * ToneF * time);
            }
            else
            {
                for (time=0, s=0; s < s_dash; s++, samp_index++, time += Ts)
                    samples[samp_index] = 27000 * sin(2 * M_PI * ToneF * time);
            }
            if (j < (MorseTable[index].dot + MorseTable[index].dash - 1))
            {
                for (s=0; s < s_space; s++, samp_index++)
                    samples[samp_index] = 0;
            }
        }
        // mezera mezi symboly
        if ((i+1) % 5)
        {
            for (s=0; s < s_char_space; s++, samp_index++)
                samples[samp_index] = 0;
        }
        // mezera mezi slovy
        else
        {
            for (s=0; s < s_word_space; s++, samp_index++)
                samples[samp_index] = 0;
        }
    }

    printf("Vysilani bude trvat: %.3lf s.\n", (double) (samples_len/sizeof(int16_t)) * Ts);

    wav_p->data.samples = samples;
    return samples_len;
}
