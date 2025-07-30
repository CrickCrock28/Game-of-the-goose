#include "gestire_aiuto.h"

#include <stdlib.h>

#include "..\\costanti.h"
#include "..\\modulo_gestire_file\\gestire_file.h"
#include "..\\modulo_gestire_azioni_semplici\\gestire_azioni_semplici.h"
#include "..\\modulo_spostare_cursore\\spostare_cursore.h"


#define SCELTA_STAMPARE_REGOLE 1
#define SCELTA_STAMPARE_MANUALE 2


void gestire_scelta_menu_aiuto(int scelta, char* percorso_file_regole_gioco, char* percorso_file_manuale_gioco);

void gestire_scelta_menu_aiuto(int scelta, char* percorso_file_regole_gioco, char* percorso_file_manuale_gioco) {

	if (scelta == SCELTA_STAMPARE_REGOLE) {
		// Stampare le regole del gioco
		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		stampare_file_di_testo(percorso_file_regole_gioco);
		system("pause");
	}
	else if (scelta == SCELTA_STAMPARE_MANUALE) {
		// Stampare il manuale del gioco
		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		stampare_file_di_testo(percorso_file_manuale_gioco);
		system("pause");
	}

	return;
}

void gestire_menu_aiuto(char* percorso_file_menu_aiuto, char* percorso_file_regole_gioco, char* percorso_file_manuale_gioco) {
    int scelta; // Scelta di una azione del menù aiuto
    int riga;
    
    do {
        // Stampare il menù aiuto
        system("cls");
	    spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
        stampare_file_di_testo(percorso_file_menu_aiuto);

        // Richiedere un valore intero per scegliere l'azione del menù e ne attende l'inserimento
    	riga = ottenere_riga_cursore();
        scelta = chiedere_intero(MESSAGGIO_SCELTA_AZIONE_MENU, SCELTA_USCIRE_DAL_MENU, SCELTA_STAMPARE_MANUALE, riga, PRIMA_COORDINATA_SCHERMO);

    	// Gestisce la scelta dell'utente
    	gestire_scelta_menu_aiuto(scelta, percorso_file_regole_gioco, percorso_file_manuale_gioco);


    } while (scelta != SCELTA_USCIRE_DAL_MENU);

    return;
}
