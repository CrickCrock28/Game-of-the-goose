#include "gestire_aiuto.h"

void gestire_menu_aiuto(){
    int scelta;
    do
    {
        stampare_file_di_testo("menu_aiuto.txt");
        chiedere_intero("Inserire scelta (0 a 2):", 0, 2, 7, 0);
        if(scelta == 1){
            stampare_file_di_testo("regole_gioco.txt");
        }else if(scelta == 2){
            stampare_file_di_testo("manuale_gioco.txt");
        }
    } while (scelta == 0);
}
