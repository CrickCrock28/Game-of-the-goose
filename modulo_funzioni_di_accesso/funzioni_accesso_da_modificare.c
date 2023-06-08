#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int posizione;
    int numero_turni_bloccato;
    int bloccato;
    int numero_dadi_lanciati;
} record_giocatore;

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

//------------------------------------------------------------------------------------------------

#define NUMERO_GIOCATORI_MAX 4
typedef struct {
    record_giocatore giocatori[NUMERO_GIOCATORI_MAX];
    int dimensione;
} record_vet_giocatori;

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

//-----------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------

typedef struct {
    record_percorso percorso;
    record_vet_giocatori vet_giocatori;
    int indice_giocatore_di_turno;
    int terminata;
    int ultimo_lancio_dado_1;
    int ultimo_lancio_dado_2;
    int nuova_partita;
    int abbandona_partita;
} record_partita;

record_percorso leggere_percorso_record_partita(record_partita partita) {
	record_percorso percorso;
    percorso = partita.percorso;
    return percorso;
}

record_vet_giocatori leggere_vet_giocatori_record_partita(record_partita partita) {
	record_vet_giocatori vet_giocatori;
	vet_giocatori = partita.vet_giocatori;
	return vet_giocatori;
}

int leggere_indice_giocatore_di_turno_record_partita(record_partita partita) {
    int indice_giocatore_di_turno;
	indice_giocatore_di_turno = partita.indice_giocatore_di_turno;
    return indice_giocatore_di_turno;
}

int leggere_terminata_record_partita(record_partita partita) {
    int terminata;
	terminata = partita.terminata;
    return terminata;
}

int leggere_ultimo_lancio_dado_1_record_partita(record_partita partita) {
    int ultimo_lancio_dado_1;
	ultimo_lancio_dado_1 = partita.ultimo_lancio_dado_1;
    return ultimo_lancio_dado_1;
}

int leggere_ultimo_lancio_dado_2_record_partita(record_partita partita) {
    int ultimo_lancio_dado_2;
	ultimo_lancio_dado_2 = partita.ultimo_lancio_dado_2;
    return ultimo_lancio_dado_2;
}

int leggere_nuova_partita_record_partita(record_partita partita) {
    int nuova_partita;
	nuova_partita = partita.nuova_partita;
    return nuova_partita;
}

int leggere_abbandona_partita_record_partita(record_partita partita) {
    int abbandona_partita;
	abbandona_partita = partita.abbandona_partita;
    return abbandona_partita;
}

record_partita scrivere_percorso_record_partita(record_partita partita, record_percorso nuovo_percorso) {
    partita.percorso = nuovo_percorso;
    return partita;
}

record_partita scrivere_vet_giocatori_record_partita(record_partita partita, record_vet_giocatori nuovo_vet_giocatori) {
    partita.vet_giocatori = nuovo_vet_giocatori;
    return partita;
}
record_partita scrivere_indice_giocatore_di_turno_record_partita(record_partita partita, int nuovo_indice) {
    partita.indice_giocatore_di_turno = nuovo_indice;
    return partita;
}

record_partita scrivere_terminata_record_partita(record_partita partita, int nuova_terminata) {
    partita.terminata = nuova_terminata;
    return partita;
}

record_partita scrivere_ultimo_lancio_dado_1_record_partita(record_partita partita, int nuovo_lancio) {
    partita.ultimo_lancio_dado_1 = nuovo_lancio;
    return partita;
}

record_partita scrivere_ultimo_lancio_dado_2_record_partita(record_partita partita, int nuovo_lancio) {
    partita.ultimo_lancio_dado_2 = nuovo_lancio;
    return partita;
}

record_partita scrivere_nuova_partita_record_partita(record_partita partita, int nuova_partita) {
    partita.nuova_partita = nuova_partita;
    return partita;
}

record_partita scrivere_abbandona_partita_record_partita(record_partita partita, int abbandona_partita) {
    partita.abbandona_partita = abbandona_partita;
    return partita;
}

//----------------------------------------------------------------------------

typedef struct record_dati_nuova_partita {
	int numero_giocatori;
	int numero_caselle;
} record_dati_nuova_partita;

int leggere_numero_giocatori_record_dati_nuova_partita(record_dati_nuova_partita dati_nuova_partita) {
	int numero_giocatori;
	numero_giocatori = dati_nuova_partita.numero_giocatori;
	return numero_giocatori;
}
void scrivere_numero_giocatori_record_dati_nuova_partita(record_dati_nuova_partita* dati_nuova_partita, int numero_giocatori) {
	dati_nuova_partita->numero_giocatori = numero_giocatori;
	return;
}
int leggere_numero_caselle_record_dati_nuova_partita(record_dati_nuova_partita dati_nuova_partita) {
	int numero_caselle;
	numero_caselle = dati_nuova_partita.numero_caselle;
	return numero_caselle;
}
void scrivere_numero_caselle_record_dati_nuova_partita(record_dati_nuova_partita* dati_nuova_partita, int numero_caselle) {
	dati_nuova_partita->numero_caselle = numero_caselle;
	return;
}

//----------------------------------------------------------------------------

#define NUMERO_PARTITE_MAX 5

typedef struct record_vettore_partite_salvate {
	record_partita partite[NUMERO_PARTITE_MAX];
	int dimensione;
} record_vettore_partite_salvate;

int leggere_dimensione_record_vettore_partite_salvate(record_vettore_partite_salvate vettore_partite_salvate){
        int dim= record_vettore_partite_salvate.dimensione;
        return dim;
}

record_vettore_partite_salvate scrivere_dimensione_record_vettore_partite_salvate(record_vettore_partite_salvate vettore_partite_salvate, int dim){
     dimensione.vettore_partite_salvate = dim;
     return vettore_partite_salvate;
}

record_partita leggere_partita_record_vettore_partite_salvate(record_vettore_partite_salvate vettore_partite_salvate, int indice){
        record_partita partita = vettore_partite_salvate.partite[indice];
        return partita;
}

record_vettore_partite_salvate scrivere_partita_record_vettore_partite_salvate(record_vettore_partite_salvate vettore_partite_salvate, record_partita partita, int indice){
        vettore_partite_salvate.partite[indice] = partita;
        return vettore_partite_salvate;
}

//----------------------------------------------------------------------------

typedef struct record_menu_partite_salvate{
    char fb*  menu_partita.txt;
    record_partita partita_opzionale;
} record_menu_partite_salvate;