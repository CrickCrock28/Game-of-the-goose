#ifndef GESTIRE_PARTITE_SALVATE_H_
#define GESTIRE_PARTITE_SALVATE_H_

#include "..\\moduli_record\\modulo_record_partite_salvate\\record_partite_salvate.h"
#include "..\\moduli_record\\modulo_record_partita\\record_partita.h"

record_partite_salvate gestire_menu_partite_salvate(record_partite_salvate salvataggi, char* percorso_file_menu_carica_partita);
void salvare_partita(char* percorso_file_partite_salvate, record_partita partita);

#endif /* GESTIRE_PARTITE_SALVATE_H_ */
