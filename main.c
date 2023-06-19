#include "record_classificato.h"
#include "record_giocatore.h"
#include "record_partita.h"
#include "record_partite_salvate.h"
#include "record_percorso.h"
#include "vet_giocatori.h"
#include "vettore_partite_salvate.h"
#include "azioni_semplici.h"
#include "creare_nuova_partita.h"
#include "gestire_aiuto.h"
#include "gestire_classifica.h"
#include "gestire_file.h"
#include "gestire_partite_salvate.h"
#include "giocare_partita.h"
#include "stdlib.h"
#include "stdio.h"


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


int main(void) {
    bool partita_caricata, creare_nuova_partita;
    int scelta, riprendere_partita;
    record_partita partita;
    record_salvataggi salvataggi;

    do {
        stampare_file_di_testo(NOME_FILE_MENU_PRINCIPALE);
        scelta = chiedere_intero(MESSAGGIO_INSERIMENTO, 0, 4, 9, 0);
        if (scelta == 1) {
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
            } while (riprendere_partita == 1);
        }
        else if (scelta == 2) {
            // menu carica partita
            gestire_menu_partite_salvate(NOME_FILE_MENU_CARICA_PARTITA, NOME_FILE_PARTITE_SALVATE, &salvataggi);
            // leggere_partite_salvate(salvataggi, &partite_salvate); ?
            if (leggere_indice_giocatore_di_turno_record_partita(leggere_partita_opzionale(salvataggi)) == PARTITA_OPZIONALE_INESISTENTE) {
                leggere_partita_opzionale(salvataggi, &partita);
                partita_caricata = true;
            }
        }
        else if (scelta == 3) {
            // menu classifica
            gestire_menu_classifica(NOME_FILE_MENU_CLASSIFICA);
        }
        else if (scelta == 4) {
            // menu aiuto
            gestire_menu_aiuto(NOME_FILE_MENU_AIUTO, NOME_FILE_REGOLE_GIOCO, NOME_FILE_MANUALE_GIOCO);
        }
    } while (scelta != 0);

    return EXIT_SUCCESS;
}