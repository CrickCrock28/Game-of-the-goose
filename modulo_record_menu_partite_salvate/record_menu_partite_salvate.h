#ifndef RECORD_MENU_PARTITE_SALVATE_H_
#define RECORD_MENU_PARTITE_SALVATE_H_

#include "record_partita.h"

typedef struct record_partite_salvate{
    FILE* file_partite_salvate;
    record_partita partita_opzionale;
} record_menu_partite_salvate;

FILE* leggere_file_partite_salvate();
void scrivere_file_partite_salvate();
record_partita leggere_partita_opzionale();
void scrivere_partita_opzionale();

#endif /* RECORD_MENU_PARTITE_SALVATE */