#ifndef RECORD_PERCORSO_H_
#define RECORD_PERCORSO_H_

#include "..\\..\\costanti.h"

typedef struct {
    int dimensione;
    char caselle[NUMERO_MASSIMO_CASELLE];
} record_percorso;

int leggere_dimensione_record_percorso(record_percorso percorso);
char leggere_casella_record_percorso(record_percorso percorso, int indice);
record_percorso scrivere_dimensione_record_percorso(record_percorso percorso, int nuova_dimensione);
record_percorso scrivere_casella_record_percorso(record_percorso percorso, int indice, char nuova_casella);
void copiare_caselle_percorso(record_percorso percorso, char* caselle);

#endif /* RECORD_PERCORSO */
