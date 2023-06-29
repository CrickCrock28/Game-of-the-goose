#ifndef CREARE_NUOVA_PARTITA_H_
#define CREARE_NUOVA_PARTITA_H_

#include "../moduli_record/modulo_record_dati_nuova_partita/record_dati_nuova_partita.h"
#include "../moduli_record/modulo_record_percorso/record_percorso.h"
#include "../moduli_record/modulo_record_vet_giocatori/record_vet_giocatori.h"
#include "../moduli_record/modulo_record_partita/record_partita.h"
#include "../moduli_record/modulo_record_giocatore/record_giocatore.h"
#include "../modulo_giocare_partita/giocare_partita.h"

#define NUMERO_MASSIMO_GIOCATORI 4 // Numero massimo di giocatori
#define NUMERO_MINIMO_GIOCATORI	2 // Numero minimo di giocatori
#define NUMERO_MINIMO_CASELLE 50 // Numero minimo di caselle
#define NUMERO_MASSIMO_CASELLE 90 // Numero massimo di caselle
#define NUMERO_PREDEFINITO_GIOCATORI 2 // Numero di giocatori scelto dal programma per la nuova partita
#define NUMERO_PREDEFINITO_CASELLE 90 // Lunghezza del percorso scelto dal programma per la nuova partita
#define PRIMA_POSIZIONE_PERCORSO 1 // Prima posizione del percorso, cioè l’inizio
#define MASSIMO_TURNI_BLOCCATO 3 // Numero di turni massimo in cui il giocatore può rimanere bloccato
#define CASELLA_NORMALE	'N' // Indica la casella normale, cioè senza effetti particolari
#define CASELLA_OCA	'O' // Indica la casella oca
#define CASELLA_PONTE 'T' // Indica la casella ponte
#define CASELLA_LOCANDA 'D' // Indica la casella locanda
#define CASELLA_POZZO 'Z' // Indica la casella pozzo
#define CASELLA_LABIRINTO 'L' // Indica la casella labirinto
#define CASELLA_SCHELETRO 'S' // Indica la casella scheletro
#define CASELLA_PRIGIONE 'P' // Indica la casella prigione
#define CASELLA_FINE 'F' // Indica l'ultima casella del percorso, quella in cui si vince
#define CASELLA_VUOTA 'V' // Indica la casella vuota, cioè che non esiste praticamente nel percorso che vede il giocatore
#define FREQUENZA_OCA 9 // Indica ogni quante caselle ci sarà la casella oca
#define PONTE 6 // Posizione della casella ponte su percorso da 90 caselle
#define LOCANDA	19 // Posizione della casella locanda su percorso da 90 caselle
#define POZZO 31 // Posizione della casella pozzo su percorso da 90 caselle
#define LABIRINTO 42 // Posizione della casella labirinto su percorso da 90 caselle
#define ARRIVO_LABIRINTO 33 // Posizione in cui il giocatore deve spostarsi se arriva sulla casella labirinto (riferita al percorso da 90 caselle)
#define PRIGIONE 52 // Posizione della casella prigione su percorso da 90 caselle
#define SCHELETRO 58 // Posizione della casella scheletro su percorso da 90 caselle
#define GIOCATORE_NON_STABILITO	-1 // Indica che il giocatore di turno non è stato ancora stabilito
#define LANCIO_NON_EFFETTUATO -1 // Indica che non è stato ancora effettuato alcun lancio
#define POSIZIONE_GIOCATORE_NON_PARTECIPANTE -2 // Indica che il giocatore non sta giocando la partita
#define POSIZIONE_INIZIO (PRIMO_INDICE_ARRAY - 1) // Indica la posizione del giocatore all’inizio della partita
record_dati_nuova_partita chiedere_dati_nuova_partita(char* NOME_FILE_MENU_SCELTA_DATI_NUOVA_PARTITA);
record_partita creare_nuova_partita(record_dati_nuova_partita dati_nuova_partita);
record_percorso inizializzare_percorso(record_percorso percorso);
record_percorso inserire_caselle_oche(record_percorso percorso);
record_percorso inserire_casella_speciale(record_percorso percorso, int posizione_casella_speciale, char carattere_casella_speciale);
record_percorso inserire_caselle_speciali(record_percorso percorso);
record_vet_giocatori inizializzare_record_vet_giocatori(record_vet_giocatori vet);

#endif /* CREARE_NUOVA_PARTITA_H_ */
