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

void stampare_file_di_testo(char* percorso_file) {

	FILE* file;
	char carattere;

	file = fopen(percorso_file, "r");
	while ((carattere = fgetc(file)) != EOF) {
	    printf("%c", carattere);
	}
	fclose(file);

	return;
}

int contare_righe_file_di_testo(char* percorso_file) {
	FILE* file;
	char carattere;
	int righe;

	file = fopen(percorso_file, "r");
	righe = 0;
	while ((carattere = fgetc(file)) != EOF) {
		if (carattere == '\n') {
			righe = righe + 1;
		}
	}
	fclose(file);

	return righe;
}
