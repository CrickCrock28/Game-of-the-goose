#include "gestire_file.h"

#include <stdio.h>
#include <stdlib.h>


#include "..\\costanti.h"

#define MESSAGGIO_FILE_NON_TROVATO "Impossibile trovare il file: \0"


bool verificare_file_esistente(char* percorso_file) {
	bool file_esitente;
	FILE* file;

	file = fopen(percorso_file, "r");
	if (file != NULL) {
		file_esitente = true;
	}
	else {
		file_esitente = false;
	}
	fclose(file);
	
	return file_esitente;
}

bool verificare_esistenza_tutti_file() {

	bool tutti_i_file_esistono = true;

    if (!verificare_file_esistente(PERCORSO_FILE_MENU_NUOVA_PARTITA)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_NUOVA_PARTITA);
        tutti_i_file_esistono = false;
    }

    if (!verificare_file_esistente(PERCORSO_FILE_MENU_PRINCIPALE)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_PRINCIPALE);
        tutti_i_file_esistono = false;
    }

    if (!verificare_file_esistente(PERCORSO_FILE_MENU_PARTITA)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_PARTITA);
        tutti_i_file_esistono = false;
    }

    if (!verificare_file_esistente(PERCORSO_FILE_MENU_PARTITE_SALVATE)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_PARTITE_SALVATE);
        tutti_i_file_esistono = false;
    }

    if (!verificare_file_esistente(PERCORSO_FILE_MENU_AIUTO)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_AIUTO);
        tutti_i_file_esistono = false;
    }

    if (!verificare_file_esistente(PERCORSO_FILE_MENU_CLASSIFICA)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_CLASSIFICA);
        tutti_i_file_esistono = false;
    }

    if (!verificare_file_esistente(PERCORSO_FILE_REGOLE_GIOCO)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_REGOLE_GIOCO);
        tutti_i_file_esistono = false;
    }

    if (!verificare_file_esistente(PERCORSO_FILE_MANUALE_GIOCO)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MANUALE_GIOCO);
        tutti_i_file_esistono = false;
    }

    if (!verificare_file_esistente(PERCORSO_FILE_PARTITE_SALVATE)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_PARTITE_SALVATE);
        tutti_i_file_esistono = false;
    }

    if (!verificare_file_esistente(PERCORSO_FILE_CLASSIFICA)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_CLASSIFICA);
        tutti_i_file_esistono = false;
    }
    if (!verificare_file_esistente(PERCORSO_FILE_TITOLO)) {
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_TITOLO);
        tutti_i_file_esistono = false;
    }
    return tutti_i_file_esistono;
}


void stampare_file_di_testo(char* percorso_file) {

	FILE* file;
	char carattere;
	int riga = PRIMA_RIGA;

	file = fopen(percorso_file, "r");
	while ((carattere = fgetc(file)) != CARATTERE_FINE_FILE) {
	    printf("%c", carattere);
		if (carattere == '\n') {
			riga = riga + 1;
		}
	}
	fclose(file);

	return;
}
