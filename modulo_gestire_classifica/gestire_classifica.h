#ifndef GESTIRE_CLASSIFICA_H_
#define GESTIRE_CLASSIFICA_H_

#include "../costanti.h"
#include "../modulo_record_classificato/record_classificato.h"
#define NUMERO_MASSIMO_CLASSIFICATI 10
#define TIRI_CLASSIFICATO_FINE -1
#define MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO "Inserire il nome del nuovo classificato(3 caratteri)\nInserisci:\0"

void gestire_menu_classifica(char* NOME_FILE_MENU_CLASSIFICA,char* NOME_FILE_CLASSIFICA);
void aggiornare_classifica(char* NOME_FILE_CLASSIFICA, record_partita partita, char* MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO, int NUMERO_MASSIMO_CLASSIFICATI);
int trovare_posizione_classificato(record_classificato* classificati, int tiri, int dimensione, int NUMERO_MASSIMO_CLASSIFICATI);
void inserire_indice_classificati(record_classificato* classificati, int numero_classificati,record_classificato classificato, int indice_classificato, int NUMERO_MASSIMO_CLASSIFICATI);
int aggiornare_dimensione(int dimensione, int NUMERO_MASSIMO_CLASSIFICATI);
int recuperare_tiri_classificato(record_partita partita);
void stampare_classifica(char* NOME_FILE_CLASSIFICA);
record_classificato inserire_record_classificato(record_classificato classificato_da_copiare, record_classificato classificato_da_inserire);
void stampare_giocatore_classificato(record_classificato giocatore_classificato);

#endif /* GESTIRE_CLASSIFICA_H_ */
