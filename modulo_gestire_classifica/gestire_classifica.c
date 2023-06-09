#include <stdbool.h>
#include <stdio.h>
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

void aggiornare_classifica(char* NOME_FILE_CLASSIFICA, record_partita partita, char* MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO, int NUMERO_MASSIMO_CLASSIFICATI){
    record_classificato classificati[NUMERO_MASSIMO_CLASSIFICATI], classificato;
    int dimensione = 0,//numero di giocatori classificati
        i = 0,//contatore dei giocatori classificati
        tiri,//numero di tiri del giocatore da classificare
        posizione;//posizione del nuovo giocatore nella classifica
    FILE* classifica;//puntatore al file della classifica
    char nome[LUNGHEZZA_NOME + 1];//nome del giocatore che si deve registrare
    classifica = fopen(NOME_FILE_CLASSIFICA, "rb");
    if(verificare_file_esistente(classifica)){
        fread(&dimensione, sizeof(int), 1, classifica);
        fread(classificati, sizeof(record_classificato), dimensione, classifica);
        tiri=recuperare_tiri_classificato(partita);
        posizione = trovare_posizione_classificato(classificati, tiri, dimensione, NUMERO_MASSIMO_CLASSIFICATI);
        if(posizione != -1){
            printf("%s", MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO);
            scanf("%s", nome);
            classificato = scrivere_nome_record_classificato(classificato, nome);
            classificato = scrivere_tiri_record_classificato(classificato, tiri);
            inserire_indice_classificati(classificati, dimensione, classificato, posizione, NUMERO_MASSIMO_CLASSIFICATI);
            dimensione = aggiornare_dimensione(dimensione, NUMERO_MASSIMO_CLASSIFICATI);
            fwrite(&dimensione, sizeof(int), 1, classifica);
            fwrite(classificati, sizeof(record_classificato), dimensione, classifica);
        }
    }
}

int trovare_posizione_classificato(record_classificato* classificati, int tiri, int dimensione, int NUMERO_MASSIMO_CLASSIFICATI){
    bool posizione_trovata = false;
    int posizione = PRIMO_INDICE_ARRAY;
    while(posizione < dimensione && posizione_trovata == false){
        if(tiri > leggere_tiri_record_classificato(classificati[posizione])){
            posizione = posizione + 1;
        } else {
            posizione_trovata = true;
        }
    }
    if(posizione == NUMERO_MASSIMO_CLASSIFICATI){
        posizione = -1;
    }
    return posizione;
}

int aggiornare_dimensione(int dimensione,int NUMERO_MASSIMO_CLASSIFICATI){
    if(dimensione < NUMERO_MASSIMO_CLASSIFICATI - 1){
        dimensione = dimensione + 1;
    }
    return dimensione;
}

void inserire_indice_classificati(record_classificato* classificati, int numero_classificati,record_classificato classificato, int indice_classificato, int NUMERO_MASSIMO_CLASSIFICATI){
    
}

int recuperare_tiri_classificato(record_partita partita){

}

void stampare_classifica(char* NOME_FILE_CLASSIFICA){

}

record_classificato inserire_record_classificato(record_classificato classificato_da_copiare, record_classificato classificato_da_inserire){

}

void stampare_giocatore_classificato(record_classificato giocatore_classificato){

}
