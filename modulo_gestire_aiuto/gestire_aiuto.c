#include "gestire_aiuto.h"

void gestire_menu_aiuto(char* NOME_FILE_MENU_AIUTO, char* NOME_FILE_REGOLE_GIOCO, char* NOME_FILE_MANUALE_GIOCO) {
    int scelta; // Scelta di una azione del menù
    FILE* menu_aiuto, // Puntatore al file menù aiuto
    *manuale_gioco,  // Puntatore al file contenente il manuale gioco
    *regole_gioco; // Puntatore al file contenente le regole 
    // Aprire i file di testo in lettura
    menu_aiuto = fopen(NOME_FILE_MENU_AIUTO, "r");
    manuale_gioco = fopen(NOME_FILE_MANUALE_GIOCO, "r");
    regole_gioco = fopen(NOME_FILE_REGOLE_GIOCO, "r");

    if (verificare_file_esistente(menu_aiuto) == true && verificare_file_esistente(manuale_gioco) == true && verificare_file_esistente(regole_gioco) == true) {
        do {
            // Stampare il menù aiuto
            stampare_file_di_testo(menu_aiuto);
            // Richiedere un valore intero per scegliere l'azione del menù e ne attende l'inserimento
            scelta = chiedere_intero(MESSAGGIO_SCELTA, 0, 2, 7, 0);
            if (scelta == STAMPARE_REGOLE) {
                // Stampare le regole del gioco
                stampare_file_di_testo(regole_gioco);
            }
            else if (scelta == STAMPARE_MANUALE) {
                // Stampare il manuale del gioco
                stampare_file_di_testo(manuale_gioco);
            }
            rewind(menu_aiuto);
            rewind(regole_gioco);
            rewind(manuale_gioco);
        } while (scelta != USCIRE);
    }
    //Chiudere i file di testo precedentemente aperti
    fclose(menu_aiuto);
    fclose(manuale_gioco);
    fclose(regole_gioco);

    return;
}
