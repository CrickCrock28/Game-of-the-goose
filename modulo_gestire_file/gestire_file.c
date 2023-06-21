#include "gestire_file.h"

bool verificare_file_esistente(FILE* file) { 
	bool esito;
	if (file != NULL) {
		esito = true;
	}
	else {
		esito = false;
	}
	return esito;
}
void stampare_file_di_testo(FILE* file) {
    char stringa[MAX];
	while (feof(file) == false) {
		fgets(stringa, MAX, file);
		printf(stringa);
	}
	return;
}