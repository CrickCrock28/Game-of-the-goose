#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dimensione;
    char caselle[90];
} record_percorso;

int leggere_dimensione_record_percorso(record_percorso percorso) {
    int dimensione;
    dimensione = percorso.dimensione;
    return dimensione;
}

char leggere_casella_record_percorso(record_percorso percorso, int indice) {
    char casella;
    casella = percorso.caselle[indice];
    return casella;
}

record_percorso scrivere_dimensione_record_percorso(record_percorso percorso, int nuova_dimensione) {
    percorso.dimensione = nuova_dimensione;
    return percorso;
}

record_percorso scrivere_casella_record_percorso(record_percorso percorso, int indice, char nuova_casella) {
    percorso.caselle[indice] = nuova_casella;
    return percorso;
}