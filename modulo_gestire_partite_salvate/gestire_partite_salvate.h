#ifndef GESTIRE_PARTITE_SALVATE_H_
#define GESTIRE_PARTITE_SALVATE_H_

record_menu_partite_salvate gestire_menu_partite_salvate(int scelta, record_partite_salvate salvataggi, int numero_partita, const char* menu_carica_partita);
record_partita leggere_partita_scelta(FILE* file_partite_salvate, int numero_partite);
FILE* salvare_partita(FILE* file_partite_salvate, record_partita partita);
int stampare_partite_salvate(FILE* file_partite_salvate); 
FILE* cancellare_partita_da_file(FILE* file_partite_salvate, int numero_partita);
record_vettore_partite_salvate rimuovere_partita_da_vettore(record_vettore_partite_salvate vettore_partite_salvate, int indice_elemento_da_rimuovere);

#endif /* GESTIRE_PARTITE_SALVATE_H_ */