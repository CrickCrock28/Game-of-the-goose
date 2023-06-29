#ifndef RECORD_PERCORSO_H_
#define RECORD_PERCORSO_H_

typedef struct {
    int dimensione;
    char caselle[90];
} record_percorso;

int leggere_dimensione_record_percorso(record_percorso percorso) ;
char leggere_casella_record_percorso(record_percorso percorso, int indice) ;
record_percorso scrivere_dimensione_record_percorso(record_percorso percorso, int nuova_dimensione) ;
record_percorso scrivere_casella_record_percorso(record_percorso percorso, int indice, char nuova_casella) ;

#endif /* RECORD_PERCORSO */