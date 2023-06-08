#include "gestire_classifica.h"
#include "../modulo_gestire_file/gestire_file.h"
#include "../costanti.h"

void gestire_menu_classifica(char* NOME_FILE_MENU_CLASSIFICA,char* NOME_FILE_CLASSIFICA){
    int scelta;
    FILE* classifica, *menu_classifica;
    classifica = fopen(NOME_FILE_CLASSIFICA, "rb");
    menu_classifica = fopen(NOME_FILE_MENU_CLASSIFICA, "r");

    if(verificare_file_esistente(classifica) && verificare_file_esistente(menu_classifica)){
        do
        {
            stampare_file_di_testo(menu_classifica);
            scelta = chiedere_intero(MESSAGGIO_SCELTA, 0, 1, 7, 0);
            if(scelta = 1){
                stampare_classifica(classifica);
            }
        } while (scelta != 0);
    }
    return;
}

void aggiornare_classifica(char* NOME_FILE_CLASSIFICA, record_partita partita){
    record_classificato classificati[NUMERO_CLASSIFICATI];
    int dimensione = 0, i = 0;
    FILE* classifica;
    classifica = fopen(NOME_FILE_CLASSIFICA, "rb");
    if(verificare_file_esistente(classifica)){
        fread(&dimensione, sizeof(int), 1, fd);
        i = PRIMO_INDICE_ARRAY;
        while(i < dimensione){
            fread(&classificati[i], sizeof(int), 1, fd);
            i = i + 1;
        }
    }
}

void inserire_indice_classificati(record_classificato* classificati, int numero_classificati,record_classificato classificato, int indice_classificato){

}

int recuperare_tiri_classificato(record_partita partita){

}

void stampare_classifica(char* NOME_FILE_CLASSIFICA){

}

record_classificato inserire_record_classificato(record_classificato classificato_da_copiare, record_classificato classificato_da_inserire){

}

void stampare_giocatore_classificato(record_classificato giocatore_classificato){

}
