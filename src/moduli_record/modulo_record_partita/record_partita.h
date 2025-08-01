#ifndef RECORD_PARTITA_H_
#define RECORD_PARTITA_H_

#include<stdbool.h>

#include "..\\..\\moduli_record\\modulo_record_percorso\\record_percorso.h"
#include "..\\..\\moduli_record\\modulo_record_vet_giocatori\\record_vet_giocatori.h"


typedef struct {
    record_percorso percorso;
    record_vet_giocatori vet_giocatori;
    int indice_giocatore_di_turno;
    int ultimo_lancio_dado_1;
    int ultimo_lancio_dado_2;
    bool nuova_partita;
    bool terminata;
} record_partita;


record_percorso leggere_percorso_record_partita(record_partita partita);
record_vet_giocatori leggere_vet_giocatori_record_partita(record_partita partita);
int leggere_indice_giocatore_di_turno_record_partita(record_partita partita);
bool leggere_terminata_record_partita(record_partita partita);
int leggere_ultimo_lancio_dado_1_record_partita(record_partita partita);
int leggere_ultimo_lancio_dado_2_record_partita(record_partita partita);
bool leggere_nuova_partita_record_partita(record_partita partita);
record_partita scrivere_percorso_record_partita(record_partita partita, record_percorso nuovo_percorso);
record_partita scrivere_vet_giocatori_record_partita(record_partita partita, record_vet_giocatori nuovo_vet_giocatori);
record_partita scrivere_indice_giocatore_di_turno_record_partita(record_partita partita, int nuovo_indice);
record_partita scrivere_terminata_record_partita(record_partita partita, int nuova_terminata);
record_partita scrivere_ultimo_lancio_dado_1_record_partita(record_partita partita, int nuovo_lancio);
record_partita scrivere_ultimo_lancio_dado_2_record_partita(record_partita partita, int nuovo_lancio);
record_partita scrivere_nuova_partita_record_partita(record_partita partita, int nuova_partita);

#endif /* RECORD_PARTITA */
