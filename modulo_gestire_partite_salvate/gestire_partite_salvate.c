#include <stdio.h>
#include <stdlib.h>
#include "funzioni_accesso_da_modificare.h"
#include "gestire_partite_salvate.h" 
#include "record_vettore_partite_salvate.h"
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
#define MASSIMO_PARTITE_SALVATE //DA SCRIVERE 
#define FALSO 0
#define VERO 1

//DA RIVEDERE
record_menu_partite_salvate gestire_menu_partite_salvate(int scelta, record_partite_salvate salvataggi, int numero_partita, const char* menu_carica_partita){
    int numero_partite_salvate;
    record_partita partita_scelta;
    FILE* file_partite_salvate;

    do{
        stampare_file_di_testo(menu_carica_partita);
        scelta = chiedere_intero(”Inserisci il numero corrispondente all’azione da eseguire: 0, 2, 8, 0);
        file_partite_salvate = leggere_file_partite_salvate(salvataggi);
        numero_partite_salvate = leggere_da_file_binario(file_partite_salvate);
        stampare_partite_salvate(file_partite_salvate);
        
        if(scelta = 1){
            numero_partita = chiedere_intero(”Inserisci il numero corrispondente alla partita da cancellare: ”, 0, 2, (numero_partite_salvate*2+1), 0);
            file_partite_salvate = cancellare_partita_da_file(file_partite_salvate, numero_partita);
            salvataggi = scrivere_partite_salvate(salvataggi, file_partite_salvate);
            }else{
            if(scelta = 2)
            numero_partita = chiedere_intero(”Inserisci il numero corrispondente alla partita da caricare: ”, 0, 2,  (numero_partite_salvate*2+1), 0);
            partita_scelta = leggere_partita_scelta(file_partite_salvate, numero_partita);
            salvataggi = scrivere_partite_salvate(salvataggi, file_partite_salvate);
            }
    }while(scelta != 0);
    return salvataggi;
}


//DA RIVEDERE
record_partita leggere_partita_scelta(FILE* file_partite_salvate, int numero_partite){
    int i;
    int numero_partite_salvate;
    record_vettore_partite_salvate vet_partite_salvate;
    record_partita partita_scelta;

    numero_partite_salvate = leggere_da_file_binario(file_partite_salvate);
    i = PRIMO_INDICE_ARRAY;
    while(i<=numero_partite_salvate){
    leggere_partita_record_vettore_partite_salvate(vet_partite_salvate, i) = leggere_da_file_binario(file_partite_salvate);
    i=i+1;
    }
    partita_scelta  = copiare_partita(partita_caricata, leggere_partita_record_vettore_partite_salvate(vet_partite_salvate, numero_partite_salvate);
    return partita_scelta;
}


FILE* salvare_partita(FILE* file_partite_salvate, record_partita partita){
    int numero_partite_salvate;
    int numero_partita_da_cancellare;
    numero_partite_salvate = leggere_da_file_binario(file_partite_salvate);

if(numero_partite_salvate == MASSIMO_PARTITE_SALVATE){
    stampare_partite_salvate(file_partite_salvate);
    numero_partita_da_cancellare = richiedere_intero(”Inserisci il numero della partita da cancellare per poter salvare la partita corrente (oppure 0 se non vuoi salvare): ”, 0, 5, (numero_partite_salvate*2+1), 0);
    if(numero_partita_da_cancellare != 0){
        file_partite_salvate = cancellare_partita_da_file(file_partite_salvate, numero_partita_da_cancellare);
        file_partite_salvate = accodare_a_file_binario(file_partite_salvate, partita);
        }else{
            file_partite_salvate = accodare_a_file_binario(file_partite_salvate, partita);
            }
    }
    return file_partite_salvate;
}


//DA RIVEDERE
int stampare_partite_salvate(FILE* file_partite_salvate){
    int i;
    int posizione_giocatore;
    int numero_partite_salvate;
    int numero_partita;
    int numero_giocatore;


    numero_partite_salvate = leggere_da_file_binario(file_partite_salvate);
    i = PRIMO_INDICE_ARRAY;
    
    while(i<=numero_partite_salvate){
        elemento di vet_partite_salvate in posizione i = leggere_da_file_binario(file_partite_salvate);
        i=i+1;
        }
        
    numero_partita = PRIMO_INDICE_ARRAY;
    
    while(numero_partita ≤ NUMERO_MASSIMO_PARTITE_SALVATE){
        stampare_a_video(”Partita “);
        stampare_a_video(numero_partita);
        stampare_a_video(”:\n”);
        stampare_a_video(”Dimensione del percorso: ”);
        stampare_a_video(leggere_dimensione_record_percorso(leggere_percorso_record_partita(elemento di vet_partite salvate in posizione numero_partita)));
        stampare_a_video(”\n”);
        numero_giocatore = PRIMO_INDICE_ARRAY;
        
        while(numero_giocatore <= NUMERO_MASSIMO_GIOCATORI){
            posizione_giocatore = leggere_posizione_giocatore_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita)));
            if(posizione_giocatore != POSIZIONE_GIOCATORE_NON_PARTECIPANTE){
                stampare_a_video(”Posizione giocatore “);
                stampare_a_video(numero_giocatore);
                stampare_a_video(”: ”);
                stampare_a_video(posizione_giocatore);
                stampare_a_video(”\n”);
                }
        numero_giocatore = numero_giocatore + 1;
        stampare_a_video(”\n”);
        numero_partita = numero_partita + 1;
        }
    } 
    return numero_partite_salvate;
}

//DA RIVEDERE 
FILE* cancellare_partita_da_file(FILE* file_partite_salvate, int numero_partita){
    int i;
    int numero_partite_salvate;

    numero_partite_salvate = leggere_da_file_binario(file_partite_salvate);
    i = PRIMO_INDICE_ARRAY;
    
    while(i<=numero_partite_salvate){
    elemento di vet_partite_salvate in posizione i = leggere_da_file_binario(file_partite_salvate);
    i=i+1;
    }
    
    vet_partite_salvate = rimuovere_partita_da_vettore(vet_partite_salvate, NUMERO_MASSIMO_PARTITE_SALVATE, numero_partita);
    i = PRIMO_INDICE_ARRAY;
    
    while(i<=numero_partite_salvate){
    scrivere_su_file_binario(partite_salvate, elemento di vet_partite_salvate in posizione i);
    i=i+1;
    }
    return file_partite_salvate;
}


record_vettore_partite_salvate rimuovere_partita_da_vettore(record_vettore_partite_salvate vettore_partite_salvate, int indice_elemento_da_rimuovere){
    int i;

    i = indice_elemento_da_rimuovere;
    while(i<=(leggere_dimensione_record_vettore_partite_salvate(vettore_partite_salvate)-1)){
        vettore_partite_salvate = scrivere_partita_record_vettore_partite_salvate(vettore_partite_salvate , leggere_partita_record_vettore_partite_salvate(vettore_partite_salvate, i+1), i);
        i = i + 1;
    }
    vettore_partite_salvate = scrivere_dimensione_record_vettore_partite_salvate(vettore_partite_salvate, leggere_dimensione_record_vettore_partite_salvate(vettore_partite_salvate)-1);
    return vettore_partite_salvate;
}