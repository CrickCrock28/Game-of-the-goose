#include "gestire_aiuto.h"

void gestire_menu_aiuto(char* percorso_file_menu_aiuto, char* percorso_file_regole_di_gioco, char* percorso_file_manuale_gioco) {
    int scelta; // Scelta di una azione del menù aiuto
    
    do {
        // Stampare il menù aiuto
        system("cls");
	    spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
        stampare_file_di_testo(percorso_file_menu_aiuto);
        // Richiedere un valore intero per scegliere l'azione del menù e ne attende l'inserimento
        scelta = chiedere_intero(MESSAGGIO_SCELTA, 0, 2, 7, 0);
        if (scelta == SCELTA_STAMPARE_REGOLE) {
            // Stampare le regole del gioco
            system("cls");
            spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
            stampare_file_di_testo(percorso_file_manuale_gioco);
        }
        else if (scelta == SCELTA_STAMPARE_MANUALE) {
            // Stampare il manuale del gioco
            system("cls");
            spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
            stampare_file_di_testo(percorso_file_regole_di_gioco);
        }
    } while (scelta != SCELTA_USCIRE_DAL_MENU);

    return;
}
