#include "gestire_file.h"

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

int stampare_file_di_testo(char* percorso_file) {

	FILE* file;
	char carattere;
	int riga = PRIMA_RIGA;

	file = fopen(percorso_file, "r");
	while ((carattere = fgetc(file)) != CARATTERE_FINE_FILE) {
	    printf("%c", carattere);
		if(carattere == '\n') {
			riga = riga + 1;
		}
	}
	fclose(file);

	return riga;
}

int contare_righe_file_di_testo(char* percorso_file) {
	FILE* file;
	char carattere;
	int righe;

	file = fopen(percorso_file, "r");
	righe = 0;
	while ((carattere = fgetc(file)) != CARATTERE_FINE_FILE) {
		if (carattere == '\n') {
			righe = righe + 1;
		}
	}
	fclose(file);

	return righe;
}
