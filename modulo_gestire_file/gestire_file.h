#ifndef GESTIRE_FILE_H_
#define GESTIRE_FILE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define PRIMA_RIGA 0

int stampare_file_di_testo(char* percorso_file);
bool verificare_file_esistente(char* percorso_file);

#endif /* GESTIRE_FILE_H_ */