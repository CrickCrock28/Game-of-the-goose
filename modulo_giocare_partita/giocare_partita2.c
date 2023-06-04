#include <stdio.h>
#include <stdlib.h>
#include <funzioni_accesso_da_modificare.h>

#define NUMERO_MINIMO_CASELLE 1
#define NUMERO_MASSIMO_CASELLE 100
#define CASELLA_OCA 'O'
#define CASELLA_PONTE 'P'
#define CASELLA_LOCANDA 'L'
#define CASELLA_POZZO 'Z'
#define CASELLA_LABIRINTO 'A'
#define CASELLA_SCHELETRO 'S'
#define CASELLA_PRIGIONE 'G'
#define CASELLA_FINE 'F'
#define ARRIVO_LABIRINTO 42
#define NUMERO_MASSIMO_CASELLE 100
#define TURNI_BLOCCATO_LOCANDA

#define NUMERO_MASSIMO_GIOCATORI 4
#define PRIMO_INDICE_ARRAY 0
#define FALSO 0
#define VERO 1
#define PRIMA_POSIZIONE_PERCORSO 1
#define PERCORSO_FILE_MENU_PARTITA "menu_partita.txt"

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
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_pozzo(record_partita partita, int indice_giocatore){
    int trovato = FALSO;
    int i = PRIMO_INDICE_ARRAY;

    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    while(i<=NUMERO_MASSIMO_GIOCATORI && trovato = FALSO){
        giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, i);
        if(trovare_tipo_casella_giocatore(giocatore) = CASELLA_POZZO && leggere_bloccato_record_giocatore(giocatore) = VERO){
            giocatore = scrivere_bloccato__record_giocatore(giocatore, FALSO);
            vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, i, giocatore);
            trovato = VERO;
        }
        i=i+1;
    }
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    giocatore = scrivere_bloccato_record_giocatore(giocatore, VERO);
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_locanda(record_partita partita, int indice_giocatore){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    giocatore = scrivere_numero_turni_bloccato_record_giocatore(giocatore, TURNI_BLOCCATO_LOCANDA);
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_finale(record_partita partita, int indice_giocatore){

    partita = scrivere_terminata_record_partita(partita, VERO);

    return partita;
}



