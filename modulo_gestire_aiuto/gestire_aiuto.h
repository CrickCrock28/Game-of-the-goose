#ifndef GESTIRE_AIUTO_H_
#define GESTIRE_AIUTO_H_

#include "../costanti.h"
#include "../modulo_gestire_file/gestire_file.h"
#include "../modulo_gestire_azioni_semplici/gestire_azioni_semplici.h"
#define SCELTA_STAMPARE_REGOLE 1
#define SCELTA_STAMPARE_MANUALE 2

// Gestisce il menù di aiuto 
void gestire_menu_aiuto(char* percorso_file_menu_aiuto, char* percorso_file_regole_gioco, char* percorso_file_manuale_gioco);

#endif /* GESTIRE_AIUTO_H_ */
