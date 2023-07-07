//PERFETTO
#ifndef GESTIRE_CLASSIFICA_H_
#define GESTIRE_CLASSIFICA_H_


#include "..\\moduli_record\\modulo_record_partita\\record_partita.h"


void gestire_menu_classifica(char* percorso_file_menu_classifica, char* percorso_file_classifica);
void aggiornare_classifica(record_partita partita, int indice_giocatore_vincitore);
void stampare_classifica(char* percorso_file_classifica);


#endif /* GESTIRE_CLASSIFICA_H_ */
