#include <gestire_aiuto.h>
#include <gestire_file.h>
#include <costanti.h>

void gestire_menu_aiuto(){
    int scelta;
    if(verificare_file_esistente(NOME_FILE_MENU_AIUTO) && verificare_file_esistente(NOME_FILE_MANUALE_GIOCO) && verificare_file_esistente(NOME_FILE_REGOLE_GIOCO)){
        do{
            stampare_file_di_testo("menu_aiuto.txt");
            chiedere_intero(MESSAGGIO_SCELTA, 0, 2, 7, 0);
            if(scelta == 1){
                stampare_file_di_testo("regole_gioco.txt");
            }else if(scelta == 2){
                stampare_file_di_testo("manuale_gioco.txt");
            }
        } while (scelta == 0);
    }
    return;
}
