#include "record_partita.h"
#include "record_percorso.h"
#include "record_vet_giocatori.h"

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