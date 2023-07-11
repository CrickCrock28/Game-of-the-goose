// PERFETTO
#include "creare_nuova_partita.h"

#include <stdbool.h>
#include <stdlib.h>

#include "..\\costanti.h"
#include "..\\percorsi_file.h"

#include "..\\modulo_gestire_file\\gestire_file.h"
#include "..\\modulo_gestire_azioni_semplici\\gestire_azioni_semplici.h"
#include "..\\modulo_spostare_cursore\\spostare_cursore.h"

#include "..\\moduli_record\\modulo_record_percorso\\record_percorso.h"
#include "..\\moduli_record\\modulo_record_vet_giocatori\\record_vet_giocatori.h"
#include "..\\moduli_record\\modulo_record_giocatore\\record_giocatore.h"
#include "..\\moduli_record\\modulo_record_dati_nuova_partita\\record_dati_nuova_partita.h"

#include "..\\modulo_giocare_partita\\giocare_partita.h"


#define MESSAGGIO_NUMERO_GIOCATORI "Inserisci il numero di giocatori (2 a 4): "
#define MESSAGGIO_NUMERO_CASELLE "Inserisci il numero di caselle (50 a 90): "

#define SCELTA_UTILIZZARE_DATI_PREDEFINITI 1
#define SCELTA_UTILIZZARE_DATI_PERSONALIZZATI 2

#define TIPO_CASELLA_VUOTA 'V'

#define FREQUENZA_OCA 9

#define POSIZIONE_PONTE_90_CASELLE 6
#define POSIZIONE_LOCANDA_90_CASELLE 19
#define POSIZIONE_POZZO_90_CASELLE 31
#define POSIZIONE_LABIRINTO_90_CASELLE 42
#define POSIZIONE_PRIGIONE_90_CASELLE 52
#define POSIZIONE_SCHELETRO_90_CASELLE 58

#define LANCIO_NON_EFFETTUATO -1


record_partita gestire_scelta_menu_nuova_partita(int scelta);
record_dati_nuova_partita chiedere_dati_nuova_partita(char* percorso_file_titolo, bool utilizzare_dati_predefiniti);
record_partita creare_nuova_partita(record_dati_nuova_partita dati_nuova_partita);
record_percorso inizializzare_percorso(record_percorso percorso);
record_percorso inserire_caselle_oche(record_percorso percorso);
record_percorso inserire_casella_speciale(record_percorso percorso, int posizione_casella_speciale, char carattere_casella_speciale);
record_percorso inserire_caselle_speciali(record_percorso percorso);
record_vet_giocatori inizializzare_record_vet_giocatori(record_vet_giocatori vet);


record_partita gestire_menu_nuova_partita(char* percorso_file_menu_nuova_partita){

	int scelta, riga;
    record_partita partita;

    do {
    	// Stampa il menu nuova partita
		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		stampare_file_di_testo(percorso_file_menu_nuova_partita);

		// Chiede all'utente quale azione eseguire
		riga = ottenere_riga_cursore();
		scelta = chiedere_intero(MESSAGGIO_SCELTA_AZIONE_MENU, SCELTA_USCIRE_DAL_MENU, SCELTA_UTILIZZARE_DATI_PERSONALIZZATI, riga, PRIMA_COORDINATA_SCHERMO);

		// Gestisce la scelta dell'utente
		partita = gestire_scelta_menu_nuova_partita(scelta);

		// Se all'interno del menu partita è stato scelto di abbandonare la partita
		if(leggere_terminata_record_partita(partita)){
			// Imposto scelta su SCELTA_USCIRE_DAL_MENU in modo da uscire dal menu e tornare al menu principale
			scelta = SCELTA_USCIRE_DAL_MENU;
		}

    } while(scelta != SCELTA_USCIRE_DAL_MENU &&
    		leggere_terminata_record_partita(partita) == false);

    return partita;
}

record_partita gestire_scelta_menu_nuova_partita(int scelta){

	record_partita partita;
	record_dati_nuova_partita dati_nuova_partita;

	// Se l'utente sceglie di usare i dati predefiniti
	if (scelta == SCELTA_UTILIZZARE_DATI_PREDEFINITI) {
		// Crea una partita utilizzando i dati predefiniti e iniziala
		dati_nuova_partita = chiedere_dati_nuova_partita(PERCORSO_FILE_TITOLO, true);
		partita = creare_nuova_partita(dati_nuova_partita);
		partita = giocare_partita(partita);

		// Altimenti, se l'utente scegie di utilizzare dati personalizzati
		} else {
			if (scelta == SCELTA_UTILIZZARE_DATI_PERSONALIZZATI) {
				// Chiedi i dati all'utente e con questi crea inizia una nuova partita
				dati_nuova_partita = chiedere_dati_nuova_partita(PERCORSO_FILE_TITOLO, false);
				partita = creare_nuova_partita(dati_nuova_partita);
				partita = giocare_partita(partita);
			}
		}

	return partita;
}

record_dati_nuova_partita chiedere_dati_nuova_partita(char* percorso_file_titolo, bool utilizzare_dati_predefiniti) {
	int numero_giocatori, numero_caselle, riga;
	record_dati_nuova_partita dati_nuova_partita;

	if(utilizzare_dati_predefiniti == true){

		// Salva i dati predefiniti per il numero dei giocatori e il numero di caselle in dati_nuova_partita
		dati_nuova_partita = scrivere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_GIOCATORI);
		dati_nuova_partita = scrivere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_CASELLE);

	} else {

		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		stampare_file_di_testo(percorso_file_titolo);
		riga = ottenere_riga_cursore();

		// Chiedi il numero di giocatori e di caselle all'utente
		numero_giocatori = chiedere_intero(MESSAGGIO_NUMERO_GIOCATORI, NUMERO_MINIMO_GIOCATORI, NUMERO_MASSIMO_GIOCATORI, riga, PRIMA_COORDINATA_SCHERMO);
		numero_caselle = chiedere_intero(MESSAGGIO_NUMERO_CASELLE, NUMERO_MINIMO_CASELLE, NUMERO_MASSIMO_CASELLE, (riga+1), PRIMA_COORDINATA_SCHERMO);

		// Salva i dati scelti dall'utente in dati_nuova_partita
		dati_nuova_partita = scrivere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita, numero_giocatori);
		dati_nuova_partita = scrivere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita, numero_caselle);

	}

	return dati_nuova_partita;
}

record_partita creare_nuova_partita(record_dati_nuova_partita dati_nuova_partita) {
	record_percorso percorso;
	record_vet_giocatori vet_gioc;
	record_partita partita;

	// Crea il percorso
	percorso = scrivere_dimensione_record_percorso(percorso, leggere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita));
	percorso = inizializzare_percorso(percorso);
	percorso = inserire_caselle_oche(percorso);
	percorso = inserire_caselle_speciali(percorso);

	// Crea il vettore contenente i giocatori
	vet_gioc = scrivere_dimensione_record_vet_giocatori(vet_gioc, leggere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita));
 	vet_gioc = inizializzare_record_vet_giocatori(vet_gioc);

 	// Salva il vettore contenente i giocatori e il percorso nella partita
	partita = scrivere_percorso_record_partita(partita, percorso);
	partita = scrivere_vet_giocatori_record_partita(partita, vet_gioc);

	// Scrive i dati della partita non scritti in precedenza
	partita = scrivere_indice_giocatore_di_turno_record_partita(partita, GIOCATORE_DI_TURNO_NON_STABILITO);
	partita = scrivere_terminata_record_partita(partita, false);
	partita = scrivere_ultimo_lancio_dado_1_record_partita(partita, LANCIO_NON_EFFETTUATO);
	partita = scrivere_ultimo_lancio_dado_2_record_partita(partita, LANCIO_NON_EFFETTUATO);
	partita = scrivere_nuova_partita_record_partita(partita, false);

	return partita;
}

record_percorso inizializzare_percorso(record_percorso percorso) {
	int i;

	i = PRIMO_INDICE_ARRAY;
	while (i < leggere_dimensione_record_percorso(percorso)) {
		percorso = scrivere_casella_record_percorso(percorso, i, TIPO_CASELLA_NORMALE);
		i = i + 1;
	}
	while (i < NUMERO_MASSIMO_CASELLE) {
		percorso = scrivere_casella_record_percorso(percorso, i, TIPO_CASELLA_VUOTA);
		i = i + 1;
	}

	return percorso;
}

record_percorso inserire_caselle_oche(record_percorso percorso) {
	int i;

	i = FREQUENZA_OCA - 1; // Viene decrementato di 1 poichè in c l'indice dell'n-sima casella è n-1
	while (i < leggere_dimensione_record_percorso(percorso)) {
		percorso = scrivere_casella_record_percorso(percorso, i, TIPO_CASELLA_OCA);
		i = i + FREQUENZA_OCA;
	}

	return percorso;
}

record_percorso inserire_casella_speciale(record_percorso percorso, int posizione_casella_speciale, char carattere_casella_speciale) {

	// Decremento la posizione perchè se la proporzione ha dato come risultato "n" l'elemento dell'array corrispondente in c è "n-1"
	posizione_casella_speciale--;

	// Incremento la posizione della casella fino a quando questa non coincide con ka posizione di una casella normale
	while (leggere_casella_record_percorso(percorso, posizione_casella_speciale) != TIPO_CASELLA_NORMALE) {
		posizione_casella_speciale++;
	}

	// Inserisco la casella all'interno del percorso
	percorso = scrivere_casella_record_percorso(percorso, posizione_casella_speciale, carattere_casella_speciale);

	return percorso;
}

record_percorso inserire_caselle_speciali(record_percorso percorso) {
	int posizione_ponte,
		posizione_locanda,
		posizione_pozzo,
		posizione_labirinto,
		posizione_prigione,
		posizione_scheletro;

	// Calcola, mediante una proporzione, le posizioni delle caselle in base alla dimensione del percorso e le inserisce all'interno di esso
	posizione_ponte = calcolare_proporzione(POSIZIONE_PONTE_90_CASELLE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_ponte, TIPO_CASELLA_PONTE);

	posizione_locanda = calcolare_proporzione(POSIZIONE_LOCANDA_90_CASELLE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_locanda, TIPO_CASELLA_LOCANDA);

	posizione_pozzo = calcolare_proporzione(POSIZIONE_POZZO_90_CASELLE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_pozzo, TIPO_CASELLA_POZZO);

	posizione_labirinto = calcolare_proporzione(POSIZIONE_LABIRINTO_90_CASELLE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_labirinto, TIPO_CASELLA_LABIRINTO);

	posizione_prigione = calcolare_proporzione(POSIZIONE_PRIGIONE_90_CASELLE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_prigione, TIPO_CASELLA_PRIGIONE);

	posizione_scheletro = calcolare_proporzione(POSIZIONE_SCHELETRO_90_CASELLE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_scheletro, TIPO_CASELLA_SCHELETRO);

	percorso = scrivere_casella_record_percorso(percorso, leggere_dimensione_record_percorso(percorso) - 1, TIPO_CASELLA_FINE);

	return percorso;
}

record_vet_giocatori inizializzare_record_vet_giocatori(record_vet_giocatori vet) {
	int i;
	record_giocatore giocatore;

	// Scorre tutti i giocatori
	i = PRIMO_INDICE_ARRAY;
	while (i < NUMERO_MASSIMO_GIOCATORI) {

		// Inizializza il giocatore
		if (i < leggere_dimensione_record_vet_giocatori(vet)) {
			giocatore = scrivere_posizione_record_giocatore(giocatore, POSIZIONE_INIZIO_PARTITA);
		}
		else {
			giocatore = scrivere_posizione_record_giocatore(giocatore, POSIZIONE_GIOCATORE_NON_PARTECIPANTE);
		}
		giocatore = scrivere_numero_turni_bloccato_record_giocatore(giocatore, NUMERO_TURNI_NON_BLOCCATO_LOCANDA);
		giocatore = scrivere_numero_dadi_lanciati_record_giocatore(giocatore, 0);
		giocatore = scrivere_bloccato_record_giocatore(giocatore, false);

		// Riscrive il giocatore nel vettore
		vet = scrivere_giocatore_record_vet_giocatori(vet, i, giocatore);

		i++;
	}
	return vet;
}
