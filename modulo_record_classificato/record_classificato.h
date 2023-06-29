#ifndef RECORD_CLASSIFICATO_H
#define RECORD_CLASSIFICATO_H

#include<string.h>

#include "../costanti.h"

typedef struct record_classificato {
	char nome_giocatore[LUNGHEZZA_NOME + 1]; // Nome del giocatore classificato
	int tiri; // Numero di tiri del giocatore classificato
} record_classificato;

// Legge il nome del giocatore classificato
void leggere_nome_giocatore_record_classificato(record_classificato classificato, char* nome);
// Inserisce il nome del giocatore classificato
record_classificato scrivere_nome_giocatore_record_classificato(record_classificato classificato, char* nome);
// Legge il numero di tiri del giocatore classificato
int leggere_tiri_record_classificato(record_classificato classificato);
// Inserisce il numero di tiri del giocatore classificato
record_classificato scrivere_tiri_record_classificato(record_classificato classificato, int tiri);

#endif /* RECORD_CLASSIFICATO_H */
