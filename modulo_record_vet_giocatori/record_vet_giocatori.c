#include "record_vet_giocatori.h"

int leggere_dimensione_record_vet_giocatori(record_vet_giocatori vet_giocatori) {
    int dimensione;
    dimensione = vet_giocatori.dimensione;
    return dimensione;
}

record_giocatore leggere_giocatore_record_vet_giocatori(record_vet_giocatori vet_giocatori, int indice) {
    record_giocatore giocatore;
    giocatore = vet_giocatori.giocatori[indice];
    return giocatore;
}

record_vet_giocatori scrivere_dimensione_record_vet_giocatori(record_vet_giocatori vet_giocatori, int nuova_dimensione) {
    vet_giocatori.dimensione = nuova_dimensione;
    return vet_giocatori;
}

record_vet_giocatori scrivere_giocatore_record_vet_giocatori(record_vet_giocatori vet_giocatori, int indice, record_giocatore nuovo_giocatore) {
    vet_giocatori.giocatori[indice] = nuovo_giocatore;
    return vet_giocatori;
}