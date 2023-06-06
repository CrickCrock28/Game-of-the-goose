/*
 * gestire_file.c
 *
 *  Created on: 6 giu 2023
 *      Author: pulpa
 */

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
