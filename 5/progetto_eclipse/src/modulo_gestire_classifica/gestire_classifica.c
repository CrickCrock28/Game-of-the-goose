//PERFETTO

#include "gestire_classifica.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "..\\percorsi_file.h"
#include "..\\moduli_record\\modulo_record_classificato\\record_classificato.h"
#include "..\\moduli_record\\modulo_record_giocatore\\record_giocatore.h"
#include "..\\moduli_record\\modulo_record_vet_giocatori\\record_vet_giocatori.h"

#include "..\\modulo_gestire_file\\gestire_file.h"
#include "..\\modulo_gestire_azioni_semplici\\gestire_azioni_semplici.h"
#include "..\\modulo_spostare_cursore\\spostare_cursore.h"


#define SCELTA_STAMPARE_CLASSIFICA 1

#define NUMERO_MASSIMO_CLASSIFICATI 10

#define MESSAGGIO_ENTRATO_IN_CLASSIFICA "Sei entrato in classifica!"
#define MESSAGGIO_PUNTEGGIO_NON_SUFFICIENTE_CLASSIFICA "Con il numero di lanci effettuati (%d) non puoi entrare in classifica."

#define MESSAGGIO_BORDO_SUPERIORE_INFERIORE_CLASSIFICA "------------------------------------------------------"
#define MESSAGGIO_PRIMA_RIGA_CLASSIFICA "|  Posto in classifica  |  Nome  |  Numereo di tiri  |"
#define MESSAGGIO_CLASSIFICATO "|          %2d           |  %s   |        %2d         |"
#define MESSAGGIO_CLASSIFICA_VUOTA "La classifica e' vuota"

#define MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO "Inserisci il tuo nome in modo da inserito nella classifica (3 caratteri): "
#define MESSAGGIO_ERRORE_NOME_VUOTO "Il nome non puo' essere vuoto, riprova"

#define STRINGA_NOME_VUOTO "   "
#define STRINGA_NOME_NON_AMMESSO_1 "\n  "
#define STRINGA_NOME_NON_AMMESSO_2 " \n "
#define STRINGA_NOME_NON_AMMESSO_3 "  \n"


int contare_classificati(char* percorso_file_classifica);
void gestire_menu_classifica(char* percorso_file_menu_classifica, char* percorso_file_classifica);
int contare_classificati(char* percorso_file_classifica);
record_classificato leggere_classificato_da_file(const char* percorso_file_classifica, int indice_classificato);
void leggere_vettore_classificati_da_file(char* percorso_file_classifica, record_classificato* vettore_classificati);
void inserire_classificato_in_vettore_classificati(record_classificato* vettore_classificati, int numero_classificati, record_classificato classificato_da_inserire);
void scrivere_vettore_classificati_su_file(char* percorso_file_classifica, record_classificato* vettore_classificati, int numero_classificati);
void inserire_classificato_in_classifica(char* percorso_file_classifica, record_classificato classificato_da_inserire);
void chiedere_nome_giocatore(char* nome_vincitore, char* messaggio);
int trovare_punteggio_minimo_ingresso_classifica(char* percorso_file_classifica);


void gestire_menu_classifica(char* percorso_file_menu_classifica, char* percorso_file_classifica) {
    int scelta, riga; // Scelta dell'utente tra le opzioni del menù

    do {
        // Stampare il menu e chiede all'utente la scelta
        system("cls");
	    spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
        stampare_file_di_testo(percorso_file_menu_classifica);
        riga = ottenere_riga_cursore();
        scelta = chiedere_intero(MESSAGGIO_SCELTA_AZIONE_MENU, SCELTA_USCIRE_DAL_MENU, SCELTA_STAMPARE_CLASSIFICA, riga, PRIMA_COORDINATA_SCHERMO);

        // Se l'utente sceglie di stampare la classifica
        if (scelta == SCELTA_STAMPARE_CLASSIFICA) {
            // Stampa a video la classifica
            stampare_classifica(percorso_file_classifica);
            system("pause");
        }
    } while (scelta != SCELTA_USCIRE_DAL_MENU);
    
    return;
}

int contare_classificati(char* percorso_file_classifica) {
    FILE *file;
    record_classificato classificato;
    int numero_classificati = 0;

    // Apri il file in modalità di lettura binaria
    file = fopen(percorso_file_classifica, "rb");

    // Calcola il numero di record classificati nel file
    while (fread(&classificato, sizeof(classificato), 1, file)) {
    	numero_classificati++;
    }

    // Chiudi il file
    fclose(file);

    // Restituisci il numero di classificati
    return numero_classificati;
}

record_classificato leggere_classificato_da_file(const char* percorso_file_classifica, int indice_classificato) {
    FILE* file_classifica;
    record_classificato classificato;

    // Apri il file in modalità di lettura binaria
    file_classifica = fopen(percorso_file_classifica, "rb");

    // Posizionati all'indice del giocatore nel file
    fseek(file_classifica, (indice_classificato-1)*sizeof(record_classificato), SEEK_SET);

    // Leggi il classificato dal file
	fread(&classificato, sizeof(record_classificato), 1, file_classifica);

    // Chiudi il file
    fclose(file_classifica);

    return classificato;
}

void leggere_vettore_classificati_da_file(char* percorso_file_classifica, record_classificato* vettore_classificati) {
    FILE *file_classifica;
    int numero_classificati;

    // Apri il file in modalità di lettura binaria
    file_classifica = fopen(percorso_file_classifica, "rb");

    // Conta i classificati all'interno della classifica
    numero_classificati = contare_classificati(percorso_file_classifica);

    // Leggi i record classificati dal file
    fread(vettore_classificati, sizeof(record_classificato), numero_classificati, file_classifica);

    // Chiudi il file
    fclose(file_classifica);

    return;
}

void inserire_classificato_in_vettore_classificati(record_classificato* vettore_classificati, int numero_classificati, record_classificato classificato_da_inserire) {

    int posizione_in_classifica, i;
    bool inserito = false;

    // Se è il primo classificato
	if(numero_classificati == 1){
		// Inserisci il classificato nella prima posizione dell'array
		vettore_classificati[PRIMO_INDICE_ARRAY] = classificato_da_inserire;

	// Altrimenti ci sono già dei classificati
	} else {

		posizione_in_classifica = PRIMO_INDICE_ARRAY;

		// Inserisci il classificato nel vettore
		while(posizione_in_classifica < numero_classificati && !inserito){
			// Se il numero di tiri del nuovo classificato è minore del numero di tiri del giocatore in classifica preso in esame
			if(leggere_tiri_record_classificato(classificato_da_inserire) <
			   leggere_tiri_record_classificato(vettore_classificati[posizione_in_classifica])){

				// Sposta tutti gli elementi del vettore a destra partendo dal posto in cui verrà inserito il nuovo classificato
				i = posizione_in_classifica + 1;
				while(i < numero_classificati){
					vettore_classificati[i] = vettore_classificati[i-1];
					i++;
				}

				// Inserisce il nuovo classificato
				vettore_classificati[posizione_in_classifica] = classificato_da_inserire;
				// Imposta la variabile inserito a true in modo da uscie dal ciclo
				inserito = true;
			}
			posizione_in_classifica++;
		}
	}
    return;
}

void scrivere_vettore_classificati_su_file(char* percorso_file_classifica, record_classificato* vettore_classificati, int numero_classificati){
	FILE *file_classifica;
	int i;

	// Apri il file in modalità di scrittura binaria
	file_classifica = fopen(percorso_file_classifica, "wb");

	// Scrivi i record classificati nel file
	i = PRIMO_INDICE_ARRAY;
	while(i < numero_classificati){
		// Inserisco il classificato i sul file
		fwrite(&vettore_classificati[i], sizeof(record_classificato), 1, file_classifica);
		i++;
	}

	// Chiudi il file
	fclose(file_classifica);

	return;
}

void inserire_classificato_in_classifica(char* percorso_file_classifica, record_classificato classificato_da_inserire){

	int numero_classificati;
	record_classificato vettore_classificati[NUMERO_MASSIMO_CLASSIFICATI];

	// Legge il numero di classificati
	numero_classificati = contare_classificati(percorso_file_classifica);

	// Se il file non è pieno incrementa il numero dei classificati
	if(numero_classificati<NUMERO_MASSIMO_CLASSIFICATI){
		numero_classificati++;
	}

	// Mette i classificati presenti nel file in un vettore
	leggere_vettore_classificati_da_file(percorso_file_classifica, vettore_classificati);

	// Inserisce il nuovo classificato nel vettore
	inserire_classificato_in_vettore_classificati(vettore_classificati, numero_classificati, classificato_da_inserire);

	// Scrive il vettore contenente i classificati aggiornati sul file
	scrivere_vettore_classificati_su_file(percorso_file_classifica, vettore_classificati, numero_classificati);

	return;
}

void chiedere_nome_giocatore(char* nome_vincitore, char* messaggio) { // SE INSERISCI 25 CARATTERI SI BUGGA

	int lunghezza_nome, i, riga;

	// Stampa il messaggio per chiedere il nome all'utente
	printf("%s", messaggio);

	// Chiede il nome all'utente
	getchar(); // Consuma il vecchio carattere di nuova riga rimasto nel buffer
	scanf("%[^\n]", nome_vincitore); // Legge i caratteri fino al \n
	getchar(); // Consuma il carattere di nuova riga rimasto nel buffer

	// Calcola la lunghezza del nome
    lunghezza_nome = strlen(nome_vincitore);

	// Se la lunghezza del nome è minore della dimensione corretta
	if (lunghezza_nome < LUNGHEZZA_NOME_CLASSIFICATO) {
		// Completa con spazi
		i = lunghezza_nome;
		while (i < LUNGHEZZA_NOME_CLASSIFICATO) {
			nome_vincitore[i] = CARATTERE_SPAZIO;
			i++;
		}
	}

	// Aggiungi il terminatore di stringa
	nome_vincitore[LUNGHEZZA_NOME_CLASSIFICATO] = CARATTERE_FINE_STRINGA;  // Aggiungi il terminatore di stringa


	// Fino a quando il nome corrisponde ad uno di quelli non ammessi
    while(strcmp(STRINGA_NOME_VUOTO, nome_vincitore) == 0||
    	  strcmp(STRINGA_NOME_NON_AMMESSO_1, nome_vincitore) == 0||
		  strcmp(STRINGA_NOME_NON_AMMESSO_2, nome_vincitore) == 0||
		  strcmp(STRINGA_NOME_NON_AMMESSO_3, nome_vincitore) == 0){

    	//Comunica l'errore all'utente
		printf(MESSAGGIO_ERRORE_NOME_VUOTO);

		// Stampa nuovamente il messaggio per inserire il nome
    	riga = ottenere_riga_cursore(); // La riga è quella successiva a quella in cui è stato inserito il nome (a causa del \n usato per inserire il nome)
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, riga-1);
		printf("%s", messaggio);

		// Chiede il nome all'utente
		scanf("%[^\n]", nome_vincitore); // Legge i caratteri fino al \n
		getchar(); // Consuma il carattere di nuova riga rimasto nel buffer

		// Calcola la lunghezza del nome
		lunghezza_nome = strlen(nome_vincitore);

		// Se la lunghezza del nome è minore della dimensione corretta
		if (lunghezza_nome < LUNGHEZZA_NOME_CLASSIFICATO) {
			// Completa con spazi
			i = lunghezza_nome;
			while (i < LUNGHEZZA_NOME_CLASSIFICATO) {
				nome_vincitore[i] = CARATTERE_SPAZIO;
				i++;
			}
		}

		// Aggiungi il terminatore di stringa
		nome_vincitore[LUNGHEZZA_NOME_CLASSIFICATO] = CARATTERE_FINE_STRINGA;

    }
	return;
}

int trovare_punteggio_minimo_ingresso_classifica(char* percorso_file_classifica){
	int punteggio_minimo,
		numero_classificati;
	record_classificato ultimo_classificato;

	// Conta i classificati all'interno del file
	numero_classificati = contare_classificati(percorso_file_classifica);

	// Se la classifica è piena
	if(numero_classificati == NUMERO_MASSIMO_CLASSIFICATI){

		// Legge l'ultimo giocatore dalla classifica
		ultimo_classificato = leggere_classificato_da_file(percorso_file_classifica, numero_classificati);

		// Imposta il puntegio minimo per entrare in classifica pari al punteggio dell'ultimo giocatore in classifica
		punteggio_minimo = leggere_tiri_record_classificato(ultimo_classificato);

	// Altrimenti la classifica non è piena
	} else {
		// Imposta il punteggio minimo per entrare in classifica a "+ infinito" in modo che chiunque possa entrare in classifica
		punteggio_minimo = INT_MAX;
	}

	return punteggio_minimo;
}

void aggiornare_classifica(record_partita partita, int indice_giocatore_vincitore){

	int punteggio_ingresso_classifica,
		numero_tiri_vincitore,
		riga;
	record_giocatore giocatore_vincitore;
	record_classificato classificato;
	char nome_vincitore[LUNGHEZZA_NOME_CLASSIFICATO + 1];

	// Legge il numero di tiri del giocatore che ha vinto la partita
	giocatore_vincitore = leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), indice_giocatore_vincitore);
	numero_tiri_vincitore = leggere_numero_dadi_lanciati_record_giocatore(giocatore_vincitore);

	// Legge il punteggio minimo per entrare in classifica (il numero di tiri più grande in classifica)
	punteggio_ingresso_classifica = trovare_punteggio_minimo_ingresso_classifica(PERCORSO_FILE_CLASSIFICA);

	// Se il giocatore può entrare in classifica
	if(numero_tiri_vincitore < punteggio_ingresso_classifica){

		// Chiede al giocatore il suo nome
		chiedere_nome_giocatore(nome_vincitore, MESSAGGIO_RICHIESTA_NOME_CLASSIFICATO);

		// Crea il record classificato per inserire il giocatore in classifica
		classificato = scrivere_nome_giocatore_record_classificato(classificato, nome_vincitore);
		classificato = scrivere_tiri_record_classificato(classificato, leggere_numero_dadi_lanciati_record_giocatore(giocatore_vincitore));

		// Inserisce il classificato all'interno della classifica
		inserire_classificato_in_classifica(PERCORSO_FILE_CLASSIFICA, classificato);

		//Comunica al giocatore che è entrato in classifica
		riga = ottenere_riga_cursore();
		stampare_riga_vuota(riga, NUMERO_COLONNA_MASSIMA);
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, riga);
		printf(MESSAGGIO_ENTRATO_IN_CLASSIFICA);
		printf("%c",CARATTERE_NUOVA_RIGA);

	// Altimenti il giocatore non può entrare in classifica
	} else {

		// Comunica al giocatore che non può entrare in classifica
		printf(MESSAGGIO_PUNTEGGIO_NON_SUFFICIENTE_CLASSIFICA, numero_tiri_vincitore);
		printf("%c",CARATTERE_NUOVA_RIGA);
	}

	return;
}

void stampare_classifica(char* percorso_file_classifica){
    FILE *file_classifica;
    record_classificato classificato;
    int numero_tiri,
		numero_classificato = 0;
    char nome[LUNGHEZZA_NOME_CLASSIFICATO + 1];

    // Stampa il titolo
    system("cls");
    stampare_file_di_testo(PERCORSO_FILE_TITOLO);

    // Apri il file in modalità di lettura binaria
    file_classifica = fopen(percorso_file_classifica, "rb");

    // Leggi i record classificati dal file e stampali
    while (fread(&classificato, sizeof(record_classificato), 1, file_classifica)) {
    	// Legge i dati del classificato
        numero_classificato++;

        if(numero_classificato == 1){
            // Stampa la prima riga della classifica
            printf(MESSAGGIO_PRIMA_RIGA_CLASSIFICA);
            printf("%c",CARATTERE_NUOVA_RIGA);
        	printf(MESSAGGIO_BORDO_SUPERIORE_INFERIORE_CLASSIFICA);
        	printf("%c",CARATTERE_NUOVA_RIGA);
        }

    	leggere_nome_giocatore_record_classificato(classificato, nome);
    	numero_tiri = leggere_tiri_record_classificato(classificato);
    	// Stampa i dati del classificato
        printf(MESSAGGIO_CLASSIFICATO, numero_classificato, nome, numero_tiri);
        printf("%c",CARATTERE_NUOVA_RIGA);
    	printf(MESSAGGIO_BORDO_SUPERIORE_INFERIORE_CLASSIFICA);
    	printf("%c",CARATTERE_NUOVA_RIGA);
    }

    if(numero_classificato == 0){
    	printf(MESSAGGIO_CLASSIFICA_VUOTA);
        printf("%c",CARATTERE_NUOVA_RIGA);
    }

    // Chiudi il file
    fclose(file_classifica);

	return;
}