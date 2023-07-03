// PERFETTO
#ifndef GESTIRE_AZIONI_SEMPLICI_H_
#define GESTIRE_AZIONI_SEMPLICI_H_


int ottenere_riga_cursore();
int ottenere_colonna_cursore();
int chiedere_intero(const char* messaggio, int valore_minimo, int valore_massimo, int x, int y);
int calcolare_proporzione(int n_1, int d_1, int d_2);
int generare_numero_casuale(int minimo, int massimo);
void stampare_riga_vuota(int riga, int numero_colonna_massima);


#endif
