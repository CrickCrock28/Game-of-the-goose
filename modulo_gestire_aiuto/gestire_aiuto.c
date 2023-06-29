#include "gestire_aiuto.h"

void gestire_menu_aiuto(char* percorso_file_menu_aiuto, char* percorso_file_regole_gioco, char* percorso_file_manuale_gioco) {
    int scelta; // Scelta di una azione del menù aiuto
    int riga;
    
    do {
        // Stampare il menù aiuto
        system("cls");
	    spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
        riga = stampare_file_di_testo(percorso_file_menu_aiuto);
        // Richiedere un valore intero per scegliere l'azione del menù e ne attende l'inserimento
        scelta = chiedere_intero(MESSAGGIO_SCELTA, SCELTA_USCIRE_DAL_MENU, SCELTA_STAMPARE_MANUALE, (riga + 1), PRIMA_COORDINATA_SCHERMO);
        if (scelta == SCELTA_STAMPARE_REGOLE) {
            // Stampare le regole del gioco
            system("cls");
            spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
            riga = stampare_file_di_testo(percorso_file_regole_gioco);
            system("pause"); // DA CAMBIARE
        }
        else if (scelta == SCELTA_STAMPARE_MANUALE) {
            // Stampare il manuale del gioco
            system("cls");
            spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
            riga = stampare_file_di_testo(percorso_file_manuale_gioco);
            system("pause"); // DA CAMBIARE
        }
    } while (scelta != SCELTA_USCIRE_DAL_MENU);

    return;
}
