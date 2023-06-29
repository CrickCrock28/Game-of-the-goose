#include "gestire_classifica.h"
#define TITOLO_STAMPA_CLASSIFICA "Giocatori classificati:\n\0"
#define NUMERO_POSTO_CLASSIFICA "Posto numero\0"
#define NOME "nome: \0"
#define TIRI "tiri: \0"

void gestire_menu_classifica(char* percorso_file_menu_classifica, char* percorso_file_classifica) {
    int scelta; // Scelta dell'utente tra le opzioni del menù

    do {
        // Stampare il menù
        system("cls");
	    spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
        stampare_file_di_testo(percorso_file_menu_classifica);
        // Chiedere e attendere l'inserimento della scelta tra le opzioni del menù
        scelta = chiedere_intero(MESSAGGIO_SCELTA, 0, 1, 7, 0);
        if (scelta == STAMPARE_CLASSIFICA) {
            // Stampare a video la classifica
            stampare_classifica(percorso_file_classifica);
        }
    } while (scelta != SCELTA_USCIRE_DAL_MENU);
    
    return;
}

void aggiornare_classifica(char* NOME_FILE_CLASSIFICA, record_partita partita) {
    record_classificato classificati[NUMERO_MASSIMO_CLASSIFICATI], classificato;
    int dimensione, // Numero di giocatori classificati
        tiri, // Numero di tiri del giocatore da classificare
        posizione; // Posizione del nuovo giocatore nella classifica
    FILE* classifica; // Puntatore al file contenente la classifica
    char nome[LUNGHEZZA_NOME + 1]; // Nome del giocatore che si deve registrare
    dimensione = PRIMO_INDICE_ARRAY;
    // Aprire il file binario in modalità lettura
    classifica = fopen(NOME_FILE_CLASSIFICA, "rb");
    
    //  leggere dal file la classifica
    fread(&dimensione, sizeof(int), 1, classifica);
    fread(classificati, sizeof(record_classificato), dimensione, classifica);
    // Chiudere il file
    fclose(classifica);
    // Recuperare il numero di tiri del vincitore potenzialmente classificato
    tiri=recuperare_tiri_vincitore(partita);
    // Controllare se il vincitore ha eseguito un numero di tiri tale che possa entrare nella classifica
    posizione = trovare_posizione_vincitore(classificati, tiri, dimensione);

    if (posizione != GIOCATORE_NON_CLASSIFICATO) {
        // Chiedere il nome del nuovo classificato
        printf("%s", MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO);
        scanf("%s", nome);
        // Scrivere il giocatore classificato come giocatore
        classificato = scrivere_nome_giocatore_record_classificato(classificato, nome);
        classificato = scrivere_tiri_record_classificato(classificato, tiri);
        // Inserire il giocatore nella classifica
        inserire_vincitore_in_classifica(classificati, dimensione, classificato, posizione);
        // Aggiornare il numero di classificati
        dimensione = aggiornare_dimensione_classifica(dimensione);
        // Aprire il file binario in modalità scrittura
        classifica = fopen(NOME_FILE_CLASSIFICA, "wb");
        // Scrivere il numero di classificati nel file
        fwrite(&dimensione, sizeof(int), 1, classifica);
        fwrite(classificati, sizeof(record_classificato), dimensione, classifica);
    }
    
    // Chiudere il file binario della classifica precedentemente aperto
    fclose(classifica);
    return;
}

int trovare_posizione_vincitore(record_classificato* classificati, int tiri, int dimensione) {
    bool posizione_trovata; // Posizione in cui inserire il vincitore nella classifica trovata
    int posizione; // Posizione in cui si verifica se il vincitore può essere inserito
    posizione_trovata = false;
    posizione = PRIMO_INDICE_ARRAY;
    if (tiri != GIOCATORE_NON_CLASSIFICATO) {
        while (posizione < dimensione && posizione_trovata == false) {
            // Controllare se i tiri del vincitore sono maggiori dei tiri del classificato in una posizione
            if (tiri > leggere_tiri_record_classificato(classificati[posizione])) {
                posizione = posizione + 1;
            } 
            else {
                posizione_trovata = true;
            }
        }
        if (posizione == NUMERO_MASSIMO_CLASSIFICATI) {
            posizione = GIOCATORE_NON_CLASSIFICATO;
        }
    }
    else {
        posizione = GIOCATORE_NON_CLASSIFICATO;
    }
    return posizione;
}

int aggiornare_dimensione_classifica(int dimensione) {
    // Controllare se il numero dei classificati è inferiore a 10
    if (dimensione < NUMERO_MASSIMO_CLASSIFICATI - 1) {
        dimensione = dimensione + 1;
    }

    return dimensione;
}

void inserire_vincitore_in_classifica(record_classificato* classificati, int numero_classificati, record_classificato classificato, int indice_classificato) {
        int i; // Contatore del numero di giocatori classificati
        // Controllare se il numero dei classificati è già di 10
        if (numero_classificati == NUMERO_MASSIMO_CLASSIFICATI - 1) {
            i = numero_classificati;
        } 
        else {
            i = numero_classificati + 1;
        }

        while (i > indice_classificato) {
            // Copiare il classificato di un posto in classifica e lo inserisce nel posto subito inferiore
            classificati[i] = copiare_record_classificato(classificati[i], classificati[i - 1]);
            i = i - 1;
        }
        // Inserire il vincitore nella classifica
        classificati[i] = copiare_record_classificato(classificati[i], classificato);

        return;
}

int recuperare_tiri_vincitore(record_partita partita) {
    int i, // Contatore del numero di giocatori analizzati
    tiri; // Tiri effettuati dal vincitore
    bool trovato; // Indica se il gicoatore vincitore è stato trovato
    trovato = false;
    i = PRIMO_INDICE_ARRAY;
    while (i < NUMERO_MASSIMO_GIOCATORI && trovato == false) {
        // Controllare se la posizione del giocatore è uguale a quella della casella finale del percorso
        if (leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), i)) 
        == leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita))) {
            trovato = true;
        }
        else {
            i = i + 1;
        }
    }
    if (trovato == false){
        tiri = GIOCATORE_NON_CLASSIFICATO;
    }
    else {
        // Copiare il numero dei tiri del giocatore vincitore
        tiri = leggere_numero_dadi_lanciati_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), i));
    }    
    return tiri;
}

record_classificato copiare_record_classificato(record_classificato classificato_con_dati_da_copiare, record_classificato classificato_con_dati_da_inserire) {
	char nome_classificato[LUNGHEZZA_NOME];

    // Copia il nome di un classificato nell'altro classificato
	leggere_nome_giocatore_record_classificato(classificato_con_dati_da_inserire, nome_classificato);
    classificato_con_dati_da_copiare = scrivere_nome_giocatore_record_classificato(classificato_con_dati_da_copiare, nome_classificato);
    // Copia il numero di tiri di un classificato
    classificato_con_dati_da_copiare = scrivere_tiri_record_classificato(classificato_con_dati_da_copiare, leggere_tiri_record_classificato(classificato_con_dati_da_inserire));

    return classificato_con_dati_da_copiare;
}

void stampare_classifica(char* percorso_file_classifica) {
    record_classificato classificati[NUMERO_MASSIMO_CLASSIFICATI];
    int i, // Contatore dei giocatori classificati
    numero_classificati; // Numero di giocatori classificati
    i = PRIMO_INDICE_ARRAY;
    FILE* classifica; // Puntatore al file binario contenente la classifica

    classifica = fopen(percorso_file_classifica, "rb");

    //  Leggere dal file la classifica
    fread(&numero_classificati, sizeof(int), 1, classifica);
    fread(classificati, sizeof(record_classificato), numero_classificati, classifica);
    printf("%s", TITOLO_STAMPA_CLASSIFICA);
    while (i < numero_classificati) {
        // Stampare un giocatore di una posizione della classifica
        printf("%s%d: ", NUMERO_POSTO_CLASSIFICA, i + 1);
        stampare_giocatore_classificato(classificati[i]);
        i = i + 1;
    }

    // Chiudere il file binario della classifica precedentemente aperto
    fclose(classifica);
    return;
}

void stampare_giocatore_classificato(record_classificato giocatore_classificato) {
    char nome[LUNGHEZZA_NOME + 1]; // Stringa che contiene il nome di un classificato da stampare
    // Leggere il nome di un classificato
    leggere_nome_giocatore_record_classificato(giocatore_classificato, nome);    
    // Stampare il nome di un classificato
    printf("%s%s ,", NOME, nome);
    // Stampare il numero di tiri di un classificato
    printf("%s%d\n", TIRI, leggere_tiri_record_classificato(giocatore_classificato));

    return;
}
