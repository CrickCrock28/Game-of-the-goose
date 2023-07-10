// PERFETTO
#include "giocare_partita.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "..\\costanti.h"
#include "..\\percorsi_file.h"


#include "..\\modulo_gestire_file\\gestire_file.h"
#include "..\\modulo_gestire_azioni_semplici\\gestire_azioni_semplici.h"
#include "..\\modulo_spostare_cursore\\spostare_cursore.h"

#include "..\\moduli_record\\modulo_record_vet_giocatori\\record_vet_giocatori.h"
#include "..\\moduli_record\\modulo_record_giocatore\\record_giocatore.h"
#include "..\\moduli_record\\modulo_record_percorso\\record_percorso.h"
#include "..\\modulo_gestire_partite_salvate\\gestire_partite_salvate.h"
#include "..\\modulo_gestire_classifica\\gestire_classifica.h"


#define MESSAGGIO_STABILIRE_GIOCATORE_INIZIALE "Tutti i giocatori tireranno i dadi per stabilire chi sara' il primo giocatore.\nIniziera' il giocatore che ottera' il punteggio piu' alto (in caso di parita'\niniziera' il primo giocatore che ottenuto tale punteggio):"
#define MESSAGGIO_DADI_TIRATI "Primo dado: %d  	       Secondo dado: %d\n             Totale: %2d"
#define MESSAGGIO_GIOCATORE_INIZIALE "Iniziera' il giocatore %d."
#define MESSAGGIO_NUMERO_GIOCATORE "Giocatore %d "
#define MESSAGGIO_SIMBOLO_GIOCATORE "(%s):"
#define MESSAGGIO_GIOCATORE_DI_TURNO "E' il turno del giocatore %d "

#define MESSAGGIO_CASELLA_ATTUALE "ti trovi sulla casella numero %d."
#define MESSAGGIO_NUOVA_POSIZIONE "Ti sei spostato dalla casella %d alla casella %d"
#define MESSAGGIO_GESTIONE_SURPLUS "Per la regola delle caselle in surplus ti sei spostato sulla casella %d"
#define MESSAGGIO_CASELLA_SPECIALE_AGGIORNAMENTO_POSIZIONE "La casella numero %d e' una casella %s, per il suo effetto sei finito\nsulla casella %d."
#define MESSAGGIO_ARRIVO_CASELLA_LOCANDA "La casella numero %d e' una casella %s, rimarrai bloccato per %d turni."
#define MESSAGGIO_ARRIVO_CASELLA_POZZO_PRIGIONE "La casella numero %d e' una casella %s, rimarrai bloccato qui fino a\nquando qualcuno non prendera' il tuo posto oppure otterrai %d o %d tirando i dadi."
#define MESSAGGIO_SBLOCCO_ARRIVO_POZZO_PRIGIONE "Hai sbloccato il giocatore %d "
#define MESSAGGIO_CASELLA_SPECIALE_BLOCCATO "Poiche' nei turni precedenti sei finito sulla casella %s sei bloccato."
#define MESSAGGIO_NUMERO_TURNI_BLOCCATO "Rimarrai bloccato ancora per %d turni."
#define MESSAGGIO_PROSEGUIRE_PROSSIMO_TURNO "Potrai proseguire nel prossimo turno."
#define MESSAGGIO_ISTRUZIONI_USCITA_POZZO_PRIGIONE "Se con questo lancio di dadi otterrai %d o %d uscirai dalla casella %s."
#define MESSAGGIO_SBLOCCATO_POZZO_PRIGIONE "Hai ottenuto %d quindi sei stato sbloccato."
#define MESSAGGIO_NON_SBLOCCATO_POZZO_PRIGIONE "Hai ottenuto %d quindi rimarrai bloccato."
#define MESSAGGIO_ARRIVO_CASELLA_FINALE "La casella numero %d e' la casella %s. Hai vinto!"
#define MESSAGGIO_CASELLA_SPECIALE_FINE "Hai vinto!"

#define NOME_CASELLA_SCHELETRO "\033[0;31mscheletro\033[0m" // prigione (rosso)
#define NOME_CASELLA_LABIRINTO "\033[0;31mlabirinto\033[0m" // labirinto (rosso)
#define NOME_CASELLA_LOCANDA "\033[0;31mlocanda\033[0m" // locanda (rosso)
#define NOME_CASELLA_OCA "\033[0;32moca\033[0m" // oca (verde)
#define NOME_CASELLA_PONTE "\033[0;32mponte\033[0m" // ponte (verde)
#define NOME_CASELLA_POZZO "\033[0;31mpozzo\033[0m" // pozzo (rosso)
#define NOME_CASELLA_PRIGIONE "\033[0;31mprigione\033[0m" // prigione (rosso)
#define NOME_CASELLA_FINE "\033[0;33mfinale\033[0m" // finale (giallo)
#define LUNGHEZZA_MASSIMA_NOME_CASELLA 20

#define PRIMO_DADO_COMBINAZIONE_4_5 4
#define SECONDO_DADO_COMBINAZIONE_4_5 5
#define ARRIVO_PRIMO_LANCIO_4_5 53

#define PRIMO_DADO_COMBINAZIONE_3_6 3
#define SECONDO_DADO_COMBINAZIONE_3_6 6
#define ARRIVO_PRIMO_LANCIO_3_6 26

#define SOMMA_DADI_USCITA_PRIGIONE_POZZO_1 5
#define SOMMA_DADI_USCITA_PRIGIONE_POZZO_2 7

#define NUMERO_MINIMO_DADO 1
#define NUMERO_MASSIMO_DADO 6

#define TURNI_BLOCCATO_LOCANDA 3
#define POSIZIONE_ARRIVO_LABIRINTO_90_CASELLE 33

#define PRIMA_POSIZIONE_PERCORSO 1

#define SCELTA_TIRARE_I_DADI 1
#define SCELTA_CREARE_NUOVA_PARTITA 2
#define SCELTA_SALVARE_PARTITA 3
#define SCELTA_ABBANDONARE_PARTITA 4

#define PRIMA_RIGA_TABELLONE "--------------------------------Gioco dell'oca------------------------------"
#define BORDO_SUPERIORE_INFERIORE_CASELLA "------"
#define INTERNO_CASELLA_CON_GIOCATORI "|%s  %s|"
#define INTERNO_CASELLA_TIPO_E_NUMERO "|%s%c%s %2d|"

#define NUMERO_CASELLE_PER_RIGA 15

#define SIMBOLO_GIOCATORE_1 "\033[0;33mX\033[0m" // X giallo
#define SIMBOLO_GIOCATORE_2 "\033[0;34mX\033[0m" // X blu
#define SIMBOLO_GIOCATORE_3 "\033[0;35mX\033[0m" // X magenta
#define SIMBOLO_GIOCATORE_4 "\033[0;36mX\033[0m" // X ciano
#define LUNGHEZZA_SIMBOLO_GIOCATORE 13
#define STRINGA_SPAZIO_VUOTO " "
#define CARATTERE_SPAZIO_VUOTO ' '

#define INDICE_GIOCATORE_1 0
#define INDICE_GIOCATORE_2 1
#define INDICE_GIOCATORE_3 2
#define INDICE_GIOCATORE_4 3

#define INIZIO_CODICE_COLORE_ROSSO "\033[0;31m"
#define INIZIO_CODICE_COLORE_VERDE "\033[0;32m"
#define INIZIO_CODICE_COLORE_GIALLO "\033[0;33m"
#define LUNGHEZZA_INIZIO_CODICE_COLORE 9
#define FINE_CODICE_COLORE "\033[0m"


void stampare_messaggio_simbolo_giocatore(char* messaggio_simbolo_giocatore, int indice_giocatore);
char trovare_tipo_casella_giocatore(record_partita partita, int indice_giocatore);
record_partita gestire_menu_partita(char* percorso_file_menu_partita, record_partita partita);
void stampare_percorso(record_partita partita);
record_partita gestire_surplus(record_partita partita, int indice_giocatore);
record_partita lanciare_primi_dadi(record_partita partita, int indice_giocatore);
record_partita lanciare_dadi(record_partita partita, int indice_giocatore);
record_partita lanciare_dadi_pozzo_prigione(record_partita partita, int indice_giocatore);
void stampare_valori_dadi(int dado_1, int dado_2, int indice_giocatore);
void stampare_aggiornamento_posizione(int vecchia_posizione, int nuova_posizione);
record_partita avanzare_turno(record_partita partita);
record_partita stabilire_primo_giocatore(record_partita partita);
record_partita applicare_effetto_casella_oca_ponte(record_partita partita, int indice_giocatore, char tipo_casella, bool effetto_contrario);
record_partita applicare_effetto_casella_pozzo_prigione(record_partita partita, int indice_giocatore, char tipo_casella);
record_partita applicare_effetto_casella_locanda(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_finale(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_labirinto(record_partita partita, int indice_giocatore);
record_partita applicare_effetto_casella_scheletro(record_partita partita, int indice_giocatore);
record_partita gestire_effetti_caselle_speciali(record_partita partita, int indice_giocatore);
record_partita gestire_scelta_menu_partita(record_partita partita, int scelta);


void stampare_messaggio_simbolo_giocatore(char* messaggio_simbolo_giocatore, int indice_giocatore){
	if(indice_giocatore == INDICE_GIOCATORE_1){
		printf(messaggio_simbolo_giocatore, SIMBOLO_GIOCATORE_1);
	}else{
		if(indice_giocatore == INDICE_GIOCATORE_2){
			printf(messaggio_simbolo_giocatore, SIMBOLO_GIOCATORE_2);
		}else{
			if(indice_giocatore == INDICE_GIOCATORE_3){
				printf(messaggio_simbolo_giocatore, SIMBOLO_GIOCATORE_3);
			}else{
				if(indice_giocatore == INDICE_GIOCATORE_4){
					printf(messaggio_simbolo_giocatore, SIMBOLO_GIOCATORE_4);
				}
			}
		}
	}

	return;
}

char trovare_tipo_casella_giocatore(record_partita partita, int indice_giocatore){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    record_percorso percorso;
    int numero_casella;
    char tipo_casella;

    // Legge il numero della casella in cui si trova il giocatore
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    numero_casella = leggere_posizione_record_giocatore(giocatore) - 1; // Viene decrementato di 1 poichè in c l'indice dell'n-esima casella è n-1

    // Legge il tipo della casella in cui si trova il giocatore
    percorso = leggere_percorso_record_partita(partita);
    tipo_casella = leggere_casella_record_percorso(percorso, numero_casella);

    return tipo_casella;
}

record_partita giocare_partita(record_partita partita){

	int indice_giocatore_di_turno;

    // Mostra il percorso all'utente
    stampare_percorso(partita);
    system("pause");

    // Controlla se bisogna ancora stabilire il primo giocatore
    indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
    if(indice_giocatore_di_turno == GIOCATORE_DI_TURNO_NON_STABILITO){
    	// Se non è stato ancora fatto stabilisce il primo giocatore
        partita = stabilire_primo_giocatore(partita);
    }

    while(!(leggere_terminata_record_partita(partita))){

    	partita = gestire_menu_partita(PERCORSO_FILE_MENU_PARTITA, partita);
    }

    return partita;
}

record_partita gestire_menu_partita(char* percorso_file_menu_partita, record_partita partita){

    int scelta, riga, indice_giocatore_di_turno, numero_casella;
    record_giocatore giocatore;

	do {
		// Stampa il menu della partita
		system("cls");
		spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
		stampare_file_di_testo(PERCORSO_FILE_MENU_PARTITA);
		printf("%c", CARATTERE_NUOVA_RIGA);

	    // Recupera e mostra informazioni relative al giocatore di turno e alla sua posizione
        indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
        printf(MESSAGGIO_GIOCATORE_DI_TURNO, indice_giocatore_di_turno+1);
        stampare_messaggio_simbolo_giocatore(MESSAGGIO_SIMBOLO_GIOCATORE, indice_giocatore_di_turno);
		printf("%c", CARATTERE_NUOVA_RIGA);
        giocatore = leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), indice_giocatore_di_turno);
        numero_casella = leggere_posizione_record_giocatore(giocatore);
        printf(MESSAGGIO_CASELLA_ATTUALE, numero_casella);
		printf("%c", CARATTERE_NUOVA_RIGA);
		printf("%c", CARATTERE_NUOVA_RIGA);

        // Chiede al giocatore di effettuare la scelta
		riga = ottenere_riga_cursore();
        scelta = chiedere_intero(MESSAGGIO_SCELTA_AZIONE_MENU, SCELTA_USCIRE_DAL_MENU, SCELTA_ABBANDONARE_PARTITA, riga, PRIMA_COORDINATA_SCHERMO);

        //Gestisce la scelta effettuata
        partita = gestire_scelta_menu_partita(partita, scelta);

	} while(scelta == SCELTA_TIRARE_I_DADI &&
			leggere_terminata_record_partita(partita) == false);

    return partita;
}

record_partita gestire_surplus(record_partita partita, int indice_giocatore){

	int dimensione_percorso, posizione_surplus, nuova_posizione;
	char tipo_casella;
	record_giocatore giocatore;
    record_vet_giocatori vet_giocatori;


	// Legge il giocatore di cui gestire il surplus dalla partita
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
	giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

	// Legge la posizione del giocatore
	posizione_surplus = leggere_posizione_record_giocatore(giocatore);

	// Legge la dimensione del percorso
	dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

	// Il giocatore retrocede delle caselle in surplus
	nuova_posizione = dimensione_percorso - (posizione_surplus - dimensione_percorso);
	giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);

	// Salva il giocatore nella partita
	vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
	partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

	// Ottiene il tipo della casella su cui è finito il giocatore
	tipo_casella = trovare_tipo_casella_giocatore(partita, indice_giocatore);

	// Comunica al giocatore che è stato gestito il surplus
	printf(MESSAGGIO_GESTIONE_SURPLUS, nuova_posizione);
	printf("%c", CARATTERE_NUOVA_RIGA);

	// Fino a quando il giocatore si trova su una casella oca o casella ponte
	while(tipo_casella == TIPO_CASELLA_OCA ||
		  tipo_casella == TIPO_CASELLA_PONTE){

		// Applica l'effetto della casella oca/ponte al contrario
		partita = applicare_effetto_casella_oca_ponte(partita, indice_giocatore, tipo_casella, true);

		// Ottiene il tipo della casella su cui è finito il giocatore dopo aver applicato l'effetto
		tipo_casella = trovare_tipo_casella_giocatore(partita, indice_giocatore);
	}

	return partita;
}

record_partita lanciare_primi_dadi(record_partita partita, int indice_giocatore){
    
    int dado_1,
		dado_2,
		vecchia_posizione = POSIZIONE_INIZIO_PARTITA,
		nuova_posizione,
		dimensione_percorso;
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    // Vengono tirati i dadi
    dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);      
    dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);      
    
    // Vengono salvati i valori dei dadi
    partita = scrivere_ultimo_lancio_dado_1_record_partita(partita, dado_1);
    partita = scrivere_ultimo_lancio_dado_2_record_partita(partita, dado_2);

    // Vengono letti il giocatore e la dimensione del percorso dalla partita passata in input
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

	// Legge la dimensione del percorso
    dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

    // Viene calcolata la nuova posizione del giocatore in base ai dadi tirati
    if((dado_1 == PRIMO_DADO_COMBINAZIONE_4_5 && dado_2 == SECONDO_DADO_COMBINAZIONE_4_5)||
       (dado_1 == SECONDO_DADO_COMBINAZIONE_4_5 && dado_2 == PRIMO_DADO_COMBINAZIONE_4_5)){
    	nuova_posizione = calcolare_proporzione(ARRIVO_PRIMO_LANCIO_4_5, NUMERO_MASSIMO_CASELLE, dimensione_percorso);
    } else { if((dado_1 == PRIMO_DADO_COMBINAZIONE_3_6 && dado_2 == SECONDO_DADO_COMBINAZIONE_3_6)||
    		    (dado_1 == SECONDO_DADO_COMBINAZIONE_3_6 && dado_2 == PRIMO_DADO_COMBINAZIONE_3_6)){
    	nuova_posizione = calcolare_proporzione(ARRIVO_PRIMO_LANCIO_3_6, NUMERO_MASSIMO_CASELLE, dimensione_percorso);
		} else {
			nuova_posizione = dado_1 + dado_2;
		}
    }

    // Viene salvata la nuova posizione del giocatore
    giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
    partita = scrivere_vet_giocatori_record_partita(partita, scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore));


    // Vengono comunicati i valori e il totale dei dadi all'utente
	printf("%c", CARATTERE_NUOVA_RIGA);
	stampare_valori_dadi(dado_1, dado_2, indice_giocatore);
	printf("%c", CARATTERE_NUOVA_RIGA);
	printf("%c", CARATTERE_NUOVA_RIGA);

    // Viene comunicata la nuova posizione sul tabellone all'utente
    stampare_aggiornamento_posizione(vecchia_posizione, nuova_posizione);
	printf("%c", CARATTERE_NUOVA_RIGA);

    return partita;
}

record_partita lanciare_dadi(record_partita partita, int indice_giocatore){
    int dado_1,
		dado_2,
		dimensione_percorso,
		vecchia_posizione,
		nuova_posizione;

    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    // Vengono tirati i dadi
    dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
    dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);

    // Vengono comunicati i valori e il totale dei dadi all'utente
	printf("%c", CARATTERE_NUOVA_RIGA);
	stampare_valori_dadi(dado_1, dado_2, indice_giocatore);
	printf("%c", CARATTERE_NUOVA_RIGA);
	printf("%c", CARATTERE_NUOVA_RIGA);

    // Vengono salvati i valori degli ultimi dadi tirati
    partita = scrivere_ultimo_lancio_dado_1_record_partita(partita, dado_1);
    partita = scrivere_ultimo_lancio_dado_2_record_partita(partita, dado_2);

    // Legge il giocatore dalla partita
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

	// Legge la dimensione del percorso
	dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

	// Legge la vecchia posizione e calcola la nuova posizione dele giocatore
	vecchia_posizione = leggere_posizione_record_giocatore(giocatore);
	nuova_posizione = vecchia_posizione + dado_1 + dado_2;

	// Aggiorna la posizione alli'interno del giocatore e lo riscrive nella partita
	giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
	vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
	partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

	// Viene comunicata la nuova posizione sul tabellone all'utente
	stampare_aggiornamento_posizione(vecchia_posizione, nuova_posizione);
	printf("%c", CARATTERE_NUOVA_RIGA);

	// Se la nuova posizione del giocatore supera la fine del tabellone
	if(nuova_posizione > dimensione_percorso){
		partita = gestire_surplus(partita, indice_giocatore);

	    // Rilegge il giocatore dalla partita
	    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
	    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
	    nuova_posizione = leggere_posizione_record_giocatore(giocatore);
	}

    return partita;
}

record_partita lanciare_dadi_pozzo_prigione(record_partita partita, int indice_giocatore){
	int dado_1,
		dado_2,
		dimensione_percorso,
		vecchia_posizione,
		nuova_posizione,
		somma_dadi;

	record_vet_giocatori vet_giocatori;
	record_giocatore giocatore;

	// Vengono tirati i dadi
	dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
	dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);

	//Calcola la somma dei dadi
	somma_dadi = dado_1 + dado_2;

	// Vengono salvati i valori degli ultimi dadi tirati
	partita = scrivere_ultimo_lancio_dado_1_record_partita(partita, dado_1);
	partita = scrivere_ultimo_lancio_dado_2_record_partita(partita, dado_2);

    // Vengono comunicati i valori e il totale dei dadi all'utente
	printf("%c", CARATTERE_NUOVA_RIGA);
	stampare_valori_dadi(dado_1, dado_2, indice_giocatore);
	printf("%c", CARATTERE_NUOVA_RIGA);
	printf("%c", CARATTERE_NUOVA_RIGA);

	if(somma_dadi == SOMMA_DADI_USCITA_PRIGIONE_POZZO_1 ||
	   somma_dadi == SOMMA_DADI_USCITA_PRIGIONE_POZZO_2){

		// Legge il giocatore dalla partita
		vet_giocatori = leggere_vet_giocatori_record_partita(partita);
		giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

		// Sblocca il giocatore
		giocatore = scrivere_bloccato_record_giocatore(giocatore, false);

		// Legge la dimensione del percorso
		dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

		// Legge la vecchia posizione e calcola la nuova posizione dele giocatore
		vecchia_posizione = leggere_posizione_record_giocatore(giocatore);
		nuova_posizione = vecchia_posizione + somma_dadi;

		// Aggiorna la posizione alli'interno del giocatore e lo riscrive nella partita
		giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
		vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
		partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

		// Viene comunicata la nuova posizione sul tabellone all'utente
		stampare_aggiornamento_posizione(vecchia_posizione, nuova_posizione);
		printf("%c", CARATTERE_NUOVA_RIGA);

		// Se la nuova posizione del giocatore supera la fine del tabellone
		if(nuova_posizione > dimensione_percorso){
			// Gestisce il surplus
			partita = gestire_surplus(partita, indice_giocatore);

		    // Rilegge il giocatore dalla partita
		    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
		    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
		    nuova_posizione = leggere_posizione_record_giocatore(giocatore);
		}

		// Comunica al giocatore che è stato sbloccato
		printf(MESSAGGIO_SBLOCCATO_POZZO_PRIGIONE, somma_dadi);
		printf("%c", CARATTERE_NUOVA_RIGA);

	} else {
		// Comunica al giocatore che è stato sbloccato
		printf(MESSAGGIO_NON_SBLOCCATO_POZZO_PRIGIONE, somma_dadi);
		printf("%c", CARATTERE_NUOVA_RIGA);

	}

	return partita;
}

void stampare_valori_dadi(int dado_1, int dado_2, int indice_giocatore){

	// Stampa il numero del giocatore
	printf(MESSAGGIO_NUMERO_GIOCATORE, indice_giocatore+1);

	// Stampa il simbolo del giocatore
	stampare_messaggio_simbolo_giocatore(MESSAGGIO_SIMBOLO_GIOCATORE, indice_giocatore);
	printf("%c", CARATTERE_NUOVA_RIGA);

	// Stampa i valori dei dadi tirati
	printf(MESSAGGIO_DADI_TIRATI, dado_1, dado_2, dado_1+dado_2);

	return;
}

void stampare_aggiornamento_posizione(int vecchia_posizione, int nuova_posizione){

	printf(MESSAGGIO_NUOVA_POSIZIONE, vecchia_posizione, nuova_posizione);

	return;
}

void stampare_percorso(record_partita partita){
	int posizione_giocatore_1,
		posizione_giocatore_2,
		posizione_giocatore_3,
		posizione_giocatore_4,
		dimensione_percorso,
		x = PRIMA_COORDINATA_SCHERMO,
		y = PRIMA_COORDINATA_SCHERMO,
		numero_casella = PRIMA_POSIZIONE_PERCORSO;

	char simbolo_giocatore_1[LUNGHEZZA_SIMBOLO_GIOCATORE],
	 	 simbolo_giocatore_2[LUNGHEZZA_SIMBOLO_GIOCATORE],
		 simbolo_giocatore_3[LUNGHEZZA_SIMBOLO_GIOCATORE],
		 simbolo_giocatore_4[LUNGHEZZA_SIMBOLO_GIOCATORE],
		 inizio_codice_colore[LUNGHEZZA_INIZIO_CODICE_COLORE],
		 tipo_casella,
		 caselle[NUMERO_MASSIMO_CASELLE];


	posizione_giocatore_1 = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), INDICE_GIOCATORE_1));
	posizione_giocatore_2 = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), INDICE_GIOCATORE_2));
	posizione_giocatore_3 = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), INDICE_GIOCATORE_3));
	posizione_giocatore_4 = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), INDICE_GIOCATORE_4));

	copiare_caselle_percorso(leggere_percorso_record_partita(partita), caselle);
	dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

	system("cls");
	printf(PRIMA_RIGA_TABELLONE);
	while(numero_casella<=dimensione_percorso){
		spostare_cursore(x,y);
		if(numero_casella>NUMERO_CASELLE_PER_RIGA){
			printf(BORDO_SUPERIORE_INFERIORE_CASELLA);
		}
		

		if(posizione_giocatore_1 == numero_casella){
			strcpy(simbolo_giocatore_1, SIMBOLO_GIOCATORE_1);
		} else {
			strcpy(simbolo_giocatore_1, STRINGA_SPAZIO_VUOTO);
		}

		if(posizione_giocatore_2 == numero_casella){
			strcpy(simbolo_giocatore_2, SIMBOLO_GIOCATORE_2);
		} else {
			strcpy(simbolo_giocatore_2, STRINGA_SPAZIO_VUOTO);
		}

		spostare_cursore(x, y+1);
		printf(INTERNO_CASELLA_CON_GIOCATORI, simbolo_giocatore_1, simbolo_giocatore_2);

		if(posizione_giocatore_3 == numero_casella){
			strcpy(simbolo_giocatore_3, SIMBOLO_GIOCATORE_3);
		} else {
			strcpy(simbolo_giocatore_3, STRINGA_SPAZIO_VUOTO);
		}

		if(posizione_giocatore_4 == numero_casella){
			strcpy(simbolo_giocatore_4, SIMBOLO_GIOCATORE_4);
		} else {
			strcpy(simbolo_giocatore_4, STRINGA_SPAZIO_VUOTO);
		}

		spostare_cursore(x, y+2);
		printf(INTERNO_CASELLA_CON_GIOCATORI, simbolo_giocatore_3, simbolo_giocatore_4);
		
		if(caselle[numero_casella-1] != TIPO_CASELLA_NORMALE){
			tipo_casella = caselle[numero_casella-1];

			// Scegli l'inizio del codice colore in base al tipo di casella
			if (tipo_casella == TIPO_CASELLA_OCA ||
				tipo_casella == TIPO_CASELLA_PONTE){
					strcpy(inizio_codice_colore, INIZIO_CODICE_COLORE_VERDE);
				} else {
					if (tipo_casella == TIPO_CASELLA_FINE){
						strcpy(inizio_codice_colore, INIZIO_CODICE_COLORE_GIALLO);
					} else {
						strcpy(inizio_codice_colore, INIZIO_CODICE_COLORE_ROSSO);
					}
				}
		} else {
			tipo_casella = CARATTERE_SPAZIO_VUOTO;
		}

		spostare_cursore(x, y+3);

		printf(INTERNO_CASELLA_TIPO_E_NUMERO, inizio_codice_colore, tipo_casella, FINE_CODICE_COLORE, numero_casella);
		//"|%s%c%s %2d|"
		spostare_cursore(x, y+4);
		printf(BORDO_SUPERIORE_INFERIORE_CASELLA);
		
		x = x + 5;
		
		if(numero_casella%NUMERO_CASELLE_PER_RIGA == 0 && numero_casella!=dimensione_percorso){
			y = y + 4;
			x = PRIMA_COORDINATA_SCHERMO;
		}		

		numero_casella++;
	}
	spostare_cursore(PRIMA_COORDINATA_SCHERMO, y+5);
	return;
}

record_partita avanzare_turno(record_partita partita){
    int indice_successivo;
    
    indice_successivo = leggere_indice_giocatore_di_turno_record_partita(partita) + 1;

    if(indice_successivo > NUMERO_MASSIMO_GIOCATORI-1){
        indice_successivo = PRIMO_INDICE_ARRAY;
    } else {
    	if(leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), indice_successivo)) == POSIZIONE_GIOCATORE_NON_PARTECIPANTE){
    		indice_successivo = PRIMO_INDICE_ARRAY;
    	}
    }

    partita = scrivere_indice_giocatore_di_turno_record_partita(partita, indice_successivo);

    return partita;
}

record_partita stabilire_primo_giocatore(record_partita partita){
    int dado_1;
    int dado_2;
    int massimo_lancio_dadi;
    int indice_giocatore_iniziale;
    int i, riga;
    
    system("cls");
    stampare_file_di_testo(PERCORSO_FILE_TITOLO);
    printf(MESSAGGIO_STABILIRE_GIOCATORE_INIZIALE);
	printf("%c", CARATTERE_NUOVA_RIGA);
	printf("%c", CARATTERE_NUOVA_RIGA);

    indice_giocatore_iniziale = PRIMO_INDICE_ARRAY;
    massimo_lancio_dadi = INT_MIN;

    i = PRIMO_INDICE_ARRAY;
    while(i < leggere_dimensione_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita))){

        // Stampa il nome del giocatore con il relativo simbolo
        printf(MESSAGGIO_NUMERO_GIOCATORE, i+1);
        stampare_messaggio_simbolo_giocatore(MESSAGGIO_SIMBOLO_GIOCATORE, i);
		printf("%c", CARATTERE_NUOVA_RIGA);

		riga = ottenere_riga_cursore();
        system("pause");

    	// Vegono tirati i dadi
        dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
        dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);

        if((dado_1 + dado_2) > massimo_lancio_dadi){
            massimo_lancio_dadi = dado_1 + dado_2;
            indice_giocatore_iniziale = i;
        }

        // Elimina la riga scritta da system("pause")
        spostare_cursore(PRIMA_COORDINATA_SCHERMO, riga);
        stampare_riga_vuota(riga, NUMERO_COLONNA_MASSIMA);

        // Stampa i valori e il totale dei dadi tirati
        spostare_cursore(PRIMA_COORDINATA_SCHERMO, riga);
        printf(MESSAGGIO_DADI_TIRATI, dado_1, dado_2, dado_1+dado_2);
		printf("%c", CARATTERE_NUOVA_RIGA);
		printf("%c", CARATTERE_NUOVA_RIGA);

        i++;
    }

    // Viene comunicato il giocatore che inizierà la partita
    printf(MESSAGGIO_GIOCATORE_INIZIALE, indice_giocatore_iniziale+1);
	printf("%c", CARATTERE_NUOVA_RIGA);
	printf("%c", CARATTERE_NUOVA_RIGA);

    // Viene impostato il giocatore iniziale come giocatore di turno
    partita = scrivere_indice_giocatore_di_turno_record_partita(partita, indice_giocatore_iniziale);

    system("pause");

    return partita;
}

record_partita applicare_effetto_casella_oca_ponte(record_partita partita, int indice_giocatore, char tipo_casella, bool effetto_contrario){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    char nome_casella[LUNGHEZZA_MASSIMA_NOME_CASELLA];
    int ultimo_lancio_dadi, vecchia_posizione, nuova_posizione;

    // Legge il giocatrore che è finito sulla casella speciale dal record partita
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    vecchia_posizione = leggere_posizione_record_giocatore(giocatore);

    // Legge la somma dell'ultimo lancio dadi del giocatore
    ultimo_lancio_dadi = leggere_ultimo_lancio_dado_1_record_partita(partita) + leggere_ultimo_lancio_dado_2_record_partita(partita);

    // Se deve applicare l'effetto al contrario
    if(effetto_contrario){
    	// Applica l'effetto al contrario
        nuova_posizione = vecchia_posizione - ultimo_lancio_dadi;
    // Altrimenti appplica l'effetto normalmente
    } else {
    	// Applica l'effetto al normale
        nuova_posizione = vecchia_posizione + ultimo_lancio_dadi;
    }

	if(tipo_casella == TIPO_CASELLA_OCA){
		strcpy(nome_casella, NOME_CASELLA_OCA);
	} else {
		strcpy(nome_casella, NOME_CASELLA_PONTE);
	}
    // Mostra le conseguenze dell'effetto della casella all'utente
    printf(MESSAGGIO_CASELLA_SPECIALE_AGGIORNAMENTO_POSIZIONE, vecchia_posizione, nome_casella, nuova_posizione);
	printf("%c", CARATTERE_NUOVA_RIGA);

	// Aggiorna la posizione del giocatore e salva il giocatore all'interno della partita
    giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_pozzo_prigione(record_partita partita, int indice_giocatore, char tipo_casella){

    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    char nome_casella[LUNGHEZZA_MASSIMA_NOME_CASELLA];
    int numero_casella,	i;
    bool trovato = false;

    // Legge il vettore dei giocatori dalla partita
	vet_giocatori = leggere_vet_giocatori_record_partita(partita);

    // Scorre tutti i giocatori fino a quando non trova (se c'è) un giocatore già sulla casella su cui è finito il giocatore di turno
	i = PRIMO_INDICE_ARRAY;
    while(i < NUMERO_MASSIMO_GIOCATORI && trovato == false){

    	// Legge il giocatore dal vettore
        giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, i);

        // Se il giocatore si trova sulla casella speciale ed è bloccato (quindi era un giocatore che c'era già prima)
        if((trovare_tipo_casella_giocatore(partita, indice_giocatore) == tipo_casella) &&
           (leggere_bloccato_record_giocatore(giocatore))){

        	// Sblocca il giocatore che si trovava sulla casella speciale
        	giocatore = scrivere_bloccato_record_giocatore(giocatore, false);

        	// Comunica che il giocatore è stato sbloccato
        	printf(MESSAGGIO_SBLOCCO_ARRIVO_POZZO_PRIGIONE, i+1);
        	stampare_messaggio_simbolo_giocatore(MESSAGGIO_SIMBOLO_GIOCATORE, i);
        	printf("%c", CARATTERE_NUOVA_RIGA);

        	// Salva il giocatore nel vettore dei giocatori
            vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, i, giocatore);

            // Imposto trovato a true in modo da uscire dal ciclo
            trovato = true;
        }

        i++;
    }

    // Legge il giocatore che è appena finito sulla casella pozzo dal vettore dei giocatori
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

    // Ottiene il numero della casella su cui si trova il giocatore
    numero_casella = leggere_posizione_record_giocatore(giocatore);

    // Se il giocatore si trova sulla casella prigione
    if(tipo_casella == TIPO_CASELLA_PRIGIONE){
    	// Assegna a nome_casella il nome della casella prigione
    	strcpy(nome_casella, NOME_CASELLA_PRIGIONE);
    } else{
    	// Assegna a nome_casella il nome della casella pozzo
    	strcpy(nome_casella, NOME_CASELLA_POZZO);
    }

    // Comunica le conseguenze dell'effetto della casella all'utente
    printf(MESSAGGIO_ARRIVO_CASELLA_POZZO_PRIGIONE, numero_casella, nome_casella, SOMMA_DADI_USCITA_PRIGIONE_POZZO_1, SOMMA_DADI_USCITA_PRIGIONE_POZZO_2);
    printf("%c", CARATTERE_NUOVA_RIGA);

    // Blocca il giocatore
    giocatore = scrivere_bloccato_record_giocatore(giocatore, true);

    // Scrive il giocatore nel vettoere e il vettore nella partita
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_locanda(record_partita partita, int indice_giocatore){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    int turni_bloccato,
		numero_casella;

    // Legge il giocatore che è finito sulla casella locanda dalla partita
	vet_giocatori = leggere_vet_giocatori_record_partita(partita);
	giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);


    // L'effetto deve essere applicato solo se il giocatore è appena arrivato sulla casella locanda
    turni_bloccato = leggere_numero_turni_bloccato_record_giocatore(giocatore);

    if(turni_bloccato == NUMERO_TURNI_NON_BLOCCATO_LOCANDA){ // Se i turni bloccato sono 0 vuol dire che il giocatore è appena arrivato sulla casella

		// Applica l'effetto della casella
		giocatore = scrivere_numero_turni_bloccato_record_giocatore(giocatore, TURNI_BLOCCATO_LOCANDA);

		// Legge il numero della casella su cui si trova il giocatore
		numero_casella = leggere_posizione_record_giocatore(giocatore);

		// Mostra all'utente le conseguenze dell'effetto della casella
		printf("%c", CARATTERE_NUOVA_RIGA);
		printf(MESSAGGIO_ARRIVO_CASELLA_LOCANDA, numero_casella, NOME_CASELLA_LOCANDA, TURNI_BLOCCATO_LOCANDA);
		printf("%c", CARATTERE_NUOVA_RIGA);

		// Salva il giocatore nella partita
		vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
		partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    } else {
    	if (turni_bloccato == 0){

			// Srive nel giocatore il numero di turni corrispondente al numero di turni per un giocatore non bloccato
    		giocatore = scrivere_numero_turni_bloccato_record_giocatore(giocatore, NUMERO_TURNI_NON_BLOCCATO_LOCANDA);

    		// Salva il giocatore nella partita
    		vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    		partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);
    	}
    }

    return partita;
}

record_partita applicare_effetto_casella_finale(record_partita partita, int indice_giocatore){

	record_vet_giocatori vet_giocatori;
	record_giocatore giocatore;
	int posizione;

	partita = scrivere_terminata_record_partita(partita, true);

    // Legge la posizione del giocatore per poterla stampare
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    posizione = leggere_posizione_record_giocatore(giocatore);

	printf("%c", CARATTERE_NUOVA_RIGA);
	printf(MESSAGGIO_ARRIVO_CASELLA_FINALE, posizione, NOME_CASELLA_FINE);
	printf("%c", CARATTERE_NUOVA_RIGA);

	aggiornare_classifica(partita, indice_giocatore);
	system("pause");
	stampare_classifica(PERCORSO_FILE_CLASSIFICA);

    return partita;
}

record_partita applicare_effetto_casella_labirinto(record_partita partita, int indice_giocatore){

    record_percorso percorso;
    int dimensione_percorso, vecchia_posizione, nuova_posizione;
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    percorso = leggere_percorso_record_partita(partita);
    dimensione_percorso = leggere_dimensione_record_percorso(percorso);

    // Legge la vecchia posizione del giocatore
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    vecchia_posizione = leggere_posizione_record_giocatore(giocatore);

    // Calcola la nuova posizione del giocatore
    nuova_posizione = calcolare_proporzione(POSIZIONE_ARRIVO_LABIRINTO_90_CASELLE, NUMERO_MASSIMO_CASELLE, dimensione_percorso);

    // Sposta il giocatore in avanti di una casella fino a quando non arriva su una casella normale
    do{

    	// Salva la nuova posizione del giocatore
		giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
		vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
		partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);
		nuova_posizione++;

    }while(trovare_tipo_casella_giocatore(partita, indice_giocatore)!=TIPO_CASELLA_NORMALE);

    // Mostra le conseguenze dell'effetto della casella all'utente
    printf(MESSAGGIO_CASELLA_SPECIALE_AGGIORNAMENTO_POSIZIONE, vecchia_posizione, NOME_CASELLA_LABIRINTO, nuova_posizione);
	printf("%c", CARATTERE_NUOVA_RIGA);

    return partita;
}

record_partita applicare_effetto_casella_scheletro(record_partita partita, int indice_giocatore){

    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    int vecchia_posizione;

    // Legge il giocatore dalla partita
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    vecchia_posizione = leggere_posizione_record_giocatore(giocatore);

    // Applica l'effetto della casella
    giocatore = scrivere_posizione_record_giocatore(giocatore, PRIMA_POSIZIONE_PERCORSO);

    // Mostra le conseguenze dell'effetto della casella all'utente
    printf(MESSAGGIO_CASELLA_SPECIALE_AGGIORNAMENTO_POSIZIONE, vecchia_posizione, NOME_CASELLA_SCHELETRO, PRIMA_POSIZIONE_PERCORSO);
	printf("%c", CARATTERE_NUOVA_RIGA);

    // Riscrive il giocatore nella partita
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita gestire_effetti_caselle_speciali(record_partita partita, int indice_giocatore){

	char tipo_casella_giocatore_di_turno;
	int posizione_giocatore, dimensione_percorso;
	record_giocatore giocatore;


    do{

		tipo_casella_giocatore_di_turno = trovare_tipo_casella_giocatore(partita, indice_giocatore);

		if (tipo_casella_giocatore_di_turno == TIPO_CASELLA_OCA || tipo_casella_giocatore_di_turno == TIPO_CASELLA_PONTE){
			partita = applicare_effetto_casella_oca_ponte(partita, indice_giocatore, tipo_casella_giocatore_di_turno, false);

			// Leggee la dimensinoe del percorso
			dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

			// Legge il giocatore di turno dalla partita
			giocatore = leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), indice_giocatore);

			// Legge la posizione del giocatore
			posizione_giocatore = leggere_posizione_record_giocatore(giocatore);

			// Se il giocatore è finito fuori dal tabellone viene gestito il surplus
			if(posizione_giocatore > dimensione_percorso){
				partita = gestire_surplus(partita, indice_giocatore);
			}

		}else{
			if(tipo_casella_giocatore_di_turno == TIPO_CASELLA_LABIRINTO){
				partita = applicare_effetto_casella_labirinto(partita, indice_giocatore);
			}else{
				if(tipo_casella_giocatore_di_turno == TIPO_CASELLA_POZZO || tipo_casella_giocatore_di_turno == TIPO_CASELLA_PRIGIONE){
					partita = applicare_effetto_casella_pozzo_prigione(partita, indice_giocatore, tipo_casella_giocatore_di_turno);
				}else{
					if(tipo_casella_giocatore_di_turno == TIPO_CASELLA_LOCANDA){
						partita = applicare_effetto_casella_locanda(partita, indice_giocatore);
					}else{
						if(tipo_casella_giocatore_di_turno == TIPO_CASELLA_SCHELETRO){
							partita = applicare_effetto_casella_scheletro(partita, indice_giocatore);
						}else{
							if (tipo_casella_giocatore_di_turno == TIPO_CASELLA_FINE){
								partita = applicare_effetto_casella_finale(partita, indice_giocatore);
							}
						}
					}
				}
			}
		}
    }while(tipo_casella_giocatore_di_turno != TIPO_CASELLA_NORMALE &&
       	   tipo_casella_giocatore_di_turno != TIPO_CASELLA_LOCANDA &&
      	   tipo_casella_giocatore_di_turno != TIPO_CASELLA_POZZO &&
      	   tipo_casella_giocatore_di_turno != TIPO_CASELLA_PRIGIONE &&
		   leggere_terminata_record_partita(partita) == false);
    return partita;
}

record_partita gestire_scelta_menu_partita(record_partita partita, int scelta){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore_di_turno;
    char tipo_casella_giocatore_di_turno,
		 nome_casella[LUNGHEZZA_MASSIMA_NOME_CASELLA];
    int indice_giocatore_di_turno,
		turni_bloccato;

    if(scelta == SCELTA_TIRARE_I_DADI){

        // Aggiorna il numero di tiri del giocatore
        vet_giocatori = leggere_vet_giocatori_record_partita(partita);
        indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
        giocatore_di_turno = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore_di_turno);
        giocatore_di_turno = scrivere_numero_dadi_lanciati_record_giocatore(giocatore_di_turno, (leggere_numero_dadi_lanciati_record_giocatore(giocatore_di_turno) + 1));
        vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore_di_turno, giocatore_di_turno);
        partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

        // Legge il tipo della casella su cui si trova il giocatore di turno
        tipo_casella_giocatore_di_turno = trovare_tipo_casella_giocatore(partita, indice_giocatore_di_turno);

        // Decide cosa fare in base alla posizione del giocatore
        if(leggere_posizione_record_giocatore(giocatore_di_turno) == POSIZIONE_INIZIO_PARTITA){
        	// Se il giocatore non ha mai tirato i dadi lancia i "primi dadi"
            partita = lanciare_primi_dadi(partita, indice_giocatore_di_turno);
        } else {
        	// Se il giocatore si trova sulla casella locanda e dove rimanere bloccato ancora per qualche turno
        	if (tipo_casella_giocatore_di_turno == TIPO_CASELLA_LOCANDA &&
        		leggere_numero_turni_bloccato_record_giocatore(giocatore_di_turno) > 0){

        		// Decrementa i turni in cui il giocatore dovrà rimanere bloccato
        		turni_bloccato = leggere_numero_turni_bloccato_record_giocatore(giocatore_di_turno);
        		turni_bloccato - 1;
        		giocatore_di_turno = scrivere_numero_turni_bloccato_record_giocatore(giocatore_di_turno, turni_bloccato);
        		vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore_di_turno, giocatore_di_turno);
        		partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

        		// Comunica all'utente per quanti turni rimarrà bloccato
        		printf("%c", CARATTERE_NUOVA_RIGA);
        		printf(MESSAGGIO_CASELLA_SPECIALE_BLOCCATO, NOME_CASELLA_LOCANDA);
        		printf("%c", CARATTERE_NUOVA_RIGA);
        		printf(MESSAGGIO_NUMERO_TURNI_BLOCCATO, turni_bloccato);
        		printf("%c", CARATTERE_NUOVA_RIGA);
        		if (turni_bloccato == 0){
        			printf(MESSAGGIO_PROSEGUIRE_PROSSIMO_TURNO);
                	printf("%c", CARATTERE_NUOVA_RIGA);
        		}

			} else {
				// Se il giocatore è bloccato (quindi se si trova sulla casella pozzo o sulla casella prigione)
				if (leggere_bloccato_record_giocatore(giocatore_di_turno)){

					if(tipo_casella_giocatore_di_turno == TIPO_CASELLA_POZZO){
						strcpy(nome_casella, NOME_CASELLA_POZZO);
					} else {
						strcpy(nome_casella, NOME_CASELLA_PRIGIONE);
					}

					// Comunica al giocatore che è bloccato a a causa del pozzo o della prigione
					printf("%c", CARATTERE_NUOVA_RIGA);
	        		printf(MESSAGGIO_CASELLA_SPECIALE_BLOCCATO, nome_casella);
	        		printf("%c", CARATTERE_NUOVA_RIGA);
	        		printf(MESSAGGIO_ISTRUZIONI_USCITA_POZZO_PRIGIONE, SOMMA_DADI_USCITA_PRIGIONE_POZZO_1, SOMMA_DADI_USCITA_PRIGIONE_POZZO_2, nome_casella);
	        		printf("%c", CARATTERE_NUOVA_RIGA);

	        		system("pause");

	        		partita = lanciare_dadi_pozzo_prigione(partita, indice_giocatore_di_turno);

				} else {
					// Altrimenti alncia i dadi normalmente
					partita = lanciare_dadi(partita, indice_giocatore_di_turno);
				}

			}
        }

        // Legge il tipo della casella su cui si trova il giocatore di turno
        tipo_casella_giocatore_di_turno = trovare_tipo_casella_giocatore(partita, indice_giocatore_di_turno);

        // Se il giocatore finisce su una casella speciale
        if(tipo_casella_giocatore_di_turno != TIPO_CASELLA_NORMALE){
        	// Gestisce l'effetto della casella speciale
        	partita = gestire_effetti_caselle_speciali(partita, indice_giocatore_di_turno);
        }
        system("pause");

        // Stampa il percorso
        stampare_percorso(partita);
        system("pause");
        partita = avanzare_turno(partita);

    }else{
        if(scelta == SCELTA_CREARE_NUOVA_PARTITA){
            // Imposto il flag di nuova_partita a true
            partita = scrivere_nuova_partita_record_partita(partita, true);
            // Imposto il flag di partita terminata a true
            partita = scrivere_terminata_record_partita(partita, true);
        }else{
            if(scelta == SCELTA_SALVARE_PARTITA){
                // Salva la partita
            	salvare_partita(PERCORSO_FILE_PARTITE_SALVATE, partita);
            	system("pause");
            }else{
				if(scelta == SCELTA_ABBANDONARE_PARTITA || scelta == SCELTA_USCIRE_DAL_MENU){
					// Imposto il flag di abbandona partita a true ed esco
					partita = scrivere_terminata_record_partita(partita, true);
				}
            }
        }
    }

    return partita;
}
