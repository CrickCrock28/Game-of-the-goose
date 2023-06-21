#include <stdlib.h>
#include <stdio.h>

#include "modulo_record_classificato/record_classificato.h"
#include "modulo_record_giocatore/record_giocatore.h"
#include "modulo_record_partita/record_partita.h"
#include "modulo_record_partite_salvate/record_partite_salvate.h"
#include "modulo_record_percorso/record_percorso.h"
#include "modulo_record_vet_giocatori/record_vet_giocatori.h"
#include "modulo_record_vettore_partite_salvate/record_vettore_partite_salvate.h"
#include "modulo_azioni_semplici/azioni_semplici.h"
#include "modulo_creare_nuova_partita/creare_nuova_partita.h"
#include "modulo_gestire_aiuto/gestire_aiuto.h"
#include "modulo_gestire_classifica/gestire_classifica.h"
#include "modulo_gestire_file/gestire_file.h"
#include "modulo_gestire_partite_salvate/gestire_partite_salvate.h"
#include "modulo_giocare_partita/giocare_partita.h"


#define NOME_FILE_MENU_NUOVA_PARTITA "menu_nuova_partita.txt\0"
#define NOME_FILE_MENU_PRINCIPALE "menu_principale.txt\0"
#define NOME_FILE_MENU_CARICA_PARTITA "menu_carica_partita.txt\0"
#define NOME_FILE_MENU_AIUTO "menu_aiuto.txt\0"
#define NOME_FILE_MENU_CLASSIFICA "menu_classifica.txt\0"
#define MESSAGGIO_INSERIMENTO "Inserire la scelta: \0"
#define NOME_FILE_PARTITE_SALVATE "partite_salvate.bin\0"
#define NOME_FILE_CLASSIFICA "classifica.bin\0"
#define NOME_FILE_REGOLE_GIOCO "regole_gioco.txt\0"
#define NOME_FILE_MANUALE_GIOCO "manuale_gioco.txt\0"
#define MENU_NUOVA_PARTITA 1 // Scelta corrispondende al menu nuova partita
#define MENU_CARICA_PARTITA 2 // Scelta corrispondende al menu carica partita
#define MENU_CLASSIFICA 3 // Scelta corrispondende al menu classifica
#define MENU_AIUTO 4 // Scelta corrispondende al menu aiuto
#define CONTINUARE_PARTITA 1 // Indica che l'utente vuole continuare la partita appena salvata

int main(void) {
    bool partita_caricata, creare_nuova_partita;
    int scelta, riprendere_partita;
    record_partita partita;
    record_partite_salvate salvataggi;

    do {
        stampare_file_di_testo(NOME_FILE_MENU_PRINCIPALE);
        scelta = chiedere_intero(MESSAGGIO_INSERIMENTO, 0, 4, 9, 0);
        if (scelta == MENU_NUOVA_PARTITA) {
            riprendere_partita = 0;
            if (partita_caricata == true) {
                giocare_partita(&partita);
            }
            else {
                // se l’utente vuole crare una nuova partita, questa viene creata nella funzione gestire_menu_nuova_partita
                if (creare_nuova_partita == false) {
                    gestire_menu_nuova_partita(NOME_FILE_MENU_NUOVA_PARTITA, riprendere_partita, &partita);
                }
            }
            do {
                if (leggere_terminata_record_partita(partita) = true) {
                    // aggiorno la classifica
                    aggiornare_classifica(NOME_FILE_CLASSIFICA);
                }
                else {
                    if (leggere_salvare_partita_record_partita(partita) = true) {
                        // salvo la partita
                        salvare_partita(NOME_FILE_PARTITE_SALVATE, partita);
                        // chiedo all'utente se vuole continuare la partita
                        riprendere_partita = chiedere_intero(MESSAGGIO_INSERIMENTO, 0, 1);
                    }

                }
            } while (riprendere_partita == CONTINUARE_PARTITA);
        }
        else if (scelta == MENU_CARICA_PARTITA) {
            gestire_menu_partite_salvate(NOME_FILE_MENU_CARICA_PARTITA, NOME_FILE_PARTITE_SALVATE, &salvataggi);
            // leggere_partite_salvate(salvataggi, &partite_salvate); ?
            if (leggere_indice_giocatore_di_turno_record_partita(leggere_partita_opzionale(salvataggi)) == PARTITA_OPZIONALE_INESISTENTE) {
                leggere_partita_opzionale(salvataggi, &partita);
                partita_caricata = true;
            }
        }
        else if (scelta == MENU_CLASSIFICA) {
            gestire_menu_classifica(NOME_FILE_MENU_CLASSIFICA);
        }
        else if (scelta == MENU_AIUTO) {
            gestire_menu_aiuto(NOME_FILE_MENU_AIUTO, NOME_FILE_REGOLE_GIOCO, NOME_FILE_MANUALE_GIOCO);
        }
    } while (scelta != USCIRE);

    return EXIT_SUCCESS;
}