#ifndef CREARE_NUOVA_PARTITA_H_
#define CREARE_NUOVA_PARTITA_H_

#include "record_dati_nuova_partita.h"
#define NUMERO_MASSIMO_GIOCATORI 4 // Numero massimo di giocatori

void chiedere_dati_nuova_partita(record_dati_nuova_partita* dati_nuova_partita);
void creare_nuova_partita(record_dati_nuova_partita dati_nuova_partita, record_partita* partita);
void inizializzare_percorso(record_percorso* percorso);
void inserire_caselle_oche(record_percorso* percorso);
void inserire_casella_speciale(record_percorso* percorso, int posizione_casella_speciale, char carattere_casella_speciale);
void inserire_caselle_speciali(record_percorso* percorso);
int calcolare_proporzione(int n_1, int d_1, int d_2);
void inizializzare_record_vet_giocatori(record_vet_giocatori* vet);


#endif /* CREARE_NUOVA_PARTITA_H_ */
