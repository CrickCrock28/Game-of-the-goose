#include "gestire_file.h"

int stampare_file_di_testo(const char* file_da_stampare){

    int i = PRIMO_INDICE_ARRAY;
    
    while(verificare_file_di_testo_terminato(file_da_stampare) == false){
        stampare_a_video(leggere_riga_file(file_da_stampare, i));
    }
}


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
