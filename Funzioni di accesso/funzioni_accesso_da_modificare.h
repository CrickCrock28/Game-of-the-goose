#ifndef FUNZIONI_ACCESSO_DA_MODIFICARE_H_
#define FUNZIONI_ACCESSO_DA_MODIFICARE_H_

typedef struct {
    int posizione;
    int numero_turni_bloccato;
    int bloccato;
    int numero_dadi_lanciati;
} struct_giocatore;

struct_giocatore scrivere_posizione_record_giocatore(struct_giocatore giocatore, int nuova_posizione);
struct_giocatore scrivere_numero_turni_bloccato_record_giocatore(struct_giocatore giocatore, int nuovo_numero_turni_bloccato);
struct_giocatore scrivere_bloccato_record_giocatore(struct_giocatore giocatore, int nuovo_bloccato);
struct_giocatore scrivere_numero_dadi_lanciati_record_giocatore(struct_giocatore giocatore, int nuovo_numero_dadi_lanciati);
int leggere_posizione_record_giocatore(struct_giocatore giocatore);
int leggere_numero_turni_bloccato_record_giocatore(struct_giocatore giocatore);
int leggere_bloccato_record_giocatore(struct_giocatore giocatore);
int leggere_numero_dadi_lanciati_record_giocatore(struct_giocatore giocatore);

//------------------------------------------------------------------------------------------------

#define NUMERO_GIOCATORI_MAX 4

typedef struct {
    int dimensione;
    struct_giocatore giocatori[NUMERO_GIOCATORI_MAX];
} struct_vet_giocatori;

int leggere_dimensione_record_vet_giocatori(struct_vet_giocatori vet_giocatori);
struct_giocatore leggere_giocatore_record_vet_giocatori(struct_vet_giocatori vet_giocatori, int indice);
struct_vet_giocatori scrivere_dimensione_record_vet_giocatori(struct_vet_giocatori vet_giocatori, int nuova_dimensione);
struct_vet_giocatori scrivere_giocatore_record_vet_giocatori(struct_vet_giocatori vet_giocatori, int indice, struct_giocatore nuovo_giocatore);
//-----------------------------------------------------------------------------------------

typedef struct {
    int dimensione;
    char caselle[];
} struct_percorso;

int leggere_dimensione_record_percorso(struct_percorso percorso);
char leggere_casella_record_percorso(struct_percorso percorso, int indice);
struct_percorso scrivere_dimensione_record_percorso(struct_percorso percorso, int nuova_dimensione);
struct_percorso scrivere_casella_record_percorso(struct_percorso percorso, int indice, char nuova_casella);

//----------------------------------------------------------------------------

typedef struct {
    struct_percorso percorso;
    struct_vet_giocatori vet_giocatori;
    int indice_giocatore_di_turno;
    int terminata;
    int ultimo_lancio_dado_1;
    int ultimo_lancio_dado_2;
    int nuova_partita;
    int abbandona_partita;
} struct_partita;

struct_percorso leggere_percorso_record_partita(struct_partita partita);
struct_vet_giocatori leggere_vet_giocatori_record_partita(struct_partita partita);
int leggere_indice_giocatore_di_turno_record_partita(struct_partita partita);
int leggere_terminata_record_partita(struct_partita partita);
int leggere_ultimo_lancio_dado_1_record_partita(struct_partita partita);
int leggere_ultimo_lancio_dado_2_record_partita(struct_partita partita);
int leggere_nuova_partita_record_partita(struct_partita partita);
int leggere_abbandona_partita_record_partita(struct_partita partita);
struct_partita scrivere_percorso_record_partita(struct_partita partita, struct_percorso nuovo_percorso);
struct_partita scrivere_vet_giocatori_record_partita(struct_partita partita, struct_vet_giocatori nuovo_vet_giocatori);
struct_partita scrivere_indice_giocatore_di_turno_record_partita(struct_partita partita, int nuovo_indice);
struct_partita scrivere_terminata_record_partita(struct_partita partita, int nuova_terminata);
struct_partita scrivere_ultimo_lancio_dado_1_record_partita(struct_partita partita, int nuovo_lancio);
struct_partita scrivere_ultimo_lancio_dado_2_record_partita(struct_partita partita, int nuovo_lancio);
struct_partita scrivere_nuova_partita_record_partita(struct_partita partita, int nuova_partita);
struct_partita scrivere_abbandona_partita_record_partita(struct_partita partita, int abbandona_partita);

#endif