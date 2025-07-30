#ifndef RECORD_PARTITE_SALVATE_H_
#define RECORD_PARTITE_SALVATE_H_


#include <stdbool.h>

#include "..\\..\\costanti.h"
#include "..\\..\\moduli_record\\modulo_record_partita\\record_partita.h"


typedef struct record_partite_salvate {
    char percorso_file[DIMENSIONE_MASSIMA_PERCORSO_FILE];
    record_partita partita_opzionale;
    bool partita_presente;
} record_partite_salvate;


void leggere_percorso_file_partite_salvate_record_partite_salvate(record_partite_salvate salvataggi, char* percorso_file);
record_partite_salvate scrivere_percorso_file_partite_salvate_record_partite_salvate(record_partite_salvate salvataggi, char* percorso_file);
record_partita leggere_partita_opzionale_record_partite_salvate(record_partite_salvate salvataggi);
record_partite_salvate scrivere_partita_opzionale_record_partite_salvate(record_partite_salvate salvataggi, record_partita partita);
bool leggere_partita_presente_record_partite_salvate(record_partite_salvate salvataggi);
record_partite_salvate scrivere_partita_presente_record_partite_salvate(record_partite_salvate salvataggi, bool partita_presente);


#endif /* RECORD_MENU_PARTITE_SALVATE */
