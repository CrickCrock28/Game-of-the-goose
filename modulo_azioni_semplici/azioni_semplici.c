#include "azioni_semplici.h"

int chiedere_intero(const char* messaggio, int valore_minimo, int valore_massimo, int riga, int colonna) {
    int y;
    int num;

    spostare_cursore(colonna, riga);

    y = colonna;
    while (y <= NUMERO_COLONNA_MASSIMA) {
        printf(" ");
        y++;
    }

    spostare_cursore(colonna, riga);
    printf("%s", messaggio);
    scanf("%d", &num);
    while (num < valore_minimo || num > valore_massimo) {
        spostare_cursore(colonna, riga + 1);
        printf("Il valore deve essere compreso tra: %d e %d", valore_minimo, valore_massimo); //MAGICOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
        scanf("%d", &num);
    }

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

    srand(time(NULL));
    numero_casuale = (rand() % massimo) + minimo;

    return numero_casuale;
}