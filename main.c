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
 * program generuje wav soubory s morseovkou
 * vstupem je textový soubor
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
#include <stdlib.h>
#include "stype.h"
#include "wav.h"
#include "morse.h"

int main(void)
{
    int8_t file_name_in[30] = "vstup.txt";
    int8_t file_name_out[30] = "vystup.wav";
    int8_t file_name_spelling[30] = "spelling.wav";
	int8_t key;
    uint32_t len;
	int8_t *vstup;
    uint16_t wpm_space = 16;
    uint16_t wpm_chars = 12;
    double t_space, t_chars;
    uint16_t ToneF = 600; // kmytočet tónu

	// výpočet časů slov a mezer
	t_space = DotTime(wpm_space);
	t_chars = DotTime(wpm_chars);
	// spočítá délky morse kódů
	MorseTableCodeTime(t_space, t_chars, SAMPLE_RATE);

	do
	{
		system("cls");
		printf("\n");
		printf("   888b     d888                   .d8888b.         wykys 2015\n");
		printf("   8888b   d8888                  d88P  Y88b                  \n");
		printf("   88888b.d88888                  888    888                  \n");
		printf("   888Y88888P888  .d88b.  888d888 888         .d88b.  88888b. \n");
		printf("   888 Y888P 888 d88\"\"88b 888P\"   888  88888 d8P  Y8b 888 \"88b\n");
		printf("   888  Y8P  888 888  888 888     888    888 88888888 888  888\n");
		printf("   888   \"   888 Y88..88P 888     Y88b  d88P Y8b.     888  888\n");
		printf("   888       888  \"Y88P\"  888      \"Y8888P88  \"Y8888  888  888\n");
		printf("\n");

		printf("Aktualni nastaveni:\n");
		printf("                    1. vstupni soubor: %s\n", file_name_in);
		printf("                    2. vystupni soubor: %s\n", file_name_out);
		printf("                    3. hlaskovaci soubor: %s\n", file_name_spelling);
		printf("                    4. frekvence tonu: %hu Hz\n", ToneF);
		printf("                    5. WPM mezer: %hu\n", wpm_space);
		printf("                    6. WPM symbolu: %hu\n", wpm_chars);
		printf("                    7. Zobras morseovu tabulku\n\n");

		printf("Pro vygenerovani wavu stisknete Enter\n");
		printf("pro napovedu H, pokud chcete zmenet nastaveni\n");
		printf("zadejte jeho cislo, potvrdte stiskem Enteru >>> ");
		key = fgetc(stdin);
		fflush(stdin);

		if (key != '\n')
			switch (key)
			{
			case '1':
				printf("Zadejte nazev vstupniho souboru >>> ");
				scanf("%s", file_name_in);
				fflush(stdin);
				break;
			case '2':
				printf("Zadejte nazev vystupniho souboru >>> ");
				scanf("%s", file_name_out);
				fflush(stdin);
				break;
			case '3':
				printf("Zadejte nazev vystupniho souboru (hlaskovaci) >>> ");
				scanf("%s", file_name_spelling);
				fflush(stdin);
				break;
			case '4':
				printf("Zadejte frekvenci tonu (cele cislo) >>> ");
				scanf("%hu", &ToneF);
				fflush(stdin);
				break;
			case '5':
				printf("Zadejte WPM mezer >>> ");
				scanf("%hu", &wpm_space);
				fflush(stdin);
				break;
			case '6':
				printf("WPM symbolu: >>> ");
				scanf("%hu", &wpm_chars);
				fflush(stdin);
				break;
			case '7':
				printf("\n");
				MorseTableShow();
				system("pause");
				break;
			default :

				printf("\n\n\tPopis funkce:\n");
				printf("\t   Program nacte text ze vstupniho souboru a vygeneruje\n");
				printf("\t   dva vystupni wav soubory. V jednom souboru je morseovka\n");
				printf("\t   a ve druhem hlaskovani vstupniho textu.");

				printf("\n\n\tParametry wav vystupu:\n");
				printf("\t   Vzorkovaci frekvence: %u Hz\n", SAMPLE_RATE);
				printf("\t   Bitove rozliseni vzorku 16 b\n");
				printf("\t   Pocet zvukovych stop: 1 (mono)");

				printf("\n\n\tPri ovladani pouzivejte hlavu.\n");
				printf("\tVytvoril wykys 2015\n\n");
				system("pause");
			}

		// výpočet časů slov a mezer
		t_space = DotTime(wpm_space);
		t_chars = DotTime(wpm_chars);
		// spočítá délky morse kódů
		MorseTableCodeTime(t_space, t_chars, SAMPLE_RATE);

		printf("===============================================================\n\n");

	} while(key != '\n');

	// získání textu pro převod
    if ((len = DataLoad(file_name_in, &vstup)) == 0)
    {
		system("pause");
		return -1;
    }
    // vytvoření wav souboru s morseovkou
	if (CreateMorseWav(file_name_out, vstup, len, t_space, t_chars, ToneF) == -1)
	{
		free(vstup);
		system("pause");
		return -1;
	}

	// vytvoření wav souboru s hláskováním
	if (CreateSpellingWav(file_name_spelling, vstup, len, t_space) == -1)
	{
		free(vstup);
		system("pause");
		return -1;
	}

	// uvolnění paměti se vstupním textem
	free(vstup);
	system("pause");
    return 0;
}
