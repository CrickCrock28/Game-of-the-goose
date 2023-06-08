#include <stdio.h>
#include <stdlib.h>
#include "funzioni_accesso_da_modificare.h"
#include "gotoxy.h"

//TUTTE LE COSTANTI SONO DA RIVEDERE
#define NUMERO_MINIMO_CASELLE 1
#define NUMERO_MASSIMO_CASELLE 100
#define CASELLA_OCA '9'
#define CASELLA_PONTE '6'
#define CASELLA_LOCANDA '19'
#define CASELLA_POZZO '31'
#define CASELLA_LABIRINTO '42'
#define CASELLA_SCHELETRO '58'
#define CASELLA_PRIGIONE '52'
#define CASELLA_FINALE '90'
#define ARRIVO_LABIRINTO 999
#define TURNI_BLOCCATO_LOCANDA 999
#define NUMERO_MASSIMO_GIOCATORI 4
#define PRIMO_INDICE_ARRAY 0
#define PRIMA_POSIZIONE_PERCORSO 1
#define PERCORSO_FILE_MENU_PARTITA "menu_partita.txt"
#define ARRIVO_PRIMO_LANCIO_4_5 2
#define ARRIVO_PRIMO_LANCIO_3_6 3
#define NUMERO_MINIMO_DADO 1
#define NUMERO_MASSIMO_DADO 6
#define FALSO 0
#define VERO 1

//DA RIVEDERE
record_menu_partite_salvate gestire_menu_partite_salvate(int scelta, record_menu_partite_salvate partite_salvate, int numero_partita, const char* menu_carica_partita){

    int numero_partite_salvate;
    record_partita partita_scelta;

    do{
        stampare_file_di_testo(menu_carica_partita);
        scelta = chiedere_intero(”Inserisci il numero corrispondente all’azione da eseguire: 0, 2, 8, 0);
        stampare_partite_salvate(partite_salvate);
        numero_partite_salvate = leggere_da_file_binario(partite_salvate);
        
        if(scelta = 1){
            numero_partita = chiedere_intero(”Inserisci il numero corrispondente alla partita da cancellare: ”, 0, 2, (numero_partite_salvate*2+1), 0);
            partite_salvate = cancellare_partita_da_file(partite_salvate, numero_partita);
            salvataggi = scrivere_partite_salvate(salvataggi, partite_salvate);
            }else{
            if(scelta = 2)
            numero_partita = chiedere_intero(”Inserisci il numero corrispondente alla partita da caricare: ”, 0, 2,  (numero_partite_salvate*2+1), 0);
            partita_scelta = leggere_partita_scelta(partite_salvate, numero_partita);
            salvataggi = scrivere_partite_salvate(salvataggi, partite_salvate);
            }
    }while(scelta != 0);
    return salvataggi;
}

//DA RIVEDERE
record_partita leggere_partita_scelta(int numero_partite){
    int i;
    int numero_partite_salvate;
    record_vettore_partite_salvate vet_partite_salvate;
    record_partita partita_scelta;

    numero_partite_salvate = leggere_da_file_binario(partite_salvate);
    i = PRIMO_INDICE_ARRAY;
    while(i<=numero_partite_salvate){
    leggere_partita_record_vettore_partite_salvate(vet_partite_salvate, i) = leggere_da_file_binario(partite_salvate);
    i=i+1;
    }
    partita_scelta  = copiare_partita(partita_caricata, leggere_partita_record_vettore_partite_salvate(vet_partite_salvate, numero_partite_salvate);
}