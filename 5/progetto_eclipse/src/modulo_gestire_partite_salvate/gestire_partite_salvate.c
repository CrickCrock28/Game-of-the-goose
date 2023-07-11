// PERFETTO
#include "gestire_partite_salvate.h"


#include <stdlib.h>
#include <stdio.h>

#include "..\\costanti.h"
#include "..\\percorsi_file.h"

#include "..\\modulo_gestire_file\\gestire_file.h"
#include "..\\modulo_gestire_azioni_semplici\\gestire_azioni_semplici.h"
#include "..\\modulo_spostare_cursore\\spostare_cursore.h"


#define MESSAGGIO_SOVRASCRIVERE_PARTITA "Inserisci il numero della partita da cancellare per poter salvare la partita\ncorrente (oppure 0 se non vuoi salvare nessuna partita): "
#define MESSAGGIO_CANCELLARE_PARTITA "Inserisci il numero corrispondente alla partita da cancellare (oppure 0 se non\nvuoi cancellare nessuna parita): "
#define MESSAGGIO_CARICARE_PARTITA "Inserisci il numero corrispondente alla partita da caricare (oppure 0 se non\nvuoi caricare nessuna parita): "
#define MESSAGGIO_PARTITA_SALVATA "La partita in corso e' stata salvata"
#define MESSAGGIO_PARTITA_CANCELLATA "La partita numero %d e' stata cancellata"

#define MESSAGGIO_NUMERO_PARTITA "- Partita %d:"
#define MESSAGGIO_DIMENSIONE_PERCORSO "Dimensione del percorso: %d"
#define MESSAGGIO_POSIZIONE_GIOCATORE "Posizione giocatore %d: %d"
#define MESSAGGIO_GIOCATORE_NON_PRESENTE "Giocatore %d: non presente"
#define MESSAGGIO_NESSUNA_PARTITA_SALVATA "Non ci sono partite salvate"

#define COLONNA_STAMPA_PARTITE_PARI 40

#define SCELTA_CANCELLA_PARTITA 1
#define SCELTA_CARICA_PARTITA 2

#define NUMERO_MASSIMO_PARTITE_SALVATE 5


int contare_partite_salvate(char* percorso_file_partite_salvate);
void aggiungere_partita_su_file(char* percorso_file_partite_salvate, record_partita partita);
record_partita leggere_partita_scelta(char* percorso_file_partite_salvate, int numero_partita);
void stampare_partite_salvate(char* percorso_file_partite_salvate);
void cancellare_partita_da_file(char* percorso_file_partite_salvate, int numero_partita_da_cancellare);


record_partite_salvate gestire_menu_partite_salvate(record_partite_salvate salvataggi, char* percorso_file_menu_partite_salvate) {
    int scelta, numero_partita, riga, numero_partite_salvate;
    record_partita partita_scelta;
    char percorso_file_partite_salvate[DIMENSIONE_MASSIMA_PERCORSO_FILE];

    salvataggi = scrivere_partita_presente_record_partite_salvate(salvataggi, false);

    do {
        // Stampa il menu e chiede l'azione da eseguire
    	system("cls");
    	spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
        stampare_file_di_testo(percorso_file_menu_partite_salvate);
        riga = ottenere_riga_cursore();
        scelta = chiedere_intero(MESSAGGIO_SCELTA_AZIONE_MENU, SCELTA_USCIRE_DAL_MENU, SCELTA_CARICA_PARTITA, riga, PRIMA_COORDINATA_SCHERMO);

        // Stampa le partite salvate
        leggere_percorso_file_partite_salvate_record_partite_salvate(salvataggi, percorso_file_partite_salvate);
        stampare_partite_salvate(percorso_file_partite_salvate);
        riga = ottenere_riga_cursore();

        // Controlla quante partite ci sono sul file
        numero_partite_salvate = contare_partite_salvate(percorso_file_partite_salvate);

        // Se ci sono partite sul file
        if (numero_partite_salvate > 0) {

        	// Se l'utente vuole cancellare una partita
			if (scelta == SCELTA_CANCELLA_PARTITA) {
				// Chiede il numero della partita da cancellare e la cancella
				numero_partita = chiedere_intero(MESSAGGIO_CANCELLARE_PARTITA, SCELTA_USCIRE_DAL_MENU, numero_partite_salvate, riga, PRIMA_COORDINATA_SCHERMO);
				if (numero_partita != SCELTA_USCIRE_DAL_MENU) {
					cancellare_partita_da_file(percorso_file_partite_salvate, numero_partita);
				}
				printf("%c", CARATTERE_NUOVA_RIGA);
				system("pause");
				}
                else {
					// Altrimenti, se l'utente vuole caricare una partita
					if (scelta == SCELTA_CARICA_PARTITA) {
						// Chiede il numero della partita da caricare
						numero_partita = chiedere_intero(MESSAGGIO_CARICARE_PARTITA, SCELTA_USCIRE_DAL_MENU, numero_partite_salvate,  riga, PRIMA_COORDINATA_SCHERMO);
						// Se l'utente non ha inserito la scelta per uscire dal menu
						if (numero_partita != SCELTA_USCIRE_DAL_MENU) {
							partita_scelta = leggere_partita_scelta(percorso_file_partite_salvate, numero_partita);
							salvataggi = scrivere_partita_opzionale_record_partite_salvate(salvataggi, partita_scelta);
							salvataggi = scrivere_partita_presente_record_partite_salvate(salvataggi, true);
							scelta = SCELTA_USCIRE_DAL_MENU;
						}
					}
				}
		// Altrimenti non ci sono partite salvate
        }
        else {
        	if (scelta != SCELTA_USCIRE_DAL_MENU) {
				printf(MESSAGGIO_NESSUNA_PARTITA_SALVATA);
				printf("%c", CARATTERE_NUOVA_RIGA);
				system("pause");
			}
        }

    } while(scelta != SCELTA_USCIRE_DAL_MENU);

    return salvataggi;
}

int contare_partite_salvate(char* percorso_file_partite_salvate) {

    int dimensione;
    int numero_partite_salvate;

    FILE* file = fopen(percorso_file_partite_salvate, "rb");    
    fseek(file, 0, SEEK_END);
    dimensione = ftell(file);
    fclose(file);

    numero_partite_salvate = dimensione / sizeof(record_partita);

    return numero_partite_salvate;
}

void aggiungere_partita_su_file(char* percorso_file_partite_salvate, record_partita partita) {
    FILE* file_partite_salvate;
    
    file_partite_salvate = fopen(percorso_file_partite_salvate, "ab");
    fwrite(&partita, sizeof(record_partita), 1, file_partite_salvate);
    fclose(file_partite_salvate);

    return;
}

record_partita leggere_partita_scelta(char* percorso_file_partite_salvate, int numero_partita) {
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

void salvare_partita(char* percorso_file_partite_salvate, record_partita partita) {
    int numero_partite_salvate, numero_partita_da_cancellare, riga;

    // Ottiene il numero di partite salvate sul file
    numero_partite_salvate = contare_partite_salvate(percorso_file_partite_salvate);
    
    // Se il file dei salvataggi è pieno
    if (numero_partite_salvate == NUMERO_MASSIMO_PARTITE_SALVATE) {
        // Stampa le partite salvate e chiede quale cancellare
        stampare_partite_salvate(percorso_file_partite_salvate);
        riga = ottenere_riga_cursore();
        numero_partita_da_cancellare = chiedere_intero(MESSAGGIO_SOVRASCRIVERE_PARTITA, SCELTA_USCIRE_DAL_MENU, NUMERO_MASSIMO_PARTITE_SALVATE, riga, PRIMA_COORDINATA_SCHERMO);
        
        // Se l'utente sceglie di cancellare una partita per poter salvare quella in corso
        if (numero_partita_da_cancellare != 0) {
            // Cancella la partita scelta e aggiunge la nuova partita
            cancellare_partita_da_file(percorso_file_partite_salvate, numero_partita_da_cancellare);
			printf("%c", CARATTERE_NUOVA_RIGA);
            aggiungere_partita_su_file(percorso_file_partite_salvate, partita);
            printf(MESSAGGIO_PARTITA_SALVATA);
			printf("%c", CARATTERE_NUOVA_RIGA);
        }
    }else {
        // Salva la partita sul file
        aggiungere_partita_su_file(percorso_file_partite_salvate, partita);
		printf("%c", CARATTERE_NUOVA_RIGA);
        printf(MESSAGGIO_PARTITA_SALVATA);
		printf("%c", CARATTERE_NUOVA_RIGA);
    }

    return;
}

void stampare_partite_salvate(char* percorso_file_partite_salvate) {
    FILE* file_partite_salvate;
    int numero_partita, numero_giocatore, posizione_giocatore, riga, riga_iniziale, colonna;
    record_partita partita;

    // Stampa il titolo
	system("cls");
	spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
    stampare_file_di_testo(PERCORSO_FILE_TITOLO);
    riga_iniziale = ottenere_riga_cursore();

    file_partite_salvate = fopen(percorso_file_partite_salvate, "rb");

    // Stampa le partite salvate
    numero_partita = 1;
    while (fread(&partita, sizeof(record_partita), 1, file_partite_salvate)) { // Legge una partita per volta dal file

    	// Se il numero della partita è dispari
    	if (numero_partita%2 == 1) {
    		colonna = PRIMA_COORDINATA_SCHERMO;
    	} 
        else {
    		colonna = COLONNA_STAMPA_PARTITE_PARI;
    	}

    	riga = riga_iniziale;
    	spostare_cursore(colonna, riga);

        // Stampa i dati della partita
        printf(MESSAGGIO_NUMERO_PARTITA, numero_partita);
        riga = riga + 1;
    	spostare_cursore(colonna, riga);
        printf(MESSAGGIO_DIMENSIONE_PERCORSO, leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita)));
        riga = riga + 1;

        // Stampa i dati dei giocatori
        numero_giocatore = PRIMO_INDICE_ARRAY;
        while(numero_giocatore < NUMERO_MASSIMO_GIOCATORI) {
            posizione_giocatore = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), numero_giocatore));
            if (posizione_giocatore != POSIZIONE_GIOCATORE_NON_PARTECIPANTE) {
            	spostare_cursore(colonna, riga);
            	printf(MESSAGGIO_POSIZIONE_GIOCATORE, (numero_giocatore+1), posizione_giocatore);
            	riga = riga + 1;
            }
            else {
            	spostare_cursore(colonna, riga);
            	printf(MESSAGGIO_GIOCATORE_NON_PRESENTE, (numero_giocatore+1));
            	riga = riga + 1;
            }
            numero_giocatore = numero_giocatore + 1;
        }
    	if (numero_partita%2 == 1 && numero_partita!=NUMERO_MASSIMO_PARTITE_SALVATE) {
    		riga = riga_iniziale;
    	} 
        else {
    		riga_iniziale = riga;
    	}
        numero_partita = numero_partita + 1;
    }

    printf("%c", CARATTERE_NUOVA_RIGA);

    fclose(file_partite_salvate);

    return;
}

void cancellare_partita_da_file(char* percorso_file_partite_salvate, int numero_partita_da_cancellare) {
    
    FILE *file_partite_salvate, *file_temporaneo;        
    record_partita partita;
    int numero_partite;

    // Apre il file partite salvate in modalità lettura binaria
    file_partite_salvate = fopen(percorso_file_partite_salvate, "rb");
    // Apre il file temporaneo in modalità scrittura binaria
    file_temporaneo = fopen(PERCORSO_FILE_BINARIO_TEMPORANEO, "wb");

    // Inizializza il numero di partite scritte sul file temporaneo a 0
    numero_partite = 0;
    
    // Fino a quando legge partite dal file
    while (fread(&partita, sizeof(record_partita), 1, file_partite_salvate)) {
        // Incrementa il numero delle partite scritte sul file temporaneo
    	numero_partite = numero_partite + 1;
        
    	// Se il numero della partita è diverso dal numer odella partita da cancellare
        if (numero_partite != numero_partita_da_cancellare) {
        	// Scrive la partita sul file temporaneo
            fwrite(&partita, sizeof(record_partita), 1, file_temporaneo);
        // Altrimenti (la partita è da cancellare quindi non la scrive sul fiel temporaneo)
        } 
        else {
        	// Comunica all'utente che ha cancellato la partita
        	spostare_cursore(PRIMA_COORDINATA_SCHERMO, ottenere_riga_cursore());
            printf(MESSAGGIO_PARTITA_CANCELLATA, numero_partita_da_cancellare);
        }
    }
    
    // Chiude i file
    fclose(file_partite_salvate);
    fclose(file_temporaneo);

    // Elimina il file con tutte le partite
    remove(percorso_file_partite_salvate);
    // Rinomina il file temporaneo con il nome del file partite salvate
    rename(PERCORSO_FILE_BINARIO_TEMPORANEO, percorso_file_partite_salvate);

    return;

}
