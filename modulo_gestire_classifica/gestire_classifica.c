#include "gestire_classifica.h"

void gestire_menu_classifica(NOME_FILE_MENU_CLASSIFICA,NOME_FILE_CLASSIFICA){
    int azione_selezionata;
    if(verificare_file_esistente(NOME_FILE_MENU_AIUTO) && verificare_file_esistente(NOME_FILE_CLASSIFICA)){
        do
        {
            stampare_file_di_testo(NOME_FILE_MENU_AIUTO);
            azione_selezionata = chiedere_intero(MESSAGGIO_SCELTA, 0, 1, 7, 0);
            if(azione_selezionata = 1){
                stampare_classifica(NOME_FILE_CLASSIFICA)
            }
        } while (scelta != 0);
    }
    return;
}

void aggiornare_classifica(NOME_FILE_CLASSIFICA, record_partita partita){

}

void inserire_indice_classificati(record_classificato* classificati, int numero_classificati,record_classificato classificato, int indice_classificato){

}

int recuperare_tiri_classificato(record_partita partita){

}

void stampare_classifica(NOME_FILE_CLASSIFICA){

}

record_classificato inserire_record_classificato(record_classificato classificato_da_copiare, record_classificato classificato_da_inserire){

}

void stampare_giocatore_classificato(record_classificato giocatore_classificato){

}
