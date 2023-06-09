#ifndef RECORD_MENU_PARTITE_SALVATE_H_
#define RECORD_MENU_PARTITE_SALVATE_H_

#include "record_partita.h"

typedef struct record_menu_partite_salvate{
    FILE* file_partite_salvate;
    record_partita partita_opzionale;
} record_menu_partite_salvate;


#endif /* RECORD_MENU_PARTITE_SALVATE */