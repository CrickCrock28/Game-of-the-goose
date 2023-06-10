#include "record_partite_salvate.h"
#include "record_partita.h"

FILE* leggere_file_partite_salvate(record_partite_salvate salvataggi){
    FILE* file_salvataggi;
    file_salvataggi = salvataggi.file_partite_salvate;
    return file_salvataggi;
}

void scrivere_file_partite_salvate(record_partite_salvate* salvataggi, FILE file_salvataggi){
    salvataggi.file_partite_salvate = file_salvataggi;
}

record_partita leggere_partita_opzionale(record_partite_salvate salvataggi){
    record_partita partita;
    partita = salvataggi.partita_opzionale;
    return partita;
}

void scrivere_partita_opzionale(record_partite_salvate* salvataggi, record_partita partita){
    salvataggi.partita_opzionale = partita;
}