#ifndef GESTIRE_PARTITE_SALVATE_H_
#define GESTIRE_PARTITE_SALVATE_H_

#include "record_vettore_partite_salvate.h"
#include "record_partite_salvate.h"

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
#define NUMERO_MASSIMO_PARTITE_SALVATE //DA SCRIVERE 
#define FALSO 0
#define VERO 1

record_partite_salvate gestire_menu_partite_salvate(int scelta, record_partite_salvate salvataggi, int numero_partita, const char* menu_carica_partita);
record_partita leggere_partita_scelta(FILE* file_partite_salvate, int numero_partite);
FILE* salvare_partita(FILE* file_partite_salvate, record_partita partita);
int stampare_partite_salvate(FILE* file_partite_salvate); 
FILE* cancellare_partita_da_file(FILE* file_partite_salvate, int numero_partita);
record_vettore_partite_salvate rimuovere_partita_da_vettore(record_vettore_partite_salvate vettore_partite_salvate, int indice_elemento_da_rimuovere);

#endif /* GESTIRE_PARTITE_SALVATE_H_ */