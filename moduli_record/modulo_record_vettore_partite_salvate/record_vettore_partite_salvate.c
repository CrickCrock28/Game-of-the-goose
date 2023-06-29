#include "record_vettore_partite_salvate.h"

int leggere_dimensione_record_vettore_partite_salvate(record_vettore_partite_salvate vettore_partite_salvate){
        int dim = vettore_partite_salvate.dimensione;
        return dim;
}

record_vettore_partite_salvate scrivere_dimensione_record_vettore_partite_salvate(record_vettore_partite_salvate vettore_partite_salvate, int dim){
     vettore_partite_salvate.dimensione = dim;
     return vettore_partite_salvate;
}

record_partita leggere_record_vettore_partite_salvate(record_vettore_partite_salvate vettore_partite_salvate, int indice){
        record_partita partita = vettore_partite_salvate.partite[indice];
        return partita;
}

record_vettore_partite_salvate scrivere_record_vettore_partite_salvate(record_vettore_partite_salvate vettore_partite_salvate, record_partita partita, int indice){
        vettore_partite_salvate.partite[indice] = partita;
        return vettore_partite_salvate;
}