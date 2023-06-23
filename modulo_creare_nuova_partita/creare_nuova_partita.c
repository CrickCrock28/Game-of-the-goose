#include "creare_nuova_partita.h"
#include "../costanti.h"
#include "../modulo_gestire_azioni_semplici/gestire_azioni_semplici.h"
#include "../modulo_gestire_file/gestire_file.h"
#include <stdbool.h>
#include <stdlib.h>

#define DATI_PREDEFINITI 1 // Indica l'opzione di menu corrispondente ad usare i dati predefiniti del programma per la nuova partita
#define DATI_SCELTI_UTENTE 2 // Indica l'opzione di menu corrispondente a permettere all'utente di scegliere i dati per la nuova partita
#define MESSAGGIO_NUMERO_GIOCATORI "Inserisci il numero di giocatori (2 a 4): \0" // Messaggio da stampare al momento dell’inserimento del numero di giocatori della nuova partita
#define MESSAGGIO_NUMERO_CASELLE "Inserisci il numero di caselle (50 a 90): \0" // Messaggio da stampare al momento dell’inserimento del numero di caselle della nuova partita

// spostami
void stampare_titolo(void) {
	puts(TITOLO);
	puts(BORDO);

	return;
}

record_dati_nuova_partita chiedere_dati_nuova_partita(char* NOME_FILE_MENU_SCELTA_DATI_NUOVA_PARTITA) {
	int scelta, num_gioc, num_caselle;
	record_dati_nuova_partita dati_nuova_partita;
	FILE* menu_scelta_dati_nuova_partita;

	menu_scelta_dati_nuova_partita = fopen(NOME_FILE_MENU_SCELTA_DATI_NUOVA_PARTITA, "r");
	system("cls");
	if (verificare_file_esistente(menu_scelta_dati_nuova_partita) == true) {
		stampare_file_di_testo(menu_scelta_dati_nuova_partita);
		scelta = chiedere_intero(MESSAGGIO_SCELTA, 0, 2, 6, 0);
		if (scelta == DATI_PREDEFINITI) {
			dati_nuova_partita = scrivere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_GIOCATORI);
			dati_nuova_partita = scrivere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_CASELLE);
		}
		else if (scelta == DATI_SCELTI_UTENTE) {
			system("cls");
			stampare_titolo();
			num_gioc = chiedere_intero(MESSAGGIO_NUMERO_GIOCATORI, NUMERO_MINIMO_GIOCATORI, NUMERO_MASSIMO_GIOCATORI, 2, 0);
			system("cls");
			stampare_titolo();
			num_caselle = chiedere_intero(MESSAGGIO_NUMERO_CASELLE, NUMERO_MINIMO_CASELLE, NUMERO_MASSIMO_CASELLE, 2, 0);

			dati_nuova_partita = scrivere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita, num_gioc);
			dati_nuova_partita = scrivere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita, num_caselle);
		}
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

	i = FREQUENZA_OCA - 1;
	while (i < leggere_dimensione_record_percorso(percorso)) {
		percorso = scrivere_casella_record_percorso(percorso, i, CASELLA_OCA);
		i = i + FREQUENZA_OCA;
	}

	return percorso;
}
record_percorso inserire_casella_speciale(record_percorso percorso, int posizione_casella_speciale, char carattere_casella_speciale) {
	while (leggere_casella_record_percorso(percorso, posizione_casella_speciale) != CASELLA_NORMALE) {
		posizione_casella_speciale = posizione_casella_speciale + 1;
	}
	percorso = scrivere_casella_record_percorso(percorso, posizione_casella_speciale, carattere_casella_speciale);

	return percorso;
}
record_percorso inserire_caselle_speciali(record_percorso percorso) {
	int pos_ponte,
		pos_locanda,
		pos_pozzo,
		pos_labirinto,
		pos_prigione,
		pos_scheletro;

	pos_ponte = calcolare_proporzione(PONTE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, pos_ponte, CASELLA_PONTE);

	pos_locanda = calcolare_proporzione(LOCANDA, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, pos_locanda, CASELLA_LOCANDA);

	pos_pozzo = calcolare_proporzione(POZZO, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, pos_pozzo, CASELLA_POZZO);

	pos_labirinto = calcolare_proporzione(LABIRINTO, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, pos_labirinto, CASELLA_LABIRINTO);

	pos_prigione = calcolare_proporzione(PRIGIONE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, pos_prigione, CASELLA_PRIGIONE);

	pos_scheletro = calcolare_proporzione(SCHELETRO, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(percorso));
	percorso = inserire_casella_speciale(percorso, pos_scheletro, CASELLA_SCHELETRO);

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
		i = i + 1;
	}

	return vet;
}
