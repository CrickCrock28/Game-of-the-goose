#ifndef RECORD_CLASSIFICATO_H
#define RECORD_CLASSIFICATO_H

typedef struct record_classificato{
	char nome_giocatore[LUNGHEZZA_NOME + 1];
	int tiri;
} record_classificato;

void leggere_nome_giocatore_record_classificato(record_classificato classificato,char* nome);
record_classificato scrivere_nome_giocatore_record_classificato(record_classificato classificato, char* nome);
int leggere_tiri_record_classificato(record_classificato classificato);
record_classificato scrivere_tiri_record_classificato(record_classificato classificato, int tiri);

#endif /* RECORD_CLASSIFICATO_H */
