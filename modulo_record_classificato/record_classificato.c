#include "record_classificato.h"

void leggere_nome_giocatore_record_classificato(record_classificato classificato, char* nome){
    copiare_stringa(nome, classificato.nome_giocatore);
    return;
}

record_classificato scrivere_nome_giocatore_record_classificato(record_classificato classificato, char* nome){
    copiare_stringa(classificato.nome_giocatore, nome);
    return;
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
