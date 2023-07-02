#include "creare_nuova_partita.h"
#include "../costanti.h"
#include "../modulo_gestire_azioni_semplici/gestire_azioni_semplici.h"
#include "../modulo_gestire_file/gestire_file.h"

#include <stdbool.h>
#include <stdlib.h>


#define SCELTA_UTILIZZARE_DATI_PREDEFINITI 1
#define SCELTA_UTILIZZARE_DATI_PERSONALIZZATI 2
#define SCELTA_USCIRE_DAL_MENU 0

record_partita gestire_menu_nuova_partita(char* percorso_file_menu_nuova_partita){

	int scelta, riga;
    record_partita partita;

    do {
		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		riga = stampare_file_di_testo(percorso_file_menu_nuova_partita);
		scelta = chiedere_intero(MESSAGGIO_SCELTA, SCELTA_USCIRE_DAL_MENU, SCELTA_DATI_SCELTI_UTENTE, (riga+1), PRIMA_COORDINATA_SCHERMO);

		partita = gestire_scelta_menu_nuova_partita(scelta);

		// Se all'interno del menu partita è stato scelto di abbandonare la partita
		if(leggere_abbandona_partita_record_partita(partita)){
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
	if (scelta == SCELTA_DATI_PREDEFINITI) {
		// Crea una partita utilizzando i dati predefiniti e iniziala
		dati_nuova_partita = chiedere_dati_nuova_partita(PERCORSO_FILE_TITOLO, true);
		partita = creare_nuova_partita(dati_nuova_partita);
		partita = giocare_partita(partita);

		// Altimenti, se l'utente scegie di utilizzare dati personalizzati
		} else {
			if (scelta == SCELTA_DATI_SCELTI_UTENTE) {
				// Chiedi i dati all'utente e con questi crea inizia una nuova partita
				dati_nuova_partita = chiedere_dati_nuova_partita(PERCORSO_FILE_TITOLO, false);
				partita = creare_nuova_partita(dati_nuova_partita);
				partita = giocare_partita(partita);
			} else{
				partita = scrivere_terminata_record_partita(partita, false);
			}
		}

	return partita;
}

record_dati_nuova_partita chiedere_dati_nuova_partita(char* percorso_file_titolo, bool utilizzare_dati_predefiniti) {
	int numero_giocatori, numero_caselle, riga;
	record_dati_nuova_partita dati_nuova_partita;

	if(utilizzare_dati_predefiniti){

		// Salva i dati predefiniti per il numero dei giocatori e il numero di caselle in dati_nuova_partita
		dati_nuova_partita = scrivere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_GIOCATORI);
		dati_nuova_partita = scrivere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_CASELLE);

	} else {

		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		riga = stampare_file_di_testo(percorso_file_titolo);

		// Chiedi il numero di giocatori e di caselle all'utente
		numero_giocatori = chiedere_intero(MESSAGGIO_NUMERO_GIOCATORI, NUMERO_MINIMO_GIOCATORI, NUMERO_MASSIMO_GIOCATORI, (riga+1), PRIMA_COORDINATA_SCHERMO);
		numero_caselle = chiedere_intero(MESSAGGIO_NUMERO_CASELLE, NUMERO_MINIMO_CASELLE, NUMERO_MASSIMO_CASELLE, (riga+2), PRIMA_COORDINATA_SCHERMO);

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

	percorso = scrivere_dimensione_record_percorso(percorso, leggere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita));
	percorso = inizializzare_percorso(percorso);
	percorso = inserire_caselle_oche(percorso);
	percorso = inserire_caselle_speciali(percorso);

	vet_gioc = scrivere_dimensione_record_vet_giocatori(vet_gioc, leggere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita));
 	vet_gioc = inizializzare_record_vet_giocatori(vet_gioc);

	partita = scrivere_percorso_record_partita(partita, percorso);
	partita = scrivere_vet_giocatori_record_partita(partita, vet_gioc);

	partita = scrivere_indice_giocatore_di_turno_record_partita(partita, GIOCATORE_NON_STABILITO);
	partita = scrivere_terminata_record_partita(partita, false);
	partita = scrivere_ultimo_lancio_dado_1_record_partita(partita, LANCIO_NON_EFFETTUATO);
	partita = scrivere_ultimo_lancio_dado_2_record_partita(partita, LANCIO_NON_EFFETTUATO);
	partita = scrivere_nuova_partita_record_partita(partita, false);
	partita = scrivere_abbandona_partita_record_partita(partita, false);
	partita = scrivere_salva_partita_record_partita(partita, false);

	return partita;
}

record_percorso inizializzare_percorso(record_percorso percorso) {
	int i;

	i = PRIMO_INDICE_ARRAY;
	while (i < leggere_dimensione_record_percorso(percorso)) {
		percorso = scrivere_casella_record_percorso(percorso, i, CASELLA_NORMALE);
		i = i + 1;
	}
	while (i < NUMERO_MASSIMO_CASELLE) {
		percorso = scrivere_casella_record_percorso(percorso, i, CASELLA_VUOTA);
		i = i + 1;
	}

	return percorso;
}

record_percorso inserire_caselle_oche(record_percorso percorso) {
	int i;

	i = FREQUENZA_OCA - 1; // Viene decrementato di 1 poichè in c l'indice dell'n-sima casella è n-1
	while (i < leggere_dimensione_record_percorso(percorso)) {
		percorso = scrivere_casella_record_percorso(percorso, i, CASELLA_OCA);
		i = i + FREQUENZA_OCA;
	}

	return percorso;
}

record_percorso inserire_casella_speciale(record_percorso percorso, int posizione_casella_speciale, char carattere_casella_speciale) {

	// Decremento la posizione perchè se la proporzione ha dato come risultato "n" l'elemento dell'array corrispondente in c è "n-1"
	posizione_casella_speciale--;

	// Incremento la posizione della casella fino a quando questa non coincide con ka posizione di una casella normale
	while (leggere_casella_record_percorso(percorso, posizione_casella_speciale) != CASELLA_NORMALE) {
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

	// Calcola, mediante una proporzione le posizioni delle caselle in base alla dimensione del percorso e le inserisce all'interno di esso
	posizione_ponte = calcolare_proporzione(PONTE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_ponte, CASELLA_PONTE);

	posizione_locanda = calcolare_proporzione(LOCANDA, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_locanda, CASELLA_LOCANDA);

	posizione_pozzo = calcolare_proporzione(POZZO, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_pozzo, CASELLA_POZZO);

	posizione_labirinto = calcolare_proporzione(LABIRINTO, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_labirinto, CASELLA_LABIRINTO);

	posizione_prigione = calcolare_proporzione(PRIGIONE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_prigione, CASELLA_PRIGIONE);

	posizione_scheletro = calcolare_proporzione(SCHELETRO, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, posizione_scheletro, CASELLA_SCHELETRO);

	percorso = scrivere_casella_record_percorso(percorso, leggere_dimensione_record_percorso(percorso) - 1, CASELLA_FINE);

	return percorso;
}

record_vet_giocatori inizializzare_record_vet_giocatori(record_vet_giocatori vet) {
	int i;
	record_giocatore giocatore;

	i = PRIMO_INDICE_ARRAY;
	while (i < NUMERO_MASSIMO_GIOCATORI) {
		if (i < leggere_dimensione_record_vet_giocatori(vet)) {
			giocatore = scrivere_posizione_record_giocatore(giocatore, POSIZIONE_INIZIO);
		}
		else {
			giocatore = scrivere_posizione_record_giocatore(giocatore, POSIZIONE_GIOCATORE_NON_PARTECIPANTE);
		}
		giocatore = scrivere_numero_turni_bloccato_record_giocatore(giocatore, 0);
		giocatore = scrivere_numero_dadi_lanciati_record_giocatore(giocatore, 0);
		giocatore = scrivere_bloccato_record_giocatore(giocatore, false);
		vet = scrivere_giocatore_record_vet_giocatori(vet, i, giocatore);
		i++;
	}
	return vet;
}
