#ifndef GIOCARE_PARTITA_H
#define GIOCARE_PARTITA_H

#include <stdbool.h>
#include "giocare_partita.h"
#include "funzioni_accesso_da_modificare.h"
#include "gotoxy.h"

#define PERCORSO_FILE_MENU_PARTITA "menu_partita.txt" //DA RIVEDEREEEEEEEE
#define NUMERO_MASSIMO_CASELLE 90
#define CASELLA_OCA	'O'
#define CASELLA_PONTE 'T'
#define CASELLA_LOCANDA	'D'
#define CASELLA_POZZO 'Z'
#define CASELLA_LABIRINTO 'L'
#define CASELLA_SCHELETRO 'S'
#define CASELLA_PRIGIONE 'P'
#define CASELLA_FINE 'F'
#define ARRIVO_LABIRINTO 33
#define TURNI_BLOCCATO_LOCANDA 999 //DA RIVEDEREEEEEEEE
#define NUMERO_MASSIMO_GIOCATORI 4
#define PRIMO_INDICE_ARRAY 0
#define PRIMA_POSIZIONE_PERCORSO 1
#define ARRIVO_PRIMO_LANCIO_4_5 53
#define ARRIVO_PRIMO_LANCIO_3_6 26
#define NUMERO_MINIMO_DADO 1
#define NUMERO_MASSIMO_DADO 6

char tipo_casella(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_labirinto(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_prigione(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_scheletro(record_partita partita, int indice_giocatore);
record_partita giocare_partita(record_partita partita);
record_partita lanciare_primi_dadi(record_partita partita, int indice_giocatore);
void stampare_percorso(char* caselle, int dimensione, int posizione_giocatore_1, int posizione_giocatore_2, int posizione_giocatore_3, int posizione_giocatore_4);
record_partita avanzare_turno(record_partita partita);
record_partita stabilire_primo_giocatore(record_partita partita);
record_partita gestire_menu_nuova_partita(const char* menu_nuova_partita, const char* menu_partita_in_corso, int riprendere_partita);
record_partita applicare_effetto_casella_oca_ponte(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_pozzo(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_locanda(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_finale(record_partita partita, int indice_giocatore);
record_partita lanciare_dadi(record_partita partita, int indice_giocatore);
int calcolare_resto(int dividendo, int divisore);
record_partita gestire_effetti_caselle_speciali(record_partita partita, int indice_giocatore);
record_partita gestire_scelta_partita(record_partita partita, int scelta);
record_partita gestire_scelta_partita(int scelta);

#endif