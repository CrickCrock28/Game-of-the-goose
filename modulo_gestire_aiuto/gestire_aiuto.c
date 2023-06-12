#include "gestire_aiuto.h"
#include "../modulo_gestire_file/gestire_file.h"
#include "../costanti.h"

void gestire_menu_aiuto(char* NOME_FILE_MENU_AIUTO, char* NOME_FILE_REGOLE_GIOCO, char* NOME_FILE_MANUALE_GIOCO) {
    int scelta;
    FILE* menu_aiuto, *manuale_gioco, *regole_gioco;
    menu_aiuto = fopen(NOME_FILE_MENU_AIUTO, "r");
    manuale_gioco = fopen(NOME_FILE_MANUALE_GIOCO, "r");
    regole_gioco = fopen(NOME_FILE_REGOLE_GIOCO, "r");

    if (verificare_file_esistente(menu_aiuto) && verificare_file_esistente(manuale_gioco) && verificare_file_esistente(regole_gioco)) {
        do{
            stampare_file_di_testo(menu_aiuto);
            chiedere_intero(MESSAGGIO_SCELTA, 0, 2, 7, 0);
            if (scelta == 1) {
                stampare_file_di_testo(regole_gioco);
            }else if (scelta == 2) {
                stampare_file_di_testo(manuale_gioco);
            }
        } while (scelta == 0);
    }
    return;
}
