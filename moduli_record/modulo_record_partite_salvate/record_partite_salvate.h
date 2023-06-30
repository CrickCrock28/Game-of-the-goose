#ifndef RECORD_PARTITE_SALVATE_H_
#define RECORD_PARTITE_SALVATE_H_

#include "../../moduli_record/modulo_record_partita/record_partita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIMENSIONE_PERCORSO_FILE 30

typedef struct record_partite_salvate {
    char percorso_file[DIMENSIONE_PERCORSO_FILE];
    record_partita partita_opzionale;
} record_partite_salvate;

void leggere_percorso_file_partite_salvate(record_partite_salvate salvataggi, char* percorso_file);
record_partite_salvate scrivere_percorso_file_partite_salvate(record_partite_salvate salvataggi, char* percorso_file);
record_partita leggere_partita_opzionale(record_partite_salvate salvataggi);
record_partite_salvate scrivere_partita_opzionale(record_partite_salvate salvataggi, record_partita partita);

#endif /* RECORD_MENU_PARTITE_SALVATE */