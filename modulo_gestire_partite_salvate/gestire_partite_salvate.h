#ifndef GESTIRE_PARTITE_SALVATE_H_
#define GESTIRE_PARTITE_SALVATE_H_

#include "../modulo_record_vettore_partite_salvate/record_vettore_partite_salvate.h"
#include "../modulo_record_partite_salvate/record_partite_salvate.h"
#include "../modulo_record_partita/record_partita.h"
#include "../modulo_creare_nuova_partita/creare_nuova_partita.h"
#include <stdlib.h>
#include <stdio.h>

#define NUMERO_MASSIMO_PARTITE_SALVATE 5
#define MESSAGGIO_SCELTA_MENU "Inserire un intero che rappresenta la scelta\0"
#define PARTITA_OPZIONALE_INESISTENTE -2

record_partite_salvate gestire_menu_partite_salvate(int scelta, record_partite_salvate salvataggi, int numero_partita, const char* menu_carica_partita);
record_partita leggere_partita_scelta(FILE* file_partite_salvate, int numero_partite);
FILE* salvare_partita(FILE* file_partite_salvate, record_partita partita);
int stampare_partite_salvate(FILE* file_partite_salvate); 
FILE* cancellare_partita_da_file(FILE* file_partite_salvate, int numero_partita);
record_vettore_partite_salvate rimuovere_partita_da_vettore(record_vettore_partite_salvate vettore_partite_salvate, int indice_elemento_da_rimuovere);

#endif /* GESTIRE_PARTITE_SALVATE_H_ */