#include "creare_nuova_partita.h"

record_dati_nuova_partita chiedere_dati_nuova_partita(record_dati_nuova_partita dati_nuova_partita) {
	int scelta, num_gioc, num_caselle;

	system("cls");
	scelta = chiedere_intero(MESSAGGIO_DATI_NUOVA_PARTITA, 1, 2);
	if (scelta == 1) {
		dati_nuova_partita = scrivere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_GIOCATORI);
		dati_nuova_partita = scrivere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita, NUMERO_PREDEFINITO_CASELLE);
	}
	else {
		num_gioc = chiedere_intero(MESSAGGIO_NUMERO_GIOCATORI, NUMERO_MINIMO_GIOCATORI, NUMERO_MASSIMO_GIOCATORI);
		num_caselle = chiedere_intero(MESSAGGIO_NUMERO_CASELLE, NUMERO_MINIMO_CASELLE, NUMERO_MASSIMO_CASELLE);

		dati_nuova_partita = scrivere_numero_giocatori_record_dati_nuova_partita(dati_nuova_partita, num_gioc);
		dati_nuova_partita = scrivere_numero_caselle_record_dati_nuova_partita(dati_nuova_partita, num_caselle);
	}
	return dati_nuova_partita;
}
record_partita creare_nuova_partita(record_dati_nuova_partita dati_nuova_partita) {
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
record_percorso inizializzare_percorso(record_percorso percorso) {
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
record_percorso inserire_caselle_oche(record_percorso percorso) {
	int i;

	i = FREQUENZA_OCA;
	while (i < leggere_dimensione_record_percorso(percorso)) {
		scrivere_casella_record_percorso(percorso, i, CASELLA_OCA);
		i = i + FREQUENZA_OCA;
	}
}
record_percorso inserire_casella_speciale(record_percorso percorso, int posizione_casella_speciale, char carattere_casella_speciale) {
	while (leggere_casella_record_percorso(*percorso, posizione_casella_speciale) != CASELLA_NORMALE) {
		posizione_casella_speciale = posizione_casella_speciale + 1;
	}
	scrivere_casella_record_percorso(percorso, posizione_casella_speciale, carattere_casella_speciale);
}
record_percorso inserire_caselle_speciali(record_percorso percorso) {
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
record_vet_giocatori inizializzare_record_vet_giocatori(record_vet_giocatori vet) {
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
