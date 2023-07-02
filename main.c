#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "costanti.h"
#include "percorsi_file.h"
#include "..\\src\\moduli_record\\modulo_record_classificato\\record_classificato.h"
#include "..\\src\\moduli_record\\modulo_record_giocatore\\record_giocatore.h"
#include "..\\src\\moduli_record\\modulo_record_partita\\record_partita.h"
#include "..\\src\\moduli_record\\modulo_record_partite_salvate\\record_partite_salvate.h"
#include "..\\src\\moduli_record\\modulo_record_percorso\\record_percorso.h"
#include "..\\src\\moduli_record\\modulo_record_vet_giocatori\\record_vet_giocatori.h"
#include "..\\src\\moduli_record\\modulo_record_vettore_partite_salvate\\record_vettore_partite_salvate.h"
#include "..\\src\\modulo_gestire_azioni_semplici\\gestire_azioni_semplici.h"
#include "..\\src\\modulo_creare_nuova_partita\\creare_nuova_partita.h"
#include "..\\src\\modulo_gestire_aiuto\\gestire_aiuto.h"
#include "..\\src\\modulo_gestire_classifica\\gestire_classifica.h"
#include "..\\src\\modulo_gestire_file\\gestire_file.h"
#include "..\\src\\modulo_gestire_partite_salvate\\gestire_partite_salvate.h"
#include "..\\src\\modulo_giocare_partita\\giocare_partita.h"


#define SCELTA_MENU_NUOVA_PARTITA 1 // Scelta corrispondende al menu nuova partita
#define SCELTA_MENU_PARTITE_SALVATE 2 // Scelta corrispondende al menu carica partita
#define SCELTA_MENU_CLASSIFICA 3 // Scelta corrispondende al menu classifica
#define SCELTA_MENU_AIUTO 4 // Scelta corrispondende al menu aiuto
#define SCELTA_CONTINUARE_PARTITA 1 // Indica che l'utente vuole continuare la partita appena salvata

//void inizializzare_file(void);
#define MESSAGGIO_FILE_NON_TROVATO "Impossibile trovare il file: \0"

bool verificare_esistenza_tutti_file(){//MANCA FILE TITOLO
    
	bool tutti_i_file_esistono = true;

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_NUOVA_PARTITA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_NUOVA_PARTITA);
        tutti_i_file_esistono = false;
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_PRINCIPALE)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_PRINCIPALE);
        tutti_i_file_esistono = false;
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_PARTITE_SALVATE)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_PARTITE_SALVATE);
        tutti_i_file_esistono = false;
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_AIUTO)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_AIUTO);
        tutti_i_file_esistono = false;
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_CLASSIFICA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_CLASSIFICA);
        tutti_i_file_esistono = false;
    }

    if(!verificare_file_esistente(PERCORSO_FILE_CLASSIFICA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_CLASSIFICA);
        tutti_i_file_esistono = false;
    }

    if(!verificare_file_esistente(PERCORSO_FILE_REGOLE_GIOCO)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_REGOLE_GIOCO);
        tutti_i_file_esistono = false;
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MANUALE_GIOCO)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MANUALE_GIOCO);
        tutti_i_file_esistono = false;
    }

    if(!verificare_file_esistente(PERCORSO_FILE_CLASSIFICA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_CLASSIFICA);
        tutti_i_file_esistono = false;
    }

    if(!verificare_file_esistente(PERCORSO_FILE_PARTITE_SALVATE)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_PARTITE_SALVATE);
        tutti_i_file_esistono = false;
    }

    return tutti_i_file_esistono;
}

int main(void) {
    bool partita_caricata;
    int scelta,
        riprendere_partita,
        riga;
    record_partita partita;
    record_partite_salvate salvataggi;

    srand(time(NULL));


    while(!verificare_esistenza_tutti_file()){
    	system("pause");
    }

    salvataggi = scrivere_percorso_file_partite_salvate(salvataggi, PERCORSO_FILE_PARTITE_SALVATE);

    partita_caricata = false; // indica se l’utente ha caricato una partita in RAM dal file delle partite salvate
	do {

		// Stampa il menu principale
		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		riga = stampare_file_di_testo(PERCORSO_FILE_MENU_PRINCIPALE);
		scelta = chiedere_intero(MESSAGGIO_SCELTA, SCELTA_USCIRE_DAL_MENU, SCELTA_MENU_AIUTO, (riga+1), PRIMA_COORDINATA_SCHERMO);

		// Se l'utente sceglie di creare una nuova partita
		if (scelta == SCELTA_MENU_NUOVA_PARTITA) {
			// Se la partita è stata caricata dal file delle partite salvate
			if (partita_caricata == true) {
				// Gioca la partita caricata
				partita = giocare_partita(partita);
			}
			else {
				partita = gestire_menu_nuova_partita(PERCORSO_FILE_MENU_NUOVA_PARTITA);
			}
		}

		// Se l'utente sceglie di aprire il menu partite salvate
		else if (scelta == SCELTA_MENU_PARTITE_SALVATE) {
			salvataggi = gestire_menu_partite_salvate(salvataggi, PERCORSO_FILE_MENU_PARTITE_SALVATE);
			/* leggere_partite_salvate(salvataggi, &partite_salvate); ? legge le partite salvate, \
			l'output è inserito in partite_salvate passato per indirizzo

			partite_salvate = leggere_partite_salvate(salvataggi); <-- questa sta nello pseudocodice*/

			if (leggere_indice_giocatore_di_turno_record_partita(leggere_partita_opzionale(salvataggi)) == PARTITA_OPZIONALE_INESISTENTE) {
				partita = leggere_partita_opzionale(salvataggi);
				partita_caricata = true;
			}
		}

		// Se l'utente sceglie di aprire il menu classifica
		else if (scelta == SCELTA_MENU_CLASSIFICA) {
			gestire_menu_classifica(PERCORSO_FILE_MENU_CLASSIFICA, PERCORSO_FILE_CLASSIFICA);
		}

		// Se l'utente scegie di aprire il menu aiuto
		else if (scelta == SCELTA_MENU_AIUTO) {
			gestire_menu_aiuto(PERCORSO_FILE_MENU_AIUTO, PERCORSO_FILE_REGOLE_GIOCO, PERCORSO_FILE_MANUALE_GIOCO);
		}

	} while (scelta != SCELTA_USCIRE_DAL_MENU);

    return EXIT_SUCCESS;
}
