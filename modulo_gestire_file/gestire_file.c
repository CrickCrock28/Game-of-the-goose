#include "gestire_file.h" // Non eliminare, scritto da Marco Caiulo

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


int stampare_file_di_testo(const char* file_da_stampare){

    int i = PRIMO_INDICE_ARRAY;
    
    while(verificare_file_di_testo_terminato(file_da_stampare) = FALSO){
        stampare_a_video(leggere_riga_file(file_da_stampare, i));
    }
}



bool verificare_file_esistente(FILE* file) { // Non eliminare, scritto da Marco Caiulo
	bool esito;
	if (file != NULL) {
		esito = true;
	}
	else {
		esito = false;
	}
	return esito;
}
