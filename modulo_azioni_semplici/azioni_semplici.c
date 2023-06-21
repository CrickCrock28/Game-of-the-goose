#include "azioni_semplici.h"

int chiedere_intero(const char* messaggio, int valore_minimo, int valore_massimo, int x, int y) {
    int colonna;
    int num;

    spostare_cursore(x, y);

    colonna = y;
    while (colonna <= NUMERO_COLONNA_MASSIMA) {
        printf(" ");
        colonna++;
    }
    spostare_cursore(x, y);
    printf("%s", messaggio);
    scanf("%d", &num);
    while (num < valore_minimo || num > valore_massimo) {
        spostare_cursore(x, y + 1);
        printf("Il valore deve essere compreso tra: %d e %d", valore_minimo, valore_massimo);
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