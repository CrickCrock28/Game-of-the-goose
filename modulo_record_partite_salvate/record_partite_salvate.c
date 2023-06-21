#include "record_partite_salvate.h"

FILE* leggere_file_partite_salvate(record_partite_salvate salvataggi){
    FILE* file_salvataggi;
    file_salvataggi = salvataggi.file_partite_salvate;
    return file_salvataggi;
}

record_partite_salvate scrivere_file_partite_salvate(record_partite_salvate salvataggi, FILE* file_salvataggi){
    salvataggi.file_partite_salvate = file_salvataggi;
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