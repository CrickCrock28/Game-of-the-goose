#ifndef GESTIRE_CLASSIFICA_H_
#define GESTIRE_CLASSIFICA_H_

#include "../costanti.h"
#include "../modulo_gestire_file/gestire_file.h"
#include "../modulo_record_classificato/record_classificato.h"
#include "../modulo_creare_nuova_partita/creare_nuova_partita.h"
#include "../modulo_record_giocatore/record_giocatore.h"
#include "../modulo_record_vet_giocatori/record_vet_giocatori.h"
#include "../modulo_record_partita/record_partita.h"
#include "../modulo_record_percorso/record_percorso.h"
#include <stdbool.h>
#include <stdio.h>

#define MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO "Inserire il nome del nuovo classificato(3 caratteri)\nInserisci:\0"
#define STAMPARE_CLASSIFICA 1
#define NUMERO_MASSIMO_CLASSIFICATI 10
#define TIRI_CLASSIFICATO_FINE -1
#define GIOCATORE_NON_CLASSIFICATO -1
#define TITOLO_STAMPA_CLASSIFICA "Giocatori classificati:\n\0"
#define NUMERO_POSTO_CLASSIFICA "Posto numero\0"
#define NOME "nome: \0"
#define TIRI "tiri: \0"

// Gestisce il menù della classifica 
void gestire_menu_classifica(char* NOME_FILE_MENU_CLASSIFICA, char* NOME_FILE_CLASSIFICA);
// Aggiorna la classifica successivamente al termine di una partita
void aggiornare_classifica(char* NOME_FILE_CLASSIFICA, record_partita partita);
// Trova la posizione (se c'è) nella quale il giocatore che ha appena vinto la partita può essere inserito
int trovare_posizione_vincitore(record_classificato* classificati, int tiri, int dimensione);
// Aggiorna la dimensione della classifica se necessario
int aggiornare_dimensione_classifica(int dimensione);
// Inserisce il vincitore nel posto corretto della classifica
void inserire_vincitore_in_classifica(record_classificato* classificati, int numero_classificati,record_classificato classificato, int indice_classificato);
// Recupera il numero di tiri del vincitore
int recuperare_tiri_vincitore(record_partita partita);
// Copia un record classificato in un altro
record_classificato copiare_record_classificato(record_classificato classificato_con_dati_da_copiare, record_classificato classificato_con_dati_da_inserire);
// Stampa la classifica
void stampare_classifica(FILE* classifica);
// Stampa i dati di un singolo giocatore della classifica 
void stampare_giocatore_classificato(record_classificato giocatore_classificato);
// Carica da file in un array di classificati la classifica
void caricare_classifica_da_file(FILE* classifica, record_classificato* classificati);
#endif /* GESTIRE_CLASSIFICA_H_ */
