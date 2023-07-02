#include "giocare_partita.h"


#define PERCORSO_FILE_PARTITE_SALVATE "..\\src\\file_di_gioco\\partite_salvate.bin"

#define MESSAGGIO_STABILIRE_GIOCATORE_INIZIALE "Tutti i giocatori tireranno i dadi per stabilire chi sara' il primo giocatore.\nIniziera' il giocatore che ottera' il punteggio piu' alto (in caso di parita'\niniziera' il primo giocatore che ottenuto tale punteggio):"
#define MESSAGGIO_DADI_TIRATI "Primo dado: %d  	       Secondo dado: %d\n             Totale: %2d"
#define MESSAGGIO_GIOCATORE_INIZIALE "Iniziera' il giocatore %d."
#define MESSAGGIO_NUMERO_GIOCATORE "Giocatore %d "
#define MESSAGGIO_SIMBOLO_GIOCATORE "(%c):"
#define MESSAGGIO_NUOVA_POSIZIONE "Ti sei spostato dalla casella %d alla casella %d"
#define MESSAGGIO_GIOCATORE_DI_TURNO "E' il turno del giocatore %d "
#define MESSAGGIO_CASELLA_ATTUALE "ti trovi sulla casella numero %d."

#define MESSAGGIO_CASELLA_SPECIALE_AGGIORNAMENTO_POSIZIONE "La casella numero %d era una casella speciale, per il suo effetto sei finito\nsulla casella %d."
#define MESSAGGIO_CASELLA_SPECIALE_LOCANDA "Sei finito sulla casella locanda, rimarrai bloccato per %d turni."
#define MESSAGGIO_CASELLA_SPECIALE_FINE "Hai vinto!"

#define SOMMA_DADI_USCITA_PRIGIONE_POZZO_1 5
#define SOMMA_DADI_USCITA_PRIGIONE_POZZO_2 7

#define PRIMO_DADO_COMBINAZIONE_4_5 4
#define SECONDO_DADO_COMBINAZIONE_4_5 5
#define ARRIVO_PRIMO_LANCIO_4_5 53

#define PRIMO_DADO_COMBINAZIONE_3_6 3
#define SECONDO_DADO_COMBINAZIONE_3_6 6
#define ARRIVO_PRIMO_LANCIO_3_6 26

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
    if(indice_giocatore_di_turno == GIOCATORE_NON_STABILITO){
    	// Se non è stato ancora fatto stabilisce il primo giocatore
        partita = stabilire_primo_giocatore(partita);
    }

    while(!(leggere_terminata_record_partita(partita) ||
			leggere_nuova_partita_record_partita(partita) ||
			leggere_abbandona_partita_record_partita(partita) ||
			leggere_salva_partita_record_partita(partita))){

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
		riga = stampare_file_di_testo(PERCORSO_FILE_MENU_PARTITA);
		printf("\n");
		riga++;

	    // Recupera e mostra informazioni relative al giocatore di turno e alla sua posizione
        indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
        printf(MESSAGGIO_GIOCATORE_DI_TURNO, indice_giocatore_di_turno+1);
        stampare_messaggio_simbolo_giocatore(MESSAGGIO_SIMBOLO_GIOCATORE, indice_giocatore_di_turno);
        printf("\n");
        riga++;
        giocatore = leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), indice_giocatore_di_turno);
        numero_casella = leggere_posizione_record_giocatore(giocatore);
        printf(MESSAGGIO_CASELLA_ATTUALE, numero_casella);
        printf("\n\n");
        riga = riga + 2;

        // Chiede al giocatore di effettuare la scelta
        scelta = chiedere_intero("Inserisci la scelta: ", SCELTA_USCIRE_DAL_MENU, SCELTA_ABBANDONARE_PARTITA, riga, PRIMA_COORDINATA_SCHERMO);// NUMERO MAGICO

        //Gestisce la scelta effettuata
        partita = gestire_scelta_partita(partita, scelta);

	} while(scelta == SCELTA_TIRARE_I_DADI &&
			leggere_terminata_record_partita(partita) == false);

    return partita;
}

int gestire_surplus(int posizione_surplus, int dimensione_percorso){
	// il giocatore retrocede delle caselle in surplus
	posizione_surplus = dimensione_percorso - (posizione_surplus - dimensione_percorso);
	return posizione_surplus;
}

record_partita lanciare_primi_dadi(record_partita partita, int indice_giocatore){
    
    int dado_1,
		dado_2,
		vecchia_posizione = PRIMA_POSIZIONE_PERCORSO - 1,
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
    dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

    //viene calcolata la nuova posizione del giocatore in base ai dadi tirati
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
    printf("\n");
    printf(MESSAGGIO_NUMERO_GIOCATORE, indice_giocatore+1);
    stampare_messaggio_simbolo_giocatore(MESSAGGIO_SIMBOLO_GIOCATORE, indice_giocatore);
    printf("\n");
    printf(MESSAGGIO_DADI_TIRATI, dado_1, dado_2, dado_1+dado_2);
    printf("\n\n");
    // Viene comunicata la nuova posizione sul tabellone all'utente
    printf(MESSAGGIO_NUOVA_POSIZIONE, vecchia_posizione, nuova_posizione);
    printf("\n");

    return partita;
}

record_partita lanciare_dadi(record_partita partita, int indice_giocatore){ // BISOGNA COMUNICARE ALL'UTENTE SE E' BLOCCATO ECC...
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

    // Viene calcolata la somma dei dadi
    somma_dadi = dado_1 + dado_2;

    // Vengono salvati i valori degli ultimi dadi tirati
    partita = scrivere_ultimo_lancio_dado_1_record_partita(partita, dado_1);
    partita = scrivere_ultimo_lancio_dado_2_record_partita(partita, dado_2);

    // Legge il giocatore dalla partita
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

    if((leggere_bloccato_record_giocatore(giocatore) == false) ||
       (leggere_bloccato_record_giocatore(giocatore) == true && (somma_dadi == SOMMA_DADI_USCITA_PRIGIONE_POZZO_1 || somma_dadi == SOMMA_DADI_USCITA_PRIGIONE_POZZO_2))){

    	// Legge la dimensione del percorso
    	dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

        // Legge la vecchia posizione e calcola la nuova posizione dele giocatore
        vecchia_posizione = leggere_posizione_record_giocatore(giocatore);
        nuova_posizione = vecchia_posizione + dado_1 + dado_2;

        // Se la nuova posizione del giocatore supera la fine del tabellone
		if(nuova_posizione > dimensione_percorso){
			nuova_posizione = gestire_surplus(nuova_posizione, dimensione_percorso);
		}

        // Aggiorna la posizione alli'interno del giocatore e lo riscrive nella partita
        giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
        vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
        partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);
    }

    // Vengono comunicati i valori e il totale dei dadi all'utente
	printf("\n");
	printf(MESSAGGIO_NUMERO_GIOCATORE, indice_giocatore+1);
	stampare_messaggio_simbolo_giocatore(MESSAGGIO_SIMBOLO_GIOCATORE, indice_giocatore);
	printf("\n");
	printf(MESSAGGIO_DADI_TIRATI, dado_1, dado_2, dado_1+dado_2);
	printf("\n\n");
	// Viene comunicata la nuova posizione sul tabellone all'utente
	printf(MESSAGGIO_NUOVA_POSIZIONE, vecchia_posizione, nuova_posizione);
	printf("\n");

    return partita;
}

void stampare_percorso(record_partita partita){
	int posizione_giocatore_1,
		posizione_giocatore_2,
		posizione_giocatore_3,
		posizione_giocatore_4,
		dimensione,
		x = PRIMA_COORDINATA_SCHERMO,
		y = PRIMA_COORDINATA_SCHERMO,
		i = PRIMO_INDICE_ARRAY + 1;

	char caselle[DIMENSIONE_MASSIMA_PERCORSO];

	posizione_giocatore_1 = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), INDICE_GIOCATORE_1));
	posizione_giocatore_2 = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), INDICE_GIOCATORE_2));
	posizione_giocatore_3 = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), INDICE_GIOCATORE_3));
	posizione_giocatore_4 = leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), INDICE_GIOCATORE_4));

	copiare_caselle_percorso(leggere_percorso_record_partita(partita), caselle);
	dimensione = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

	system("cls");
	printf("%s", PRIMA_RIGA_TABELLONE);
	while(i<=dimensione){
		spostare_cursore(x,y);
		if(i>NUMERO_CASELLE_PER_RIGA){
			printf("%s", BORDO_INFERIORE_SUPERIORE_CASELLA);
		}
		
		spostare_cursore(x, y+1);
		if(posizione_giocatore_1 == i){
			printf("%c%c  ", BORDO_LATERALE_CASELLA, SIMBOLO_GIOCATORE_1);
		}
        else{
			printf("%c   ", BORDO_LATERALE_CASELLA);
		}

		if(posizione_giocatore_2 == i){
			printf("%c%c", SIMBOLO_GIOCATORE_2, BORDO_LATERALE_CASELLA);
		}
        else{
			printf(" %c", BORDO_LATERALE_CASELLA);
		}

		spostare_cursore(x, y+2);
		if(posizione_giocatore_3 == i){
			printf("%c%c  ", BORDO_LATERALE_CASELLA, SIMBOLO_GIOCATORE_3);
		}
        else{
			printf("%c   ", BORDO_LATERALE_CASELLA);
		}
		if(posizione_giocatore_4 == i){
			printf("%c%c", SIMBOLO_GIOCATORE_4, BORDO_LATERALE_CASELLA);
		}
        else{
			printf(" %c", BORDO_LATERALE_CASELLA);
        }
		
		spostare_cursore(x, y+3);
		if(caselle[i-1]!=CASELLA_NORMALE){
			printf("%c%c %2d%c", BORDO_LATERALE_CASELLA, caselle[i-1], i, BORDO_LATERALE_CASELLA);
		} else {
			printf("%c  %2d%c", BORDO_LATERALE_CASELLA, i, BORDO_LATERALE_CASELLA);
		}

		spostare_cursore(x, y+4);
		printf("%s", BORDO_INFERIORE_SUPERIORE_CASELLA);
		
		x = x + 5;
		
		if(i%NUMERO_CASELLE_PER_RIGA == 0 && i!=dimensione){
			y = y + 4;
			x = PRIMA_COORDINATA_SCHERMO;
		}		

		i++;
	}
	spostare_cursore(PRIMA_COORDINATA_SCHERMO, y+5);
	return;
}

record_partita avanzare_turno(record_partita partita){ //VORREI METTERE UN OR MA LEGGEREBBE ANCHE LE POSIZIONI MAGGIORI DELLA GRANDEZZA DEL VETTORE
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
    riga = stampare_file_di_testo(PERCORSO_FILE_TITOLO);
    printf(MESSAGGIO_STABILIRE_GIOCATORE_INIZIALE);
    printf("\n\n");
    riga = riga + 4;

    indice_giocatore_iniziale = PRIMO_INDICE_ARRAY;
    massimo_lancio_dadi = 0;

    i = PRIMO_INDICE_ARRAY;
    while(i < leggere_dimensione_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita))){

        // Stampa il nome del giocatore con il relativo simbolo
        printf(MESSAGGIO_NUMERO_GIOCATORE, i+1);
        stampare_messaggio_simbolo_giocatore(MESSAGGIO_SIMBOLO_GIOCATORE, i);
        printf("\n");
        riga++;

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
        printf("\n\n");
        riga = riga + 3;

        i++;
    }

    // Viene comunicato il giocatore che inizierà la partita
    printf(MESSAGGIO_GIOCATORE_INIZIALE, indice_giocatore_iniziale+1);
    printf("\n\n");

    // Viene impostato il giocatore iniziale come giocatore di turno
    partita = scrivere_indice_giocatore_di_turno_record_partita(partita, indice_giocatore_iniziale);

    system("pause");

    return partita;
}

record_partita applicare_effetto_casella_oca_ponte(record_partita partita, int indice_giocatore){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    int ultimo_lancio_dadi, vecchia_posizione, nuova_posizione, dimensione_percorso;

    // Legge il giocatrore che è finito sulla casella speciale dal record partita
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    vecchia_posizione = leggere_posizione_record_giocatore(giocatore);

    // Legge la vecchia posizione del giocatore la nuova posizione del giocatore
    ultimo_lancio_dadi = leggere_ultimo_lancio_dado_1_record_partita(partita) + leggere_ultimo_lancio_dado_2_record_partita(partita);
    nuova_posizione = vecchia_posizione + ultimo_lancio_dadi;

    // Legge la dimensione del percorso
   	dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

    // Se la nuova posizione del giocatore supera la fine del tabellone
	if(nuova_posizione > dimensione_percorso){
		nuova_posizione = gestire_surplus(nuova_posizione, dimensione_percorso);
	}

    // Mostra le conseguenze dell'effetto della casella all'utente
    printf(MESSAGGIO_CASELLA_SPECIALE_AGGIORNAMENTO_POSIZIONE, vecchia_posizione, nuova_posizione);
    printf("\n");

    // Riscrive il giocatore all'interno della partita
    giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_pozzo_prigione(record_partita partita, int indice_giocatore, char tipo_casella){ //DA RIVEDERE

    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    int trovato = false,
    	i = PRIMO_INDICE_ARRAY;

    // Scorre tutti i giocatori
    while(i < NUMERO_MASSIMO_GIOCATORI && trovato == false){

    	// Legge il giocatore dalla partita
    	vet_giocatori = leggere_vet_giocatori_record_partita(partita);
        giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, i);

        // Se il giocatore si trova sulla casella pozzo ed è bloccato (quindi era un giocatore che c'era già prima)
        if((trovare_tipo_casella_giocatore(partita, indice_giocatore) == tipo_casella) && (leggere_bloccato_record_giocatore(giocatore))){

        	// Sblocca il giocatore che si trovava sulla casella pozzo
        	giocatore = scrivere_bloccato_record_giocatore(giocatore, false);

        	// Salva il giocatore nel vettore dei giocatori
            vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, i, giocatore);

            // Imposto trovato a true in modo da uscire dal ciclo
            trovato = true;
        }

        i++;
    }

    // Legge il giocatore che è appena finito sulla casella pozzo dal vettore dei giocatori
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

    // Blocca il giocatore
    giocatore = scrivere_bloccato_record_giocatore(giocatore, true);

    //Riscrive il giocatore nella partita
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_locanda(record_partita partita, int indice_giocatore){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    int turni_bloccato;

    // L'effetto deve essere applicato solo se il giocatore è appena arrivato sulla casella locanda
    turni_bloccato = leggere_numero_turni_bloccato_record_giocatore(giocatore);
    if(turni_bloccato == 0){ // Se i turni bloccato sono 0 vuol dire che il giocatore è appena arrivato sulla casella

    // Legge il giocatore che è finito sulla casella locanda dalla partita
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

    // Applica l'effetto della casella
    giocatore = scrivere_numero_turni_bloccato_record_giocatore(giocatore, TURNI_BLOCCATO_LOCANDA);

    // Mostra all'utente le conseguenze dell'effetto della casella
    printf(MESSAGGIO_CASELLA_SPECIALE_LOCANDA, TURNI_BLOCCATO_LOCANDA);
    printf("\n");

    // Salva il giocatore nella partita
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    }

    return partita;
}

record_partita applicare_effetto_casella_finale(record_partita partita, int indice_giocatore){

	partita = scrivere_terminata_record_partita(partita, true);

	printf("\n");
	printf(MESSAGGIO_CASELLA_SPECIALE_FINE);
	printf("\n");

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
    nuova_posizione = calcolare_proporzione(ARRIVO_LABIRINTO, NUMERO_MASSIMO_CASELLE, dimensione_percorso);

    // Mostra le conseguenze dell'effetto della casella all'utente
    printf(MESSAGGIO_CASELLA_SPECIALE_AGGIORNAMENTO_POSIZIONE, vecchia_posizione, nuova_posizione);
    printf("\n");

    // Salva la nuova posizione del giocatore
    giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

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
    printf(MESSAGGIO_CASELLA_SPECIALE_AGGIORNAMENTO_POSIZIONE, vecchia_posizione, PRIMA_POSIZIONE_PERCORSO);
    printf("\n");

    // Riscrive il giocatore nella partita
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita gestire_effetti_caselle_speciali(record_partita partita, int indice_giocatore){

	char tipo_casella_giocatore_di_turno;

    do{

		tipo_casella_giocatore_di_turno = trovare_tipo_casella_giocatore(partita, indice_giocatore);

		if (tipo_casella_giocatore_di_turno == CASELLA_OCA || tipo_casella_giocatore_di_turno == CASELLA_PONTE){
			partita = applicare_effetto_casella_oca_ponte(partita, indice_giocatore);
			}else{
				if(tipo_casella_giocatore_di_turno == CASELLA_LABIRINTO){
					partita = applicare_effetto_casella_labirinto(partita, indice_giocatore);
					}else{
						if(tipo_casella_giocatore_di_turno == CASELLA_POZZO || tipo_casella_giocatore_di_turno == CASELLA_PRIGIONE){
							partita = applicare_effetto_casella_pozzo_prigione(partita, indice_giocatore, tipo_casella_giocatore_di_turno);
							}else{
								if(tipo_casella_giocatore_di_turno == CASELLA_LOCANDA){
									partita = applicare_effetto_casella_locanda(partita, indice_giocatore);
									}else{
										if(tipo_casella_giocatore_di_turno == CASELLA_SCHELETRO){
											partita = applicare_effetto_casella_scheletro(partita, indice_giocatore);
											}else{
												if (tipo_casella_giocatore_di_turno == CASELLA_FINE){
													partita = applicare_effetto_casella_finale(partita, indice_giocatore);
													}
											}
									}
							}
					}
			}
    }while(tipo_casella_giocatore_di_turno != CASELLA_NORMALE &&
       	   tipo_casella_giocatore_di_turno != CASELLA_LOCANDA &&
      	   tipo_casella_giocatore_di_turno != CASELLA_POZZO && // DA RIVEDERE
      	   tipo_casella_giocatore_di_turno != CASELLA_PRIGIONE && // DA RIVEDERE
		   leggere_terminata_record_partita(partita) == false);
    return partita;
}

record_partita gestire_scelta_partita(record_partita partita, int scelta){
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore_di_turno;
    int indice_giocatore_di_turno;

    if(scelta == SCELTA_TIRARE_I_DADI){

        // Tira i dadi e aggiorna i tiri del giocatore
        vet_giocatori = leggere_vet_giocatori_record_partita(partita);
        indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
        giocatore_di_turno = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore_di_turno);
        giocatore_di_turno = scrivere_numero_dadi_lanciati_record_giocatore(giocatore_di_turno, (leggere_numero_dadi_lanciati_record_giocatore(giocatore_di_turno) + 1));
        vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore_di_turno, giocatore_di_turno);
        partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

        // Decide cosa fare in base alla posizione del giocatore
        if(leggere_posizione_record_giocatore(giocatore_di_turno) == (PRIMA_POSIZIONE_PERCORSO-1)){
        	// Se il giocatore non ha mai tirato i dadi lancia i "primi dadi"
            partita = lanciare_primi_dadi(partita, indice_giocatore_di_turno);
        }else{
        	// Altrimenti alncia i dadi normalmente
        	partita = lanciare_dadi(partita, indice_giocatore_di_turno);
        }
        if(trovare_tipo_casella_giocatore(partita, indice_giocatore_di_turno) != CASELLA_NORMALE){
        	// Se il giocatore capita su una casella speciale ne gestisce l'effetto
        	partita = gestire_effetti_caselle_speciali(partita, indice_giocatore_di_turno);
        }
        system("pause");

        //stampa il percorso
        stampare_percorso(partita);
        system("pause");
        partita = avanzare_turno(partita);

    }else{
        if(scelta == SCELTA_CREARE_NUOVA_PARTITA){
            //imposto il flag a true ed esco
            partita = scrivere_nuova_partita_record_partita(partita, true);
        }else{
            if(scelta == SCELTA_SALVARE_PARTITA){
                // salvare partita
            	salvare_partita(PERCORSO_FILE_PARTITE_SALVATE, partita);
            	system("pause");
                partita = scrivere_nuova_partita_record_partita(partita, true);
            }else{
				if(scelta == SCELTA_ABBANDONARE_PARTITA || scelta == SCELTA_USCIRE_DAL_MENU){
					// imposto il flag di abbandona partita a true ed esco
					partita = scrivere_abbandona_partita_record_partita(partita, true);
				}
            }
        }
    }

    return partita;
}
