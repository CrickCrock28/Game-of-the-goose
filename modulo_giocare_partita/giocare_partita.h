#ifndef GIOCARE_PARTITA_H_
#define GIOCARE_PARTITA_H_

#include <stdbool.h>
#include "../modulo_gestire_azioni_semplici/gestire_azioni_semplici.h"
#include "../modulo_record_partita/record_partita.h"
#include "../modulo_record_giocatore/record_giocatore.h"
#include "../modulo_record_percorso/record_percorso.h"
#include "../modulo_record_vet_giocatori/record_vet_giocatori.h"
#include "../modulo_record_dati_nuova_partita/record_dati_nuova_partita.h"
#include "../modulo_gestire_file/gestire_file.h"
#include "../spostare_cursore.h"

#define PERCORSO_FILE_MENU_PARTITA "menu_partita.txt"
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
#define NUMERO_MASSIMO_GIOCATORI 4
#define PRIMO_INDICE_ARRAY 0
#define PRIMA_POSIZIONE_PERCORSO 1
#define ARRIVO_PRIMO_LANCIO_4_5 53
#define ARRIVO_PRIMO_LANCIO_3_6 26
#define NUMERO_MINIMO_DADO 1
#define NUMERO_MASSIMO_DADO 6
#define GIOCATORE_NON_STABILITO -1

char trovare_tipo_casella_giocatore(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_labirinto(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_prigione(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_scheletro(record_partita partita, int indice_giocatore);
record_partita giocare_partita(record_partita partita);
record_partita lanciare_primi_dadi(record_partita partita, int indice_giocatore);
void stampare_percorso(char* caselle, int dimensione, int posizione_giocatore_1, int posizione_giocatore_2, int posizione_giocatore_3, int posizione_giocatore_4);
record_partita avanzare_turno(record_partita partita);
record_partita stabilire_primo_giocatore(record_partita partita);
record_partita gestire_menu_nuova_partita(char* NOME_FILE_MENU_NUOVA_PARTITA, int riprendere_partita);
record_partita applicare_effetto_casella_oca_ponte(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_pozzo(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_locanda(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_finale(record_partita partita, int indice_giocatore);
record_partita lanciare_dadi(record_partita partita, int indice_giocatore);
int calcolare_resto(int dividendo, int divisore);
record_partita gestire_effetti_caselle_speciali(record_partita partita, int indice_giocatore);
record_partita gestire_scelta_partita(record_partita partita, int scelta);
record_partita gestire_scelta_nuova_partita(int scelta);

#endif