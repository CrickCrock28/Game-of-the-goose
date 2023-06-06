#ifndef FUNZIONI_ACCESSO_DA_MODIFICARE_H
#define FUNZIONI_ACCESSO_DA_MODIFICARE_H

typedef struct {
    int posizione;
    int numero_turni_bloccato;
    int bloccato;
    int numero_dadi_lanciati;
} record_giocatore;

record_giocatore scrivere_posizione_record_giocatore(record_giocatore giocatore, int nuova_posizione);
record_giocatore scrivere_numero_turni_bloccato_record_giocatore(record_giocatore giocatore, int nuovo_numero_turni_bloccato);
record_giocatore scrivere_bloccato_record_giocatore(record_giocatore giocatore, int nuovo_bloccato);
record_giocatore scrivere_numero_dadi_lanciati_record_giocatore(record_giocatore giocatore, int nuovo_numero_dadi_lanciati);
int leggere_posizione_record_giocatore(record_giocatore giocatore);
int leggere_numero_turni_bloccato_record_giocatore(record_giocatore giocatore);
int leggere_bloccato_record_giocatore(record_giocatore giocatore);
int leggere_numero_dadi_lanciati_record_giocatore(record_giocatore giocatore);

//------------------------------------------------------------------------------------------------

#define NUMERO_GIOCATORI_MAX 4

typedef struct {
    int dimensione;
    record_giocatore giocatori[NUMERO_GIOCATORI_MAX];
} record_vet_giocatori;

int leggere_dimensione_record_vet_giocatori(record_vet_giocatori vet_giocatori);
record_giocatore leggere_giocatore_record_vet_giocatori(record_vet_giocatori vet_giocatori, int indice);
record_vet_giocatori scrivere_dimensione_record_vet_giocatori(record_vet_giocatori vet_giocatori, int nuova_dimensione);
record_vet_giocatori scrivere_giocatore_record_vet_giocatori(record_vet_giocatori vet_giocatori, int indice, record_giocatore nuovo_giocatore);
//-----------------------------------------------------------------------------------------

typedef struct {
    int dimensione;
    char caselle[90];
} record_percorso;

int leggere_dimensione_record_percorso(record_percorso percorso);
char leggere_casella_record_percorso(record_percorso percorso, int indice);
record_percorso scrivere_dimensione_record_percorso(record_percorso percorso, int nuova_dimensione);
record_percorso scrivere_casella_record_percorso(record_percorso percorso, int indice, char nuova_casella);

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

record_percorso leggere_percorso_record_partita(record_partita partita);
record_vet_giocatori leggere_vet_giocatori_record_partita(record_partita partita);
int leggere_indice_giocatore_di_turno_record_partita(record_partita partita);
int leggere_terminata_record_partita(record_partita partita);
int leggere_ultimo_lancio_dado_1_record_partita(record_partita partita);
int leggere_ultimo_lancio_dado_2_record_partita(record_partita partita);
int leggere_nuova_partita_record_partita(record_partita partita);
int leggere_abbandona_partita_record_partita(record_partita partita);
record_partita scrivere_percorso_record_partita(record_partita partita, record_percorso nuovo_percorso);
record_partita scrivere_vet_giocatori_record_partita(record_partita partita, record_vet_giocatori nuovo_vet_giocatori);
record_partita scrivere_indice_giocatore_di_turno_record_partita(record_partita partita, int nuovo_indice);
record_partita scrivere_terminata_record_partita(record_partita partita, int nuova_terminata);
record_partita scrivere_ultimo_lancio_dado_1_record_partita(record_partita partita, int nuovo_lancio);
record_partita scrivere_ultimo_lancio_dado_2_record_partita(record_partita partita, int nuovo_lancio);
record_partita scrivere_nuova_partita_record_partita(record_partita partita, int nuova_partita);
record_partita scrivere_abbandona_partita_record_partita(record_partita partita, int abbandona_partita);

//----------------------------------------------------------------------------

typedef struct record_dati_nuova_partita {
	int numero_giocatori;
	int numero_caselle;
} record_dati_nuova_partita;

int leggere_numero_giocatori_record_dati_nuova_partita(record_dati_nuova_partita dati_nuova_partita);
void scrivere_numero_giocatori_record_dati_nuova_partita(record_dati_nuova_partita* dati_nuova_partita, int numero_giocatori);
int leggere_numero_caselle_record_dati_nuova_partita(record_dati_nuova_partita dati_nuova_partita);
void scrivere_numero_caselle_record_dati_nuova_partita(record_dati_nuova_partita* dati_nuova_partita, int numero_caselle);

#endif