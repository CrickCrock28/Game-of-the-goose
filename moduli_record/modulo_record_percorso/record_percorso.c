#include "record_percorso.h"

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

void copiare_caselle_percorso(record_percorso percorso, char* caselle){
	memcpy(caselle, percorso.caselle, DIMENSIONE_MASSIMA_PERCORSO*sizeof(char));
	return;
}
