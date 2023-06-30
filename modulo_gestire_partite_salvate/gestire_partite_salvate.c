#include "gestire_partite_salvate.h" 

record_partite_salvate gestire_menu_partite_salvate(record_partite_salvate salvataggi, char* percorso_file_menu_carica_partita){
    int scelta, numero_partita, riga;
    record_partita partita_scelta;
    char percorso_file_partite_salvate[DIMENSIONE_MASSIMA_PERCORSO_FILE];

    do{
        // Stampa il menu e chiede l'azione da eseguire
    	system("cls");
    	spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
        riga = stampare_file_di_testo(percorso_file_menu_carica_partita);
        scelta = chiedere_intero(MESSAGGIO_MENU, SCELTA_USCIRE_DAL_MENU, SCELTA_CARICA_PARTITA, (riga+1), PRIMA_COORDINATA_SCHERMO);

        // Stampa le partite salvate
        leggere_percorso_file_partite_salvate(salvataggi, percorso_file_partite_salvate);
        riga = stampare_partite_salvate(percorso_file_partite_salvate);
        
        if(scelta == SCELTA_CANCELLA_PARTITA){ 
            // L'utente vuole cancellare una partita salvata
            numero_partita = chiedere_intero("Inserisci il numero corrispondente alla partita da cancellare: ", SCELTA_USCIRE_DAL_MENU, SCELTA_CARICA_PARTITA, (riga+1), PRIMA_COORDINATA_SCHERMO);
            cancellare_partita_da_file(percorso_file_partite_salvate, numero_partita);

            } else {
                if(scelta == SCELTA_CARICA_PARTITA){ 
                    //L'utente vuole caricare una partita salvata
                    numero_partita = chiedere_intero("Inserisci il numero corrispondente alla partita da caricare: ", SCELTA_USCIRE_DAL_MENU, SCELTA_CARICA_PARTITA,  (riga+1), PRIMA_COORDINATA_SCHERMO);
                    partita_scelta = leggere_partita_scelta(percorso_file_partite_salvate, numero_partita);
                }
            }

    }while(scelta != SCELTA_ESCI);

    return salvataggi;
}

int contare_partite_salvate(char* percorso_file_partite_salvate) { // DA AGGIUNGERE IN PSEUDO

    int dimensione;
    int numero_partite_salvate;

    FILE* file = fopen(percorso_file_partite_salvate, "rb");    
    fseek(file, 0, SEEK_END);
    dimensione = ftell(file);
    fclose(file);

    numero_partite_salvate = dimensione / sizeof(record_partita);

    return numero_partite_salvate;
}

void aggiungere_partita_su_file(char* percorso_file_partite_salvate, record_partita partita){ // DA AGGIUNGERE IN PSEUDO
    FILE* file_partite_salvate;
    
    file_partite_salvate = fopen(percorso_file_partite_salvate, "ab");
    fwrite(&partita, sizeof(record_partita), 1, file_partite_salvate);
    fclose(file_partite_salvate);

    return;
}

record_partita leggere_partita_scelta(char* percorso_file_partite_salvate, int numero_partita){
    int posizione;
    record_partita partita_scelta;
    FILE* file_partite_salvate;

    file_partite_salvate = fopen(percorso_file_partite_salvate, "rb");

    // Calcola la posizione all'interno del file in base al numero_partite
    posizione = (numero_partita - 1) * sizeof(record_partita);
    
    // Sposta il puntatore del file alla posizione corretta
    fseek(file_partite_salvate, posizione, SEEK_SET);
    
    // Leggi la partita dal file
    fread(&partita_scelta, sizeof(record_partita), 1, file_partite_salvate);

    return partita_scelta;
}

void salvare_partita(char* percorso_file_partite_salvate, record_partita partita){
    int numero_partite_salvate;
    int numero_partita_da_cancellare;

    numero_partite_salvate = contare_partite_salvate(percorso_file_partite_salvate);
    
    if(numero_partite_salvate == NUMERO_MASSIMO_PARTITE_SALVATE){// Il file dei salvataggi è pieno
        // Stampa le partite salvate e chiede quale cancellare
        stampare_partite_salvate(percorso_file_partite_salvate);
        numero_partita_da_cancellare = chiedere_intero(MESSAGGIO_CANCELLARE_PARTITA, 0, 5, (numero_partite_salvate*2+1), 0);
        
        if(numero_partita_da_cancellare != 0){ // L'utente ha scelto di cancellare una partita per poter salvare quella in corso
            // Cancella la partita scelta e aggiunge la nuova partita
            cancellare_partita_da_file(percorso_file_partite_salvate, numero_partita_da_cancellare);
            aggiungere_partita_su_file(percorso_file_partite_salvate, partita);
        }
    }else{
        // Aggiunge la partita al file
        aggiungere_partita_su_file(percorso_file_partite_salvate, partita);
    }
    return;
}

int stampare_partite_salvate(char* percorso_file_partite_salvate){
    FILE* file_partite_salvate;
    int numero_partita, numero_giocatore, posizione_giocatore, righe_utilizzate;
    record_partita partita;

    file_partite_salvate = fopen(percorso_file_partite_salvate, "rb");

    // Stampa le partite salvate
    righe_utilizzate = 0;
    numero_partita = 1;
    while (fread(&partita, sizeof(record_partita), 1, file_partite_salvate) == 1) { // Legge una partita per volta dal file

        // Stampa i dati della partita
        printf("Partita %d:\n", numero_partita);
        printf("Dimensione del percorso: %d\n", leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita)));
        righe_utilizzate = righe_utilizzate + 2;

        // Stampa i dati dei giocatori
        numero_giocatore = PRIMO_INDICE_ARRAY;
        while(numero_giocatore < NUMERO_MASSIMO_GIOCATORI){
            posizione_giocatore = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), numero_giocatore));
            if(posizione_giocatore != POSIZIONE_GIOCATORE_NON_PARTECIPANTE){
                printf("Posizione giocatore %d: %d\n", (numero_giocatore+1), posizione_giocatore);
                righe_utilizzate++;
            }
            numero_giocatore++;
        }
        printf("\n");
        righe_utilizzate++;
        numero_partita++;
    }

    if(righe_utilizzate == 0) {
        printf("Non ci sono partite salvate\n");
        righe_utilizzate++;
    }

    return righe_utilizzate;
}

void cancellare_partita_da_file(char* percorso_file_partite_salvate, int numero_partita) {
    
    FILE *file_partite_salvate, *file_temporaneo;        
    record_partita partita;
    int numero_partite;

    file_partite_salvate = fopen(percorso_file_partite_salvate, "rb");
    file_temporaneo = fopen(PERCORSO_FILE_BINARIO_REMPORANEO, "wb");

    numero_partite = 0;
    
    while (fread(&partita, sizeof(record_partita), 1, file_partite_salvate) == 1) {
        numero_partite++;
        
        if (numero_partite != numero_partita) {
            fwrite(&partita, sizeof(record_partita), 1, file_temporaneo);
        }
    }
    
    fclose(file_partite_salvate);
    fclose(file_temporaneo);
    
    remove(percorso_file_partite_salvate);
    rename(PERCORSO_FILE_BINARIO_REMPORANEO, percorso_file_partite_salvate);
}

/* NON PENSO SERVA
record_vettore_partite_salvate rimuovere_partita_da_vettore(record_vettore_partite_salvate vettore_partite_salvate, int indice_elemento_da_rimuovere){
    int i;

    i = indice_elemento_da_rimuovere;
    while(i<=(leggere_dimensione_record_vettore_partite_salvate(vettore_partite_salvate)-1)){
        vettore_partite_salvate = scrivere_record_vettore_partite_salvate(vettore_partite_salvate , leggere_record_vettore_partite_salvate(vettore_partite_salvate, i+1), i);
        i = i + 1;
    }
    vettore_partite_salvate = scrivere_dimensione_record_vettore_partite_salvate(vettore_partite_salvate, leggere_dimensione_record_vettore_partite_salvate(vettore_partite_salvate)-1);
    return vettore_partite_salvate;
}
*/
