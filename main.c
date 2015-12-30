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
	int8_t key;
    uint32_t len;
	int8_t *vstup;
    uint16_t wpm_space = 16;
    uint16_t wpm_chars = 12;
    double t_space, t_chars;
    uint16_t ToneF = 600; // kmytočet tónu

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
		printf("                    3. frekvence tonu: %hu Hz\n", ToneF);
		printf("                    4. WPM mezer: %hu\n", wpm_space);
		printf("                    5. WPM symbolu: %hu\n\n", wpm_chars);

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
				printf("Zadejte frekvenci tonu (cele cislo) >>> ");
				scanf("%hu", &ToneF);
				fflush(stdin);
				break;
			case '4':
				printf("Zadejte WPM mezer >>> ");
				scanf("%hu", &wpm_space);
				fflush(stdin);
				break;
			case '5':
				printf("WPM symbolu: >>> ");
				scanf("%hu", &wpm_chars);
				fflush(stdin);
				break;
			default :
				printf("\n\tVytvoril wykys 2015\n");
				printf("\tPri ovladani pouzivejte hlavu.\n\n");
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
    // vytvoření wav souboru
	if (CreateMorseWav(file_name_out, vstup, len, t_space, t_chars, ToneF) == -1)
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
