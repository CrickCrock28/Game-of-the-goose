#ifndef GESTIRE_AZIONI_SEMPLICI_H_
#define GESTIRE_AZIONI_SEMPLICI_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../spostare_cursore.h"

#define NUMERO_COLONNA_MASSIMA 80
#define FINE_STRINGA '\0'
#define MESSAGGIO "Il valore deve essere compreso tra:\0"
int chiedere_intero(const char* messaggio, int valore_minimo, int valore_massimo, int x, int y);
int calcolare_proporzione(int n_1, int d_1, int d_2);
int generare_numero_casuale(int minimo, int massimo);
#endif
