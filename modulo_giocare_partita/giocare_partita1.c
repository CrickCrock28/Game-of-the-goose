#include <stdio.h>
#include <stdlib.h>
#include <funzioni_accesso_da_modificare.h>

//TUTTE LE COSTANTI SONO FA RIVEDERE

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
#define ARRIVO_LABIRINTO 999
#define TURNI_BLOCCATO_LOCANDA 999
#define NUMERO_MASSIMO_GIOCATORI 4
#define PRIMO_INDICE_ARRAY 0
#define PRIMA_POSIZIONE_PERCORSO 1
#define PERCORSO_FILE_MENU_PARTITA "menu_partita.txt"
#define ARRIVO_PRIMO_LANCIO_4_5 2
#define ARRIVO_PRIMO_LANCIO_3_6 3
#define NUMERO_MINIMO_DADO 1
#define NUMERO_MASSIMO_DADO 6
#define FALSO 0
#define VERO 1

char tipo_casella(record_partita partita, int indice_giocatore) {
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    record_percorso percorso;
    int numero_casella;
    char tipo_casella;

    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    numero_casella = leggere_posizione_record_giocatore(giocatore);
    percorso = leggere_percorso_record_partita(partita);
    tipo_casella = leggere_casella_record_percorso(percorso, numero_casella);

    return tipo_casella;
}

record_partita applicare_effetto_casella_labirinto(record_partita partita, int indice_giocatore) {
    
    record_percorso percorso;
    int dimensione_percorso;
    int nuova_posizione;
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    percorso = leggere_percorso_record_partita(partita);
    dimensione_percorso = leggere_dimensione_record_percorso(percorso);
    nuova_posizione = calcolare_proporzione(ARRIVO_LABIRINTO, NUMERO_MASSIMO_CASELLE, dimensione_percorso);
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_prigione(record_partita partita, int indice_giocatore) {
    
    int i;
    int trovato;
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    trovato = FALSO;
    i = PRIMO_INDICE_ARRAY;
    while (i < NUMERO_MASSIMO_GIOCATORI && !trovato) {
        giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, i);

        if (trovare_tipo_casella_giocatore(giocatore) == CASELLA_PRIGIONE && leggere_bloccato_record_giocatore(giocatore)) {
            giocatore = scrivere_bloccato_record_giocatore(giocatore, FALSO);
            vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, i, giocatore);
            trovato = VERO;
        }

        i++;
    }

    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    giocatore = scrivere_bloccato_record_giocatore(giocatore, VERO);
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);

    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_scheletro(record_partita partita, int indice_giocatore) {
    
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

    giocatore = scrivere_posizione_record_giocatore(giocatore, PRIMA_POSIZIONE_PERCORSO);

    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);

    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita giocare_partita(record_partita partita) {

    int indice_giocatore_di_turno;
    int scelta;

    if (!verificare_partita_iniziata(partita)) {
        partita = stabilire_primo_giocatore(partita);
    }

    while (!leggere_terminata_record_partita(partita) &&
           !leggere_nuova_partita_record_partita(partita) &&
           !leggere_abbandona_partita_record_partita(partita) &&
           !leggere_salvare_partita_record_partita(partita)) {
        indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
        stampare_file_di_testo(PERCORSO_FILE_MENU_PARTITA);
        scelta = chiedere_intero("Inserisci la scelta: ", 0, 3);    //DA RIVEDERE
        partita = gestire_scelta_partita(partita, scelta);          //DA RIVEDERE
    }

    return partita;
}

record_partita lanciare_primi_dadi(record_partita partita, int indice_giocatore) {
    
    int dado_1;
    int dado_2;
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    int dimensione_percorso;

    dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);      //DA RIVEDERE
    dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);      //DA RIVEDERE
    
    partita = scrivere_ultimo_lancio_dado_1_record_partita(partita, dado_1);
    partita = scrivere_ultimo_lancio_dado_2_record_partita(partita, dado_2);

    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

    if (dado_1 == 5 && dado_2 == 4) {
        giocatore = scrivere_posizione_record_giocatore(giocatore, calcolare_proporzione(ARRIVO_PRIMO_LANCIO_4_5, NUMERO_MASSIMO_CASELLE, dimensione_percorso));
    }
    else if (dado_1 == 6 && dado_2 == 3) {
        giocatore = scrivere_posizione_record_giocatore(giocatore, calcolare_proporzione(ARRIVO_PRIMO_LANCIO_3_6, NUMERO_MASSIMO_CASELLE, dimensione_percorso));
    }
    else {
        giocatore = scrivere_posizione_record_giocatore(giocatore, dado_1 + dado_2);
    }
    
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita avanzare_turno(record_partita partita) {
    int indice_successivo;
    
    indice_successivo = leggere_indice_giocatore_di_turno(partita) + 1;

    if (indice_successivo > leggere_dimensione_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita))) {
        indice_successivo = PRIMO_INDICE_ARRAY;
    }

    partita = scrivere_indice_giocatore_di_turno_record_partita(partita, indice_successivo);

    return partita;
}

record_partita stabilire_primo_giocatore(record_partita partita) {
    int dado_1;
    int dado_2;
    int massimo_lancio_dadi;
    int indice_inizio;
    int i;
    
    indice_inizio = PRIMO_INDICE_ARRAY;
    dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
    dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
    massimo_lancio_dadi = dado_1 + dado_2;

    i = PRIMO_INDICE_ARRAY + 1;
    while (i <= leggere_dimensione_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita))) {
        dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
        dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);

        if (massimo_lancio_dadi > dado_1 + dado_2) {
            massimo_lancio_dadi = dado_1 + dado_2;
            indice_inizio = i;
        }

        i++;
    }

    partita = scrivere_indice_giocatore_di_turno_record_partita(partita, indice_inizio);

    return partita;
}

record_partita gestire_menu_nuova_partita(const char* menu_nuova_partita, const char* menu_partita_in_corso, int riprendere_partita) {
    int nuova_partita;
    int scelta;
    record_partita partita;
    
    nuova_partita = FALSO;
    do {
        if (nuova_partita) {
            partita = gestire_scelta_nuova_partita(scelta); //DA RIVEDERE
        } else {
            if (riprendere_partita == 0) {
                stampare_file_di_testo(PERCORSO_FILE_MENU_PARTITA);
                scelta = chiedere_intero("Inserisci la scelta: ", 0, 1); //DA RIVEDERE
                partita = gestire_scelta_nuova_partita(scelta); //DA RIVEDERE
            } else {
                partita = giocare_partita(partita); //DA RIVEDERE
            }
        }

        if (leggere_nuova_partita_record_partita(partita)) {
            nuova_partita = VERO;
        } else {
            if (leggere_abbandona_partita_record_partita(partita) == FALSO) {
                scelta = 0;
            }
        }
    } while (scelta != 0);

    return partita;
}