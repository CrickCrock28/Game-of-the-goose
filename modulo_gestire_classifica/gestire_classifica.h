#ifndef GESTIRE_CLASSIFICA_H_
#define GESTIRE_CLASSIFICA_H_
#include <costanti.h>

#define NUMERO_CLASSIFICATI 10
#define TIRI_CLASSIFICATO_FINE -1
#define NOME_FILE_CLASSIFICA "classifica.bin\0”
#define NOME_FILE_MENU_CLASSIFICA "menu_classifica.txt\0”

void gestire_menu_classifica(NOME_FILE_MENU_CLASSIFICA, NOME_FILE_CLASSIFICA);
void aggiornare_classifica(NOME_FILE_CLASSIFICA,record_partita partita);
void inserire_indice_classificati();
void recuperare_tiri_classificato();
void stampare_classifica();
void inserire_record_classificato();
void stampare_giocatore_classificato();

#endif /* GESTIRE_CLASSIFICA_H_ */
