#include "stdio.h"
#include "gotoxy.h"

#define NUMERO_COLONNA_MASSIMA 80
#define FINE_STRINGA '\0'

int chiedere_intero(const char* messaggio, int valore_minimo, int valore_massimo, int x, int y) {
    int colonna;
    int num;

    GotoXY(x, y);

    colonna = y;
    while (colonna <= NUMERO_COLONNA_MASSIMA) {
        stampare_a_video(" ");
        colonna++;
    }
    GotoXY(x, y);
    printf("%s", messaggio);
    scanf("%d", &num);
    while (num < valore_minimo || num > valore_massimo) {
        GotoXY(x, y + 1);
        printf("Il valore deve essere compreso tra: %d e %d", valore_minimo, valore_massimo);
        scanf("%d", &num);
    }

    return num;
}