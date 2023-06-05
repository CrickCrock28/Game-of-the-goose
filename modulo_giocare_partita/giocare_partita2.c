#include <stdio.h>
#include <stdlib.h>
#include <funzioni_accesso_da_modificare.h>

//TUTTE LE COSTANTI SONO DA RIVEDERE
#define NUMERO_MINIMO_CASELLE 1
#define NUMERO_MASSIMO_CASELLE 100
#define CASELLA_OCA '1'
#define CASELLA_PONTE '1'
#define CASELLA_LOCANDA '1'
#define CASELLA_POZZO '1'
#define CASELLA_LABIRINTO '1'
#define CASELLA_SCHELETRO '1'
#define CASELLA_PRIGIONE '1'
#define CASELLA_FINALE '90'
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

    while(i<=NUMERO_MASSIMO_GIOCATORI && trovato == FALSO){
        giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, i);
        if(trovare_tipo_casella_giocatore(giocatore) == CASELLA_POZZO && leggere_bloccato_record_giocatore(giocatore) = VERO){
            giocatore = scrivere_bloccato_record_giocatore(giocatore, FALSO);
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


record_partita lanciare_dadi(record_partita partita, int indice_giocatore){
    int dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
    int dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
    int dimensione_percorso;
    int vecchia_posizione;
    int nuova_posizione;
    int somma_dadi=dado_1+dado_2;

    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    partita = scrivere_ultimo_lancio_dado_1_record_partita(partita, dado_1);
    partita = scrivere_ultimo_lancio_dado_2_record_partita(partita, dado_2);
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    
    if((leggere_bloccato_record_giocatore(giocatore) == FALSO) || (leggere_bloccato_record_giocatore(giocatore) == VERO && ( somma_dadi== 5 || somma_dadi= = 7))){
        dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));
        vecchia_posizione = leggere_posizione_record_giocatore(giocatore);
        nuova_posizione = vecchia_posizione + dado_1 + dado_2;
        if(nuova_posizione > dimensione_percorso){
        nuova_posizione = dimensione_percorso - (nuova_posizione - dimensione_percorso);
        }
    }else{
        giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
        vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
        partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);
    }
    return partita;
}


int calcolare_resto(int dividendo, int divisore){
    int resto = dividendo;
    while (resto >= divisore){
        resto = resto - divisore;
    }
    return resto;
}


record_partita gestire_effetti_caselle_speciali(record_partita partita, int indice_giocatore){
    if (trovare_tipo_casella_giocatore(partita, indice_giocatore)  == CASELLA_OCA || trovare_tipo_casella_giocatore(partita, indice_giocatore) = CASELLA_PONTE){
        partita = applicare_effetto_casella_oca_ponte(partita, indice_giocatore)
        }else{
            if(trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_LABIRINTO){
                partita = applicare_effetto_casella_labirinto(partita, indice_giocatore);
                }else{
                    if(trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_POZZO){
                        partita = applicare_effetto_casella_pozzo(partita, indice_giocatore);
                        }else{
                            if (trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_PRIGIONE){
                                
                                partita = applicare_effetto_casella_prigione(partita, indice_giocatore);}else{  
                                    if(trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_LOCANDA){partita = applicare_effetto_casella_locanda(partita, indice_giocatore);
                                    }else{ 
                                        if(trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_SCHELETRO){
                                            partita = applicare_effetto_casella_scheletro(partita, indice_giocatore);
                                            }else{
                                                if (trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_FINALE){
                                                }else{
                                                    partita = applicare_effetto_casella_finale(partita);
                                                }
                                            }
                                    }
                                }
                        }
                    }
            }
    return partita;
}


record_partita gestire_scelta_partita(record_partita partita, int scelta){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    int indice_giocatore_di_turno;

    if(scelta == 1){
        // tira i dadi, potrebbe terminare la partita
        vet_giocatori = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);
    }
}






