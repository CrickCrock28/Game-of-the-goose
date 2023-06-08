#include <gestire_file.h>

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
