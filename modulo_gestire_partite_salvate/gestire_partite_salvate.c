#include "gestire_partite_salvate.h"

#include "..\\percorsi_file.h"

#define SCELTA_ESCI 0
#define SCELTA_CANCELLA_PARTITA 1
#define SCELTA_CARICA_PARTITA 2

#define NUMERO_MASSIMO_PARTITE_SALVATE 5
#define MESSAGGIO_SCELTA_MENU "Inserire un intero che rappresenta la scelta"
#define MESSAGGIO_CANCELLARE_PARTITA "Inserisci il numero della partita da cancellare per poter salvare la partita corrente (oppure 0 se non vuoi salvare): "
#define MESSAGGIO_MENU "Inserisci il numero corrispondente all'azione da eseguire: " //FORSE PUO' ESSERE TRASFORMATA IN GLOBALE

#define MESSAGGIO_PARTITA_SALVATA "La partita in corso e' stata salvata"
#define MESSAGGIO_PARTITA_CANCELLATA "La partita %d e' stata cancellata"

record_partite_salvate gestire_menu_partite_salvate(record_partite_salvate salvataggi, char* percorso_file_menu_carica_partita){
    int scelta, numero_partita, riga, numero_partite_salvate;
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

        // Controlla quante partite ci sono sul file
        numero_partite_salvate = contare_partite_salvate(percorso_file_partite_salvate);

        // Se ci sono partite sul file
        if(numero_partite_salvate > 0){

        	// Se l'utente vuole cancellare una partita
			if(scelta == SCELTA_CANCELLA_PARTITA){
				// Chiede il numero della partita da cancellare e la cancella
				numero_partita = chiedere_intero("Inserisci il numero corrispondente alla partita da cancellare (oppure 0 se non vuoi cancellare nessuna parita): ", SCELTA_USCIRE_DAL_MENU, numero_partite_salvate, riga, PRIMA_COORDINATA_SCHERMO);
				cancellare_partita_da_file(percorso_file_partite_salvate, numero_partita);
				system("pause");
				} else {
					// Altrimenti, se l'utente vuole caricare una partita
					if(scelta == SCELTA_CARICA_PARTITA){
						// Chiede il numero della partita da caricare e la carica
						numero_partita = chiedere_intero("Inserisci il numero corrispondente alla partita da caricare (oppure 0 se non vuoi caricare nessuna parita): ", SCELTA_USCIRE_DAL_MENU, numero_partite_salvate,  riga, PRIMA_COORDINATA_SCHERMO);
						partita_scelta = leggere_partita_scelta(percorso_file_partite_salvate, numero_partita);
					}
				}
        } else {
        	printf("Non ci sono partite salvate");
        	printf("\n");
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

    fclose(file_partite_salvate);

    return partita_scelta;
}

void salvare_partita(char* percorso_file_partite_salvate, record_partita partita){
    int numero_partite_salvate, numero_partita_da_cancellare, riga;

    // Ottiene il numero di partite salvate sul file
    numero_partite_salvate = contare_partite_salvate(percorso_file_partite_salvate);
    
    // Se il file dei salvataggi è pieno
    if(numero_partite_salvate == NUMERO_MASSIMO_PARTITE_SALVATE){
        // Stampa le partite salvate e chiede quale cancellare
        riga = stampare_partite_salvate(percorso_file_partite_salvate);
        numero_partita_da_cancellare = chiedere_intero(MESSAGGIO_CANCELLARE_PARTITA, SCELTA_USCIRE_DAL_MENU, NUMERO_MASSIMO_PARTITE_SALVATE, riga, PRIMA_COORDINATA_SCHERMO);
        
        // Se l'utente sceglie di cancellare una partita per poter salvare quella in corso
        if(numero_partita_da_cancellare != 0){
            // Cancella la partita scelta e aggiunge la nuova partita
            cancellare_partita_da_file(percorso_file_partite_salvate, numero_partita_da_cancellare);
            printf("\n");
            aggiungere_partita_su_file(percorso_file_partite_salvate, partita);
            printf(MESSAGGIO_PARTITA_SALVATA);
            printf("\n");
        }
    }else{
        // Salva la partita sul file
        aggiungere_partita_su_file(percorso_file_partite_salvate, partita);
        printf(MESSAGGIO_PARTITA_SALVATA);
        printf("\n");
    }

    return;
}

int stampare_partite_salvate(char* percorso_file_partite_salvate){
    FILE* file_partite_salvate;
    int numero_partita, numero_giocatore, posizione_giocatore, righe_utilizzate;
    record_partita partita;

    // Stampa il titolo
	system("cls");
	spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
    righe_utilizzate = stampare_file_di_testo(PERCORSO_FILE_TITOLO);

    file_partite_salvate = fopen(percorso_file_partite_salvate, "rb");

    // Stampa le partite salvate
    numero_partita = 1;
    while (fread(&partita, sizeof(record_partita), 1, file_partite_salvate) == 1) { // Legge una partita per volta dal file

        // Stampa i dati della partita
        printf("- Partita %d:\n", numero_partita);
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
        numero_partita++;
    }

    fclose(file_partite_salvate);

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
    file_temporaneo = fopen(PERCORSO_FILE_BINARIO_TEMPORANEO, "wb");

    numero_partite = 0;
    
    while (fread(&partita, sizeof(record_partita), 1, file_partite_salvate) == 1) {
        numero_partite++;
        
        if (numero_partite != numero_partita) {
            fwrite(&partita, sizeof(record_partita), 1, file_temporaneo);
        } else {
            printf(MESSAGGIO_PARTITA_CANCELLATA, numero_partita);
            printf("\n");
        }
    }
    
    fclose(file_partite_salvate);
    fclose(file_temporaneo);

    remove(percorso_file_partite_salvate);
    rename(PERCORSO_FILE_BINARIO_TEMPORANEO, percorso_file_partite_salvate);

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
