// PERFETTO
#include "gestire_azioni_semplici.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "..\\costanti.h"

#include "..\\modulo_spostare_cursore\\spostare_cursore.h"


#define MESSAGGIO_ERRORE "Il valore deve essere compreso tra %d e %d, riprova."

#define CARATTERE_SPAZIO_VUOTO ' '


int ottenere_riga_cursore() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    int riga = consoleInfo.dwCursorPosition.Y;

    return riga;
}

int ottenere_colonna_cursore() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    int colonna = consoleInfo.dwCursorPosition.X;

    return colonna;
}

int chiedere_intero(const char* messaggio, int valore_minimo, int valore_massimo, int riga, int colonna) {
    int num, riga_errore;

    spostare_cursore(colonna, riga);
    printf("%s", messaggio);
    scanf("%d", &num);
    riga_errore = ottenere_riga_cursore();
    while (num < valore_minimo || num > valore_massimo) {
        printf(MESSAGGIO_ERRORE, valore_minimo, valore_massimo);
        spostare_cursore(colonna, riga);

        printf("%s", messaggio);
        getchar(); // Consuma il \n presente nel buffer
        scanf("%d", &num);
    }
    stampare_riga_vuota(riga_errore, NUMERO_COLONNA_MASSIMA);

    return num;
}

int calcolare_proporzione(int n_1, int d_1, int d_2) {
	int n_2, x;

	x = n_1 * d_2 / d_1;
	n_2 = (int) x;

	return n_2;
}

int generare_numero_casuale(int minimo, int massimo) {
    int numero_casuale;

    numero_casuale = (rand() % massimo) + minimo;

    return numero_casuale;
}

void stampare_riga_vuota(int riga, int numero_colonna_massima) {
	int colonna = PRIMA_COORDINATA_SCHERMO;

	spostare_cursore(colonna, riga);
    while (colonna <= numero_colonna_massima) {
        printf("%c", CARATTERE_SPAZIO_VUOTO);
        colonna= colonna+ 1;
    }
	return;
}
