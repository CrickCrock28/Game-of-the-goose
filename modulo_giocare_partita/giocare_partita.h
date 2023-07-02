#ifndef GIOCARE_PARTITA_H_
#define GIOCARE_PARTITA_H_

#include <stdbool.h>
#include "../modulo_gestire_azioni_semplici/gestire_azioni_semplici.h"
#include "../moduli_record/modulo_record_partita/record_partita.h"
#include "../moduli_record/modulo_record_giocatore/record_giocatore.h"
#include "../moduli_record/modulo_record_percorso/record_percorso.h"
#include "../moduli_record/modulo_record_vet_giocatori/record_vet_giocatori.h"
#include "../moduli_record/modulo_record_dati_nuova_partita/record_dati_nuova_partita.h"
#include "../modulo_gestire_file/gestire_file.h"
#include "../modulo_creare_nuova_partita/creare_nuova_partita.h"
#include "../modulo_gestire_partite_salvate/gestire_partite_salvate.h"
#include "../modulo_spostare_cursore/spostare_cursore.h"
#include "../costanti.h"

#define PERCORSO_FILE_MENU_PARTITA "..\\src\\file_di_gioco\\menu_partita.txt"
#define PERCORSO_FILE_TITOLO "..\\src\\file_di_gioco\\titolo.txt"
#define NUMERO_MASSIMO_CASELLE 90
#define CASELLA_OCA	'O'
#define CASELLA_PONTE 'T'
#define CASELLA_LOCANDA	'D'
#define TURNI_BLOCCATO_LOCANDA 3
#define CASELLA_POZZO 'Z'
#define CASELLA_LABIRINTO 'L'
#define CASELLA_SCHELETRO 'S'
#define CASELLA_PRIGIONE 'P'
#define CASELLA_FINE 'F'
#define CASELLA_NORMALE 'N'
#define ARRIVO_LABIRINTO 33
#define NUMERO_MASSIMO_GIOCATORI 4
#define PRIMO_INDICE_ARRAY 0
#define PRIMA_POSIZIONE_PERCORSO 1
#define NUMERO_MINIMO_DADO 1
#define NUMERO_MASSIMO_DADO 6
#define GIOCATORE_NON_STABILITO -1
#define POSIZIONE_GIOCATORE_NON_PARTECIPANTE -2

#define SCELTA_INIZIARE_NUOVA_PARTITA 1 // nomi troppo simili?????
#define SCELTA_TIRARE_I_DADI 1 // nomi troppo simili ?????
#define SCELTA_CREARE_NUOVA_PARTITA 2
#define SCELTA_SALVARE_PARTITA 3
#define SCELTA_ABBANDONARE_PARTITA 4

//costanti per la stampa
#define PRIMA_RIGA_TABELLONE "--------------------------------Gioco dell'oca------------------------------\0"
#define BORDO_LATERALE_CASELLA '|'
#define BORDO_INFERIORE_SUPERIORE_CASELLA "------\0"
#define SIMBOLO_GIOCATORE_1 '&'
#define SIMBOLO_GIOCATORE_2 '*'
#define SIMBOLO_GIOCATORE_3 '#'
#define SIMBOLO_GIOCATORE_4 '$'
#define INDICE_GIOCATORE_1 0
#define INDICE_GIOCATORE_2 1
#define INDICE_GIOCATORE_3 2
#define INDICE_GIOCATORE_4 3
#define NUMERO_CASELLE_PER_RIGA 15

char trovare_tipo_casella_giocatore(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_labirinto(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_scheletro(record_partita partita, int indice_giocatore);
record_partita giocare_partita(record_partita partita);
record_partita gestire_menu_partita(char* percorso_file_menu_partita, record_partita partita);
record_partita lanciare_primi_dadi(record_partita partita, int indice_giocatore);
void stampare_percorso(record_partita partita);
record_partita avanzare_turno(record_partita partita);
record_partita stabilire_primo_giocatore(record_partita partita);
record_partita applicare_effetto_casella_oca_ponte(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_pozzo_prigione(record_partita partita, int indice_giocatore, char tipo_casella);
record_partita applicare_effetto_casella_locanda(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_finale(record_partita partita, int indice_giocatore);
record_partita lanciare_dadi(record_partita partita, int indice_giocatore);
record_partita gestire_effetti_caselle_speciali(record_partita partita, int indice_giocatore);
record_partita gestire_scelta_partita(record_partita partita, int scelta);

#endif
