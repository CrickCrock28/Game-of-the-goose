#include "record_partite_salvate.h"

void leggere_percorso_file_partite_salvate(record_partite_salvate salvataggi, char* percorso_file){
    memcpy(percorso_file, salvataggi.percorso_file, DIMENSIONE_MASSIMA_PERCORSO*sizeof(char));
    return;
}

record_partite_salvate scrivere_percorso_file_partite_salvate(record_partite_salvate salvataggi, char* percorso_file){
    memcpy(salvataggi.percorso_file, percorso_file, DIMENSIONE_MASSIMA_PERCORSO*sizeof(char));
    return salvataggi;
}

record_partita leggere_partita_opzionale(record_partite_salvate salvataggi){
    record_partita partita;
    partita = salvataggi.partita_opzionale;
    return partita;
}

record_partite_salvate scrivere_partita_opzionale(record_partite_salvate salvataggi, record_partita partita){
    salvataggi.partita_opzionale = partita;
    return salvataggi;
}
