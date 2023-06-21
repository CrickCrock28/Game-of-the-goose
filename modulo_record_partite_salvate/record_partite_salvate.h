#ifndef RECORD_PARTITE_SALVATE_H_
#define RECORD_PARTITE_SALVATE_H_

#include "../modulo_record_partita/record_partita.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct record_partite_salvate{
    FILE* file_partite_salvate;
    record_partita partita_opzionale;
} record_partite_salvate;

FILE* leggere_file_partite_salvate(record_partite_salvate salvataggi);
record_partite_salvate scrivere_file_partite_salvate(record_partite_salvate salvataggi, FILE* file_salvataggi);
record_partita leggere_partita_opzionale(record_partite_salvate salvataggi);
record_partite_salvate scrivere_partita_opzionale(record_partite_salvate salvataggi, record_partita partita);

#endif /* RECORD_MENU_PARTITE_SALVATE */