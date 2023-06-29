#include "record_classificato.h"

void leggere_nome_giocatore_record_classificato(record_classificato classificato, char* nome){
    strcpy(nome, classificato.nome_giocatore);
    return;
}

record_classificato scrivere_nome_giocatore_record_classificato(record_classificato classificato, char* nome){
    strcpy(classificato.nome_giocatore, nome);
    return classificato;
}

int leggere_tiri_record_classificato(record_classificato classificato){
    int tiri;
    tiri = classificato.tiri;
    return tiri;
}

record_classificato scrivere_tiri_record_classificato(record_classificato classificato, int tiri){
    classificato.tiri = tiri;
    return classificato;
}
