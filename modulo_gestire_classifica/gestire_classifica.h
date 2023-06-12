#ifndef GESTIRE_CLASSIFICA_H_
#define GESTIRE_CLASSIFICA_H_

#include "../costanti.h"
#include "../modulo_record_classificato/record_classificato.h"
#define NUMERO_MASSIMO_CLASSIFICATI 10
#define TIRI_CLASSIFICATO_FINE -1
#define MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO "Inserire il nome del nuovo classificato(3 caratteri)\nInserisci:\0"

//gestisce il menù della classifica 
void gestire_menu_classifica(char* NOME_FILE_MENU_CLASSIFICA,char* NOME_FILE_CLASSIFICA);
//aggiorna la classifica successivamente al termine di una partita
void aggiornare_classifica(char* NOME_FILE_CLASSIFICA, record_partita partita, char* MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO, int NUMERO_MASSIMO_CLASSIFICATI);
//trova la posizione (se cè) nella quale il giocatore che ha appena vinto la partita può essere inserito
int trovare_posizione_vincitore(record_classificato* classificati, int tiri, int dimensione, int NUMERO_MASSIMO_CLASSIFICATI);
//aggiorna la dimensione della classifica se necessario
int aggiornare_dimensione_classifica(int dimensione, int NUMERO_MASSIMO_CLASSIFICATI);
//inserisce il vincitore nel posto corretto della classifica
void inserire_vincitore_in_classifica(record_classificato* classificati, int numero_classificati,record_classificato classificato, int indice_classificato, int NUMERO_MASSIMO_CLASSIFICATI);
//recupera il numero di tiri del vincitore
int recuperare_tiri_vincitore(record_partita partita);
//copia un record classificato in un altro
record_classificato copiare_record_classificato(record_classificato classificato_con_dati_da_copiare, record_classificato classificato_con_dati_da_inserire);
//stampa la classifica
void stampare_classifica(char* NOME_FILE_CLASSIFICA);
//stampa i dati di un singolo giocatore della classifica 
void stampare_giocatore_classificato(record_classificato giocatore_classificato);

#endif /* GESTIRE_CLASSIFICA_H_ */
