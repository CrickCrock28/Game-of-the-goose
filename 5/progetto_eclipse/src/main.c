#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "costanti.h"
#include "percorsi_file.h"

#include "..\\src\\modulo_gestire_file\\gestire_file.h"
#include "..\\src\\modulo_spostare_cursore\\spostare_cursore.h"
#include "..\\src\\modulo_gestire_azioni_semplici\\gestire_azioni_semplici.h"

#include "..\\src\\moduli_record\\modulo_record_partita\\record_partita.h"
#include "..\\src\\moduli_record\\modulo_record_partite_salvate\\record_partite_salvate.h"
#include "..\\src\\modulo_creare_nuova_partita\\creare_nuova_partita.h"
#include "..\\src\\modulo_giocare_partita\\giocare_partita.h"
#include "..\\src\\modulo_gestire_partite_salvate\\gestire_partite_salvate.h"
#include "..\\src\\modulo_gestire_classifica\\gestire_classifica.h"
#include "..\\src\\modulo_gestire_aiuto\\gestire_aiuto.h"


#define SCELTA_MENU_NUOVA_PARTITA 1 // Scelta corrispondende al menu nuova partita
#define SCELTA_MENU_PARTITE_SALVATE 2 // Scelta corrispondende al menu carica partita
#define SCELTA_MENU_CLASSIFICA 3 // Scelta corrispondende al menu classifica
#define SCELTA_MENU_AIUTO 4 // Scelta corrispondende al menu aiuto


int main(void) {
    bool partita_caricata;
    int scelta,
        riga;
    record_partita partita;
    record_partite_salvate salvataggi;

    srand(time(NULL));

    while(!verificare_esistenza_tutti_file()){
    	system("pause");
    }

    salvataggi = scrivere_percorso_file_partite_salvate_record_partite_salvate(salvataggi, PERCORSO_FILE_PARTITE_SALVATE);

    // Imposto a false il flag che indica se l'utente ha scelto di creare una nuova partita all'interno del menu partita
    partita = scrivere_nuova_partita_record_partita(partita, false);
    // Imposto a false indica se l’utente ha caricato una partita
    partita_caricata = false;
	do {

		// Se la partita è stata caricata dal file delle partite salvate
		if (partita_caricata == true) {
			// Gioca la partita caricata
			partita = giocare_partita(partita);
			partita_caricata = false;
		}

		// Se l'utente ha scelto di creare una nuova partita all'interno del menu partita
		if (leggere_nuova_partita_record_partita(partita)){
			// Crea una nuova partita
			partita = gestire_menu_nuova_partita(PERCORSO_FILE_MENU_NUOVA_PARTITA);
		}

		// Stampa il menu principale
		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		stampare_file_di_testo(PERCORSO_FILE_MENU_PRINCIPALE);
		riga = ottenere_riga_cursore();
		scelta = chiedere_intero(MESSAGGIO_SCELTA_AZIONE_MENU, SCELTA_USCIRE_DAL_MENU, SCELTA_MENU_AIUTO, riga, PRIMA_COORDINATA_SCHERMO);

		// Se l'utente sceglie di creare una nuova partita
		if (scelta == SCELTA_MENU_NUOVA_PARTITA) {
			partita = gestire_menu_nuova_partita(PERCORSO_FILE_MENU_NUOVA_PARTITA);
		}

			// Se l'utente sceglie di aprire il menu partite salvate
			else if (scelta == SCELTA_MENU_PARTITE_SALVATE) {
				salvataggi = gestire_menu_partite_salvate(salvataggi, PERCORSO_FILE_MENU_PARTITE_SALVATE);

				// Se è presente una partita nel record salvataggi (quindi se il giocatore ha caricato una partita)
				if (leggere_partita_presente_record_partite_salvate(salvataggi)) {
					//Legge la partita caricata
					partita = leggere_partita_opzionale_record_partite_salvate(salvataggi);
					// imposta partita caricata a true in modo da giocarla alla prossima iterazione del ciclo
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
