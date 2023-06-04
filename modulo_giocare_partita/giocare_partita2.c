#include <stdio.h>
#include <stdlib.h>
#include <funzioni_accesso_da_modificare.h>

record_partita applicare_effetto_casella_oca_ponte(record_partita partita, int indice_giocatore){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    int ultimo_lancio_dadi;
    int posizione;

    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    posizione = leggere_posizione_record_giocatore(giocatore);
    ultimo_lancio_dadi = leggere_ultimo_lancio_dado_1_record_partita(partita) + leggere_ultimo_lancio_dado_2_record_partita(partita);
    giocatore = scrivere_posizione_record_giocatore(giocatore, posizione + ultimo_lancio_dadi);
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_record_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}