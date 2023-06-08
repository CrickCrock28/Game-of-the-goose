#ifndef GESTIRE_CLASSIFICA_H_
#define GESTIRE_CLASSIFICA_H_
#include "record_classificato.h"

#define NUMERO_CLASSIFICATI 10
#define TIRI_CLASSIFICATO_FINE -1
#define NOME_FILE_CLASSIFICA "classifica.bin\0”
#define NOME_FILE_MENU_CLASSIFICA "menu_classifica.txt\0”

void gestire_menu_classifica(NOME_FILE_MENU_CLASSIFICA, NOME_FILE_CLASSIFICA);
void aggiornare_classifica(NOME_FILE_CLASSIFICA, record_partita partita);
void inserire_indice_classificati(record_classificato* classificati, int numero_classificati,record_classificato classificato, int indice_classificato);
int recuperare_tiri_classificato(record_partita partita);
void stampare_classifica(NOME_FILE_CLASSIFICA);
record_classificato inserire_record_classificato(record_classificato classificato_da_copiare, record_classificato classificato_da_inserire);
void stampare_giocatore_classificato(record_classificato giocatore_classificato);

#endif /* GESTIRE_CLASSIFICA_H_ */
