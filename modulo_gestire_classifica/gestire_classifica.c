#include <stdbool.h>
#include <stdio.h>
#include "gestire_classifica.h"
#include "../modulo_gestire_file/gestire_file.h"
#include "../costanti.h"
#include "../modulo_creare_nuova_partita/creare_nuova_partita.h"
#include "../modulo_record_giocatore/record_giocatore.h"
#include "../modulo_record_vet_giocatori/record_vet_giocatori.h"
#include "../modulo_record_partita/record_partita.h"
#include "../modulo_record_percorso/record_percorso.h"
#define NUMERO_MASSIMO_CLASSIFICATI 10
#define TIRI_CLASSIFICATO_FINE -1
#define TITOLO_STAMPA_CLASSIFICA "Giocatori classificati:\n\0"
#define NUMERO_POSTO_CLASSIFICA "“Posto numero\0”"
#define NOME "nome: \0"
#define TIRI "tiri: \0"

void gestire_menu_classifica(char* NOME_FILE_MENU_CLASSIFICA,char* NOME_FILE_CLASSIFICA,char* STAMPARE_CLASSIFICA,char* USCIRE){
    int scelta;//scelta dell'utente tra le opzioni del menù
    FILE* classifica,//puntatore al file binario contenente la classifica
    *menu_classifica;//puntatore al file di testo contenente il menù relativo alla classifica

    //apertura del file binario contenente la classifica in modalità lettura
    classifica = fopen(NOME_FILE_CLASSIFICA, "rb");
    //apertura del file di testo contenente il menù relativo alla classifica in modalità lettura
    menu_classifica = fopen(NOME_FILE_MENU_CLASSIFICA, "r");

    if (verificare_file_esistente(classifica) && verificare_file_esistente(menu_classifica)){
        do
        {
            //stampare il menù
            stampare_file_di_testo(menu_classifica);
            //chiedere e attendere l'inserimento della scelta tra le opzioni del menù
            scelta = chiedere_intero(MESSAGGIO_SCELTA, 0, 1, 7, 0);
            if (scelta == STAMPARE_CLASSIFICA){
                //stampare a video la classifica
                stampare_classifica(classifica);
            }
        } while (scelta != USCIRE);
    }

    return;
}

void aggiornare_classifica(char* NOME_FILE_CLASSIFICA, record_partita partita, char* MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO, int NUMERO_MASSIMO_CLASSIFICATI){
    record_classificato classificati[NUMERO_MASSIMO_CLASSIFICATI], classificato;
    int dimensione = 0,//numero di giocatori classificati
        i = 0,//contatore dei giocatori classificati
        tiri,//numero di tiri del giocatore da classificare
        posizione;//posizione del nuovo giocatore nella classifica
    FILE* classifica;//puntatore al file contenente la classifica
    char nome[LUNGHEZZA_NOME + 1];//nome del giocatore che si deve registrare
    //aprire il file binario in modalità lettura
    classifica = fopen(NOME_FILE_CLASSIFICA, "rb");
    if (verificare_file_esistente(classifica) == true){
        // leggere dal file la classifica
        fread(&dimensione, sizeof(int), 1, classifica);
        fread(classificati, sizeof(record_classificato), dimensione, classifica);
        // chiudere il file
        fclose(classifica);
        // recuperare il numero di tiri del vincitore potenzialmente classificato
        tiri=recuperare_tiri_vincitore(partita);
        //controllare se il vincitore ha eseguito un numero di tiri tale che possa entrare nella classifica
        posizione = trovare_posizione_vincitore(classificati, tiri, dimensione, NUMERO_MASSIMO_CLASSIFICATI);

        if (posizione != -1){
            //chiedere il nome del nuovo classificato
            printf("%s", MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO);
            scanf("%s", nome);
            // scrivere il giocatore classificato come giocatore
            classificato = scrivere_nome_record_classificato(classificato, nome);
            classificato = scrivere_tiri_record_classificato(classificato, tiri);
            //inserire il giocatore nella classifica
            inserire_vincitore_in_classifica(classificati, dimensione, classificato, posizione, NUMERO_MASSIMO_CLASSIFICATI);
            //aggiornare il numero di classificati
            dimensione = aggiornare_dimensione_classifica(dimensione, NUMERO_MASSIMO_CLASSIFICATI);
            //aprire il file binario in modalità scrittura
            classifica = fopen(NOME_FILE_CLASSIFICA, "wb");
            // scrivere il numero di classificati nel file
            fwrite(&dimensione, sizeof(int), 1, classifica);
            fwrite(classificati, sizeof(record_classificato), dimensione, classifica);
        }
    }

    return;
}

int trovare_posizione_vincitore(record_classificato* classificati, int tiri, int dimensione, int NUMERO_MASSIMO_CLASSIFICATI){
    bool posizione_trovata = false;//posizione in cui inserire il vincitore nella classifica trovata
    int posizione = PRIMO_INDICE_ARRAY;//posizione in cui si verifica se il vincitore può essere inserito
    while (posizione < dimensione && posizione_trovata == false){
        //controllare se i tiri del vincitore sono maggiori dei tiri del classificato in una posizione
        if (tiri > leggere_tiri_record_classificato(classificati[posizione])){
            posizione = posizione + 1;
        } 
        else {
            posizione_trovata = true;
        }
    }
    if (posizione == NUMERO_MASSIMO_CLASSIFICATI){
        posizione = - 1;
    }
    return posizione;
}

int aggiornare_dimensione_classifica(int dimensione,int NUMERO_MASSIMO_CLASSIFICATI){
    //controllare se il numero dei classificati è inferiore a 10
    if (dimensione < NUMERO_MASSIMO_CLASSIFICATI - 1){
        dimensione = dimensione + 1;
    }

    return dimensione;
}

void inserire_vincitore_in_classifica(record_classificato* classificati, int numero_classificati,record_classificato classificato, int indice_classificato, int NUMERO_MASSIMO_CLASSIFICATI){
        int i;//contatore del numero di giocatori classificati
        //controllare se il numero dei classificati è già di 10
        if (numero_classificati == NUMERO_MASSIMO_CLASSIFICATI - 1){
            i = numero_classificati
        } 
        else {
            i = numero_classificati + 1;
        }

        while (i > indice_classificato)
        {
            //copiare il classificato di un posto in classifica e lo inserisce nel posto subito inferiore
            classificati[i] = inserire_record_classificato(classificati[i], classificati[i - 1]);
            i = i - 1;
        }
        //inserire il vincitore nella classifica
        classificati[i] = inserire_record_classificato(classificati[i], classificato);

        return;
}

int recuperare_tiri_vincitore(record_partita partita){
    int i = PRIMO_INDICE_ARRAY,//contatore del numero di giocatori analizzati
    tiri;//tiri effettuati dal vincitore
    bool trovato = false;//indica se il gicoatore vincitore è stato trovato
    while (i < NUMERO_MASSIMO_GIOCATORI && trovato == false){
        //controllare se la posizione del giocatore è uguale a quella della casella finale del percorso
        if (leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), i)) 
        == leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita))){
            trovato = true;
        }
        else {
            i = i + 1;
        }
    }
    //copiare il numero dei tiri del giocatore vincitore
    tiri = leggere_numero_dadi_lanciati_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), i));
    
    return tiri;
}

record_classificato copiare_record_classificato(record_classificato classificato_con_dati_da_copiare, record_classificato classificato_con_dati_da_inserire){
    //copia il nome di un classificato nell'altro classificato
    classificato_con_dati_da_copiare.nome_giocatore = classificato_con_dati_da_inserire.nome_giocatore;
    //copia il numero di tiri di un classificato
    scrivere_tiri_record_classifica(classificato_con_dati_da_copiare.tiri, classificato_con_dati_da_inserire.tiri);

    return classificato_con_dati_da_copiare;
}

void stampare_classifica(char* NOME_FILE_CLASSIFICA,char* TITOLO_STAMPA_CLASSIFICA,char* NUMERO_POSTO_CLASSIFICA){
    record_classificato classificati[NUMERO_MASSIMO_CLASSIFICATI], classificato;
    int i = PRIMO_INDICE_ARRAY,//contatore dei giocatori classificati
    numero_classificati;//numero di giocatori classificati
    FILE* classifica;//puntatore al file contenente la classifica

    //aprire il file binario in modalità lettura
    classifica = fopen(NOME_FILE_CLASSIFICA, "rb");

    if (verificare_file_esistente(classifica) == true){
        // leggere dal file la classifica
        fread(&numero_classificati, sizeof(int), 1, classifica);
        fread(classificati, sizeof(record_classificato), numero_classificati, classifica);
        
        printf("%s", TITOLO_STAMPA_CLASSIFICA);
        while (i < numero_classificati)
        {
            //stampare un giocatore di una posizione della classifica
            printf("%s%d: ", NUMERO_POSTO_CLASSIFICA, i + 1);
            stampare_giocatore_classificato(classificati[i]);
            i = i + 1;
        }
    }

    return;
}

void stampare_giocatore_classificato(record_classificato giocatore_classificato,char* NOME,char* TIRI){
    //stampare il nome di un classificato
    printf("%s%s ,", NOME, leggere_nome_giocatore_record_classificato(giocatore_classificato));
    //stampare il numero di tiri di un classificato
    printf("%s%d\n", TIRI, leggere_tiri_record_classificato(giocatore_classificato));

    return;
}
