#include <stdlib.h>
#include <stdio.h>

#include "costanti.h"
#include "moduli_record/modulo_record_classificato/record_classificato.h"
#include "moduli_record/modulo_record_giocatore/record_giocatore.h"
#include "moduli_record/modulo_record_partita/record_partita.h"
#include "moduli_record/modulo_record_partite_salvate/record_partite_salvate.h"
#include "moduli_record/modulo_record_percorso/record_percorso.h"
#include "moduli_record/modulo_record_vet_giocatori/record_vet_giocatori.h"
#include "moduli_record/modulo_record_vettore_partite_salvate/record_vettore_partite_salvate.h"
#include "modulo_gestire_azioni_semplici/gestire_azioni_semplici.h"
#include "modulo_creare_nuova_partita/creare_nuova_partita.h"
#include "modulo_gestire_aiuto/gestire_aiuto.h"
#include "modulo_gestire_classifica/gestire_classifica.h"
#include "modulo_gestire_file/gestire_file.h"
#include "modulo_gestire_partite_salvate/gestire_partite_salvate.h"
#include "modulo_giocare_partita/giocare_partita.h"

#define PERCORSO_FILE_MENU_NUOVA_PARTITA "file_aggiuntivi\\menu_nuova_partita.txt\0" // Nome del file che contiene il menù nuova partita
#define PERCORSO_FILE_MENU_PRINCIPALE "file_aggiuntivi\\menu_principale.txt\0" // Nome del file che contiene il menù principale
#define PERCORSO_FILE_MENU_CARICA_PARTITA "file_aggiuntivi\\menu_carica_partita.txt\0" // Nome del file che contiene il menù carica partita
#define PERCORSO_FILE_MENU_AIUTO "file_aggiuntivi\\menu_aiuto.txt\0" // Nome del file che contiene il menù aiuto
#define PERCORSO_FILE_MENU_CLASSIFICA "file_aggiuntivi\\menu_classifica.txt\0" // Nome del file che contiene il menù classifica
#define PERCORSO_FILE_CLASSIFICA "file_aggiuntivi\\classifica.bin\0" // Nome del file che contiene la classifica
#define PERCORSO_FILE_REGOLE_GIOCO "file_aggiuntivi\\regole_gioco.txt\0" // Nome del file che contiene le regole di gioco
#define PERCORSO_FILE_MANUALE_GIOCO "file_aggiuntivi\\manuale_gioco.txt\0" // Nome del file che contiene il manuale di gioco
#define PERCORSO_FILE_MENU_RIPRENDERE_PARTITA "file_aggiuntivi\\menu_riprendere_partita.txt\0" // Nome del file che contiene il menù riprendere partita appena salvata
#define PERCORSO_FILE_MENU_SCELTA_DATI_NUOVA_PARTITA "file_aggiuntivi\\menu_scelta_dati_nuova_partita.txt\0"	// Nome del file che contiene il menù scegliere dati nuova parita

#define SCELTA_MENU_NUOVA_PARTITA 1 // Scelta corrispondende al menu nuova partita
#define SCELTA_MENU_CARICA_PARTITA 2 // Scelta corrispondende al menu carica partita
#define SCELTA_MENU_CLASSIFICA 3 // Scelta corrispondende al menu classifica
#define SCELTA_MENU_AIUTO 4 // Scelta corrispondende al menu aiuto
#define SCELTA_CONTINUARE_PARTITA 1 // Indica che l'utente vuole continuare la partita appena salvata

//void inizializzare_file(void);
#define MESSAGGIO_FILE_NON_TROVATO "Impossibile trovare il file: \0"

void verificare_esistenza_tutti_file(){//MANCA FILE TITOLO
    
    if(!verificare_file_esistente(PERCORSO_FILE_MENU_NUOVA_PARTITA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_NUOVA_PARTITA);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_PRINCIPALE)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_PRINCIPALE);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_CARICA_PARTITA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_CARICA_PARTITA);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_AIUTO)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_AIUTO);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_CLASSIFICA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_CLASSIFICA);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_CLASSIFICA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_CLASSIFICA);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_REGOLE_GIOCO)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_REGOLE_GIOCO);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MANUALE_GIOCO)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MANUALE_GIOCO);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_RIPRENDERE_PARTITA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_RIPRENDERE_PARTITA);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_MENU_SCELTA_DATI_NUOVA_PARTITA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_MENU_SCELTA_DATI_NUOVA_PARTITA);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_CLASSIFICA)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_CLASSIFICA);
    }

    if(!verificare_file_esistente(PERCORSO_FILE_PARTITE_SALVATE)){
        printf("%s%s\n", MESSAGGIO_FILE_NON_TROVATO, PERCORSO_FILE_PARTITE_SALVATE);
    }

    return;
}

int main(void) {
    bool partita_caricata,
        creare_nuova_partita;
    int scelta,
        riprendere_partita,
        riga;
    record_partita partita;
    record_partite_salvate salvataggi;

    //inizializzare_file(); //quando funziona il programma decommentare
    verificare_esistenza_tutti_file();
    partita_caricata = false; // indica se l’utente ha caricato una partita in RAM dal file delle partite salvate
	creare_nuova_partita = false; // indica se l’utente vuole creare una nuova partita incurante di quella precedente in corso
	do {
		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		riga = stampare_file_di_testo(PERCORSO_FILE_MENU_PRINCIPALE);
		scelta = chiedere_intero(MESSAGGIO_SCELTA, SCELTA_USCIRE_DAL_MENU, SCELTA_MENU_AIUTO, (riga+1), PRIMA_COORDINATA_SCHERMO);
		if (scelta == SCELTA_MENU_NUOVA_PARTITA) {
			if (partita_caricata == true) {
				// la partita e' stata caricata dal file delle partite salvate
				partita = giocare_partita(partita);
			}
			else {
				// se l’utente vuole creare una nuova partita, questa viene creata nella funzione gestire_menu_nuova_partita
				if (creare_nuova_partita == false) {
					partita = gestire_menu_nuova_partita(PERCORSO_FILE_MENU_NUOVA_PARTITA);//PERCORSO_FILE_MENU_SCELTA_DATI_NUOVA_PARTITA); PRIMA C'ERA QUESTO
				}
			}
			do {
				if (leggere_terminata_record_partita(partita) == true) {
					// aggiorno la classifica
					aggiornare_classifica(PERCORSO_FILE_CLASSIFICA, partita);
				}
				else {
					if (leggere_salva_partita_record_partita(partita) == true) {
						// salvo la partita
						salvare_partita(PERCORSO_FILE_PARTITE_SALVATE, partita);
						// chiedo all'utente se vuole continuare la partita
						system("cls");
	                    spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
						stampare_file_di_testo(PERCORSO_FILE_MENU_RIPRENDERE_PARTITA);
						riprendere_partita = chiedere_intero(MESSAGGIO_SCELTA, SCELTA_USCIRE_DAL_MENU, 1, (riga+1), PRIMA_COORDINATA_SCHERMO); //NUMERO MAGICO
					}
				}
			} while (riprendere_partita == SCELTA_CONTINUARE_PARTITA);
		}
		else if (scelta == SCELTA_MENU_CARICA_PARTITA) {
			salvataggi = gestire_menu_partite_salvate(salvataggi, PERCORSO_FILE_MENU_CARICA_PARTITA);
			/* leggere_partite_salvate(salvataggi, &partite_salvate); ? legge le partite salvate, \
			l'output è inserito in partite_salvate passato per indirizzo

			partite_salvate = leggere_partite_salvate(salvataggi); <-- questa sta nello pseudocodice*/

			if (leggere_indice_giocatore_di_turno_record_partita(leggere_partita_opzionale(salvataggi)) == PARTITA_OPZIONALE_INESISTENTE) {
				partita = leggere_partita_opzionale(salvataggi);
				partita_caricata = true;
			}
		}
		else if (scelta == SCELTA_MENU_CLASSIFICA) {
			gestire_menu_classifica(PERCORSO_FILE_MENU_CLASSIFICA, PERCORSO_FILE_CLASSIFICA);
		}
		else if (scelta == SCELTA_MENU_AIUTO) {
			gestire_menu_aiuto(PERCORSO_FILE_MENU_AIUTO, PERCORSO_FILE_REGOLE_GIOCO, PERCORSO_FILE_MANUALE_GIOCO);
		}
	} while (scelta != SCELTA_USCIRE_DAL_MENU);

	printf("TERMINATOOOO");
    system("pause");

    return EXIT_SUCCESS;
}
/*
void inizializzare_file(void) {
    FILE* file_partite_salvate,
        *file_classifica;

    file_classifica = fopen(PERCORSO_FILE_CLASSIFICA, "rb");
    if (verificare_file_esistente(file_classifica) == false) {
        // ricontrollare se i dati di default per il file sono corretti
        file_classifica = fopen(PERCORSO_FILE_CLASSIFICA, "wb");
        fwrite(0, sizeof(int), 1, file_classifica);
    }

    file_partite_salvate = fopen(PERCORSO_FILE_PARTITE_SALVATE, "rb");
    if (verificare_file_esistente(file_partite_salvate) == false) {
        file_partite_salvate = fopen(PERCORSO_FILE_PARTITE_SALVATE, "wb");
        // scrivere i dati di default per questo file, se esistono, altrimenti eliminare questi due commenti
        //fwrite(0, sizeof(int), 1, file_partite_salvate);
    }
    // altri file binari che devono essere creati e modificati a runtime, non dovrebbero essercene altri
    fclose(file_partite_salvate);
    fclose(file_classifica);

    return;
}*/
