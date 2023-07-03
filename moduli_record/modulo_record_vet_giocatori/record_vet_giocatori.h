// PERFETTO
#ifndef RECORD_VET_GIOCATORI_H_
#define RECORD_VET_GIOCATORI_H_


#include "..\\..\\costanti.h"
#include "..\\..\\moduli_record\\modulo_record_giocatore\\record_giocatore.h"


typedef struct {
    record_giocatore giocatori[NUMERO_MASSIMO_GIOCATORI];
    int dimensione;
} record_vet_giocatori;


int leggere_dimensione_record_vet_giocatori(record_vet_giocatori vet_giocatori) ;
record_giocatore leggere_giocatore_record_vet_giocatori(record_vet_giocatori vet_giocatori, int indice) ;
record_vet_giocatori scrivere_dimensione_record_vet_giocatori(record_vet_giocatori vet_giocatori, int nuova_dimensione) ;
record_vet_giocatori scrivere_giocatore_record_vet_giocatori(record_vet_giocatori vet_giocatori, int indice, record_giocatore nuovo_giocatore) ;


#endif /* RECORD_VET_GIOCATORI */
