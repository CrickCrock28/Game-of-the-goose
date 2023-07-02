#ifndef GESTIRE_PARTITE_SALVATE_H_
#define GESTIRE_PARTITE_SALVATE_H_

#include "../costanti.h"
#include "../moduli_record/modulo_record_vettore_partite_salvate/record_vettore_partite_salvate.h"
#include "../moduli_record/modulo_record_partite_salvate/record_partite_salvate.h"
#include "../moduli_record/modulo_record_partita/record_partita.h"
#include "../modulo_creare_nuova_partita/creare_nuova_partita.h"
#include "../modulo_gestire_azioni_semplici/gestire_azioni_semplici.h"
#include <stdlib.h>
#include <stdio.h>

#define PARTITA_OPZIONALE_INESISTENTE -2

record_partite_salvate gestire_menu_partite_salvate(record_partite_salvate salvataggi, char* NOME_FILE_MENU_CARICA_PARTITA);
int contare_partite_salvate(char* percorso_file_partite_salvate);
void aggiungere_partita_su_file(char* percorso_file_partite_salvate, record_partita partita);
record_partita leggere_partita_scelta(char* percorso_file_partite_salvate, int numero_partita);
void salvare_partita(char* percorso_file_partite_salvate, record_partita partita);
int stampare_partite_salvate(char* percorso_file_partite_salvate);
void cancellare_partita_da_file(char* percorso_file_partite_salvate, int numero_partita);
//record_vettore_partite_salvate rimuovere_partita_da_vettore(record_vettore_partite_salvate vettore_partite_salvate, int indice_elemento_da_rimuovere); NON PENSO SERVA

#endif /* GESTIRE_PARTITE_SALVATE_H_ */
