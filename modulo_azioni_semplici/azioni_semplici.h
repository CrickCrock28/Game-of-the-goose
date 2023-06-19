#ifndef AZIONI_SEMPLICI_H_
#define AZIONI_SEMPLICI_H_

#include <stdio.h>
#include "gotoxy.h"

#define NUMERO_COLONNA_MASSIMA 80
#define FINE_STRINGA '\0'

int chiedere_intero(const char* messaggio, int valore_minimo, int valore_massimo, int x, int y);

#endif
