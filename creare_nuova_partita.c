#include "creare_nuova_partita.h"
#include "costanti.h"
#include <stdbool.h>

#define NUMERO_MINIMO_GIOCATORI	2 // Numero minimo di giocatori
#define NUMERO_MASSIMO_GIOCATORI 4 // Numero massimo di giocatori
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
#define POSIZIONE_GIOCATORE_NON_PARTECIPANTE -1 // Indica che il giocatore non sta giocando la partita
#define POSIZIONE_INIZIO (PRIMO_INDICE_ARRAY - 1) // Indica la posizione del giocatore all’inizio della partita
#define MESSAGGIO_DATI_NUOVA_PARTITA "Parametri di default (1) o li scegli tu (2): "
#define MESSAGGIO_NUMERO_GIOCATORI "Numero di giocatori"
#define MESSAGGIO_NUMERO_CASELLE "Numero di caselle"

void chiedere_dati_nuova_partita(record_dati_nuova_partita* dati_nuova_partita) {
	int scelta, num_gioc, num_caselle;

	system("cls");
	scelta = chiedere_intero(MESSAGGIO_DATI_NUOVA_PARTITA, 1, 2);
	if (scelta == 1) {
		scrivere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_GIOCATORI);
		scrivere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_CASELLE);
	}
	else {
		num_gioc = chiedere_intero(MESSAGGIO_NUMERO_GIOCATORI, NUMERO_MINIMO_GIOCATORI, NUMERO_MASSIMO_GIOCATORI);
		num_caselle = chiedere_intero(MESSAGGIO_NUMERO_CASELLE, NUMERO_MINIMO_CASELLE, NUMERO_MASSIMO_CASELLE);

		scrivere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita, num_gioc);
		scrivere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita, num_caselle);
	}
}
void creare_nuova_partita(record_dati_nuova_partita dati_nuova_partita, record_partita* partita) {
	record_percorso percorso;
	record_vet_giocatori vet_gioc;

	scrivere_dimensione_record_percorso(partita, leggere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita));
	inizializzare_percorso(&percorso);
	inserire_caselle_oche(&percorso);
	inserire_caselle_speciali(&percorso);

	scrivere_dimensione_record_vet_giocatori(&vet_gioc, leggere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita));
	inizializzare_record_vet_giocatori(&vet_gioc);

	scrivere_record_percorso_record_partita(partita, percorso);
	scrivere_record_vet_giocatori_record_partita(partita, vet_gioc);

	scrivere_indice_giocatore_di_turno_record_partita(partita, GIOCATORE_NON_STABILITO);
	scrivere_terminata_record_partita(partita, false);
	scrivere_ultimo_lancio_dado_1_record_partita(partita, LANCIO_NON_EFFETTUATO);
	scrivere_ultimo_lancio_dado_2_record_partita(partita, LANCIO_NON_EFFETTUATO);
	scrivere_nuova_partita_record_partita(partita, false);
	scrivere_abbandona_partita_record_partita(partita, false);
}
void inizializzare_percorso(record_percorso* percorso) {
	int i;

	i = PRIMO_INDICE_ARRAY;
	while (i < leggere_dimensione_record_percorso(*percorso)) {
		scrivere_casella_record_percorso(percorso, i, CASELLA_NORMALE);
		i = i + 1;
	}
	while (i < NUMERO_MASSIMO_CASELLE) {
		scrivere_casella_record_percorso(percorso, i, CASELLA_VUOTA);
		i = i + 1;
	}
}
void inserire_caselle_oche(record_percorso* percorso) {
	int i;

	i = FREQUENZA_OCA;
	while (i < leggere_dimensione_record_percorso(percorso)) {
		scrivere_casella_record_percorso(percorso, i, CASELLA_OCA);
		i = i + FREQUENZA_OCA;
	}
}
void inserire_casella_speciale(record_percorso* percorso, int posizione_casella_speciale, char carattere_casella_speciale) {
	while (leggere_casella_record_percorso(*percorso, posizione_casella_speciale) != CASELLA_NORMALE) {
		posizione_casella_speciale = posizione_casella_speciale + 1;
	}
	scrivere_casella_record_percorso(percorso, posizione_casella_speciale, carattere_casella_speciale);
}
void inserire_caselle_speciali(record_percorso* percorso) {
	int pos_ponte,
		pos_locanda,
		pos_pozzo,
		pos_labirinto,
		pos_prigione,
		pos_scheletro;

	pos_ponte = calcolare_proporzione(PONTE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(*percorso));
	inserire_casella_speciale(percorso, pos_ponte, CASELLA_PONTE);

	pos_locanda = calcolare_proporzione(LOCANDA, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(*percorso));
	inserirde_casella_speciale(percorso, pos_locanda, CASELLA_LOCANDA);

	pos_pozzo = calcolare_proporzione(POZZO, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(*percorso));
	inserire_casella_speciale(percorso, pos_pozzo, CASELLA_POZZO);

	pos_labirinto = calcolare_proporzione(LABIRINTO, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(*percorso));
	inserire_casella_speciale(percorso, pos_labirinto, CASELLA_LABIRINTO);

	pos_prigione = calcolare_proporzione(PRIGIONE, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(*percorso));
	inserire_casella_speciale(percorso, pos_prigione, CASELLA_PRIGIONE);

	pos_scheletro = calcolare_proporzione(SCHELETRO, NUMERO_MASSIMO_CASELLE, leggere_dimensione_record_percorso(*percorso));
	inserire_casella_speciale(percorso, pos_scheletro, CASELLA_SCHELETRO);

	scrivere_casella_record_percorso(percorso, leggere_dimensione_record_percorso(*percorso), CASELLA_FINE);
}
int calcolare_proporzione(int n_1, int d_1, int d_2) {
	int n_2, x;

	 x = n_1 * d_2 / d_1;
	 n_2 = (int) x;

	return n_2;
}
void inizializzare_record_vet_giocatori(record_vet_giocatori* vet) {
	int i;
	record_giocatore giocatore;

	i = PRIMO_INDICE_ARRAY;
	while (i < NUMERO_MASSIMO_GIOCATORI) {
		if (i < leggere_dimensione_record_vet_giocatori(*vet)) {
			scrivere_posizione_giocatore(giocatore, POSIZIONE_INIZIO);
		}
		else {
			scrivere_posizione_giocatore(giocatore, POSIZIONE_GIOCATORE_NON_PARTECIPANTE);
		}
		scrivere_numero_turni_bloccato_record_giocatore(giocatore, 0);
		scrivere_numero_dadi_lanciati_record_giocatore(giocatore, 0);
		scrivere_bloccato_record_giocatore(giocatore, false);
		scrivere_giocatore_vet_giocatori(vet, giocatore, i);
		i = i + 1;
	}
}
