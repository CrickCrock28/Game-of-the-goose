#include "record_giocatore.h"

record_giocatore scrivere_posizione_record_giocatore(record_giocatore giocatore, int nuova_posizione) {
    giocatore.posizione = nuova_posizione;
    return giocatore;
}

record_giocatore scrivere_numero_turni_bloccato_record_giocatore(record_giocatore giocatore, int nuovo_numero_turni_bloccato) {
    giocatore.numero_turni_bloccato = nuovo_numero_turni_bloccato;
    return giocatore;
}

record_giocatore scrivere_bloccato_record_giocatore(record_giocatore giocatore, int nuovo_bloccato) {
    giocatore.bloccato = nuovo_bloccato;
    return giocatore;
}

record_giocatore scrivere_numero_dadi_lanciati_record_giocatore(record_giocatore giocatore, int nuovo_numero_dadi_lanciati) {
    giocatore.numero_dadi_lanciati = nuovo_numero_dadi_lanciati;
    return giocatore;
}

int leggere_posizione_record_giocatore(record_giocatore giocatore) {
    int posizione;
    posizione = giocatore.posizione;
    return posizione;
}

int leggere_numero_turni_bloccato_record_giocatore(record_giocatore giocatore) {
    int numero_turni_bloccato;
    numero_turni_bloccato = giocatore.numero_turni_bloccato;
    return numero_turni_bloccato;
}

int leggere_bloccato_record_giocatore(record_giocatore giocatore) {
    int bloccato;
    bloccato = giocatore.bloccato;
    return bloccato;
}

int leggere_numero_dadi_lanciati_record_giocatore(record_giocatore giocatore) {
    int numero_dadi_lanciati;
    numero_dadi_lanciati = giocatore.numero_dadi_lanciati;
    return numero_dadi_lanciati;
}