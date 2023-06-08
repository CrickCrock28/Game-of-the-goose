#include <record_dati_nuova_partita.h>

int leggere_numero_giocatori_record_dati_nuova_partita(record_dati_nuova_partita dati_nuova_partita) {
	int numero_giocatori;
	numero_giocatori = dati_nuova_partita.numero_giocatori;
	return numero_giocatori;
}
void scrivere_numero_giocatori_record_dati_nuova_partita(record_dati_nuova_partita* dati_nuova_partita, int numero_giocatori) {
	dati_nuova_partita->numero_giocatori = numero_giocatori;
	return;
}
int leggere_numero_caselle_record_dati_nuova_partita(record_dati_nuova_partita dati_nuova_partita) {
	int numero_caselle;
	numero_caselle = dati_nuova_partita.numero_caselle;
	return numero_caselle;
}
void scrivere_numero_caselle_record_dati_nuova_partita(record_dati_nuova_partita* dati_nuova_partita, int numero_caselle) {
	dati_nuova_partita->numero_caselle = numero_caselle;
	return;
}
