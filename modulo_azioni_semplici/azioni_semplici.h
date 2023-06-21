#ifndef AZIONI_SEMPLICI_H_
#define AZIONI_SEMPLICI_H_

#include <stdio.h>
#include "../spostare_cursore.h"

#define NUMERO_COLONNA_MASSIMA 80
#define FINE_STRINGA '\0'

int chiedere_intero(const char* messaggio, int valore_minimo, int valore_massimo, int x, int y);
int calcolare_proporzione(int n_1, int d_1, int d_2);
#endif
