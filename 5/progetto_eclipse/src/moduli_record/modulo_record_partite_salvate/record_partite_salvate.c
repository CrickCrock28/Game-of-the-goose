// PERFETTO
#include "record_partite_salvate.h"


#include <string.h>


void leggere_percorso_file_partite_salvate_record_partite_salvate(record_partite_salvate salvataggi, char* percorso_file) {
    memcpy(percorso_file, salvataggi.percorso_file, NUMERO_MASSIMO_CASELLE*sizeof(char));
    return;
}

record_partite_salvate scrivere_percorso_file_partite_salvate_record_partite_salvate(record_partite_salvate salvataggi, char* percorso_file) {
    memcpy(salvataggi.percorso_file, percorso_file, NUMERO_MASSIMO_CASELLE*sizeof(char));
    return salvataggi;
}

record_partita leggere_partita_opzionale_record_partite_salvate(record_partite_salvate salvataggi) {
    record_partita partita;
    partita = salvataggi.partita_opzionale;
    return partita;
}

record_partite_salvate scrivere_partita_opzionale_record_partite_salvate(record_partite_salvate salvataggi, record_partita partita) {
    salvataggi.partita_opzionale = partita;
    return salvataggi;
}


bool leggere_partita_presente_record_partite_salvate(record_partite_salvate salvataggi) {
	bool partita_presente;
	partita_presente = salvataggi.partita_presente;
    return partita_presente;
}

record_partite_salvate scrivere_partita_presente_record_partite_salvate(record_partite_salvate salvataggi, bool partita_presente) {
    salvataggi.partita_presente = partita_presente;
    return salvataggi;
}
