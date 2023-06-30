#include "giocare_partita.h"

#define MESSAGGIO_STABILIRE_GIOCATORE_INIZIALE "Tutti i giocatori tireranno i dadi per stabilire chi sara' il primo giocatore.\nIniziera' il giocatore che ottera' il punteggio piu' alto (in caso di parita'\niniziera' il primo giocatore che ottenuto tale punteggio):"
#define MESSAGGIO_DADI_TIRATI "Primo dado: %d  	       Secondo dado: %d\n             Totale: %2d"
#define MESSAGGIO_GIOCATORE_INIZIALE "Iniziera' il giocatore %d."
#define MESSAGGIO_NUMERO_GIOCATORE "Giocatore %d "
#define MESSAGGIO_SIMBOLO_GIOCATORE "(%c):"
#define MESSAGGIO_NUOVA_POSIZIONE "Ti sei spostato dalla casella %d alla casella %d"
#define MESSAGGIO_GIOCATORE_DI_TURNO "E' il turno del giocatore %d "
#define MESSAGGIO_CASELLA_ATTUALE "ti trovi sulla casella numero %d."

void stampare_messaggio_simbolo_giocatore(char* messaggio_simbolo_giocatore, int indice_giocatore){ //da aggiungere in pseudo
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

    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    numero_casella = leggere_posizione_record_giocatore(giocatore);
    percorso = leggere_percorso_record_partita(partita);
    tipo_casella = leggere_casella_record_percorso(percorso, numero_casella);

    return tipo_casella;
}

record_partita applicare_effetto_casella_labirinto(record_partita partita, int indice_giocatore){
    
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

record_partita applicare_effetto_casella_prigione(record_partita partita, int indice_giocatore){
    
    int i;
    int trovato;
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    
    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    trovato = false;
    i = PRIMO_INDICE_ARRAY;
    while(i < NUMERO_MASSIMO_GIOCATORI && !trovato){
        giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, i);

        if(trovare_tipo_casella_giocatore(partita, i) == CASELLA_PRIGIONE && leggere_bloccato_record_giocatore(giocatore)){
            giocatore = scrivere_bloccato_record_giocatore(giocatore, false);
            vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, i, giocatore);
            trovato = true;
        }

        i++;
    }

    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    giocatore = scrivere_bloccato_record_giocatore(giocatore, true);
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);

    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita applicare_effetto_casella_scheletro(record_partita partita, int indice_giocatore){
    
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);

    giocatore = scrivere_posizione_record_giocatore(giocatore, PRIMA_POSIZIONE_PERCORSO);

    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);

    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}

record_partita giocare_partita(record_partita partita){

    int scelta, riga, indice_giocatore_di_turno, numero_casella;

    // Mostra il percorso all'utente
    stampare_percorso(partita);
    system("pause");

    // Controlla se bisogna ancora stabilire il primo giocatore
    indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
    numero_casella = leggere_casella_record_percorso(leggere_percorso_record_partita(partita), indice_giocatore_di_turno);
    if(indice_giocatore_di_turno == GIOCATORE_NON_STABILITO){
    	// Se non è stato ancora fatto stabilisce il primo giocatore
        partita = stabilire_primo_giocatore(partita);
    }

    while(!leggere_terminata_record_partita(partita) &&
           !leggere_nuova_partita_record_partita(partita) &&
           !leggere_abbandona_partita_record_partita(partita) &&
           !leggere_salva_partita_record_partita(partita)){

    	// Stampa il menu della partita
    	system("cls");
	    spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
	    riga = stampare_file_di_testo(PERCORSO_FILE_MENU_PARTITA);
	    printf("\n");
	    riga++;

	    // Mostra informazioni relative al giocatore di turno e alla sua posizione
        indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
        printf(MESSAGGIO_GIOCATORE_DI_TURNO, indice_giocatore_di_turno+1);
        stampare_messaggio_simbolo_giocatore(MESSAGGIO_SIMBOLO_GIOCATORE, indice_giocatore_di_turno);
        printf("\n");
        riga++;
        printf(MESSAGGIO_CASELLA_ATTUALE, numero_casella);
        printf("\n\n");
        riga = riga + 2;

        // Chiede al giocatore di effettuare la scelta
        scelta = chiedere_intero("Inserisci la scelta: ", SCELTA_USCIRE_DAL_MENU, SCELTA_ABBANDONARE_PARTITA, riga, PRIMA_COORDINATA_SCHERMO);// NUMERO MAGICO

        //Gestisce la scelta effettuata
        partita = gestire_scelta_partita(partita, scelta);
    }

    return partita;
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
    giocatore = leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), indice_giocatore);
    dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

    //viene calcolata la nuova posizione del giocatore in base ai dadi tirati
    if((dado_1 == 5 && dado_2 == 4)||(dado_1 == 4 && dado_2 == 5)){
    	nuova_posizione = calcolare_proporzione(ARRIVO_PRIMO_LANCIO_4_5, NUMERO_MASSIMO_CASELLE, dimensione_percorso);
    }
    else if((dado_1 == 6 && dado_2 == 3)||(dado_1 == 3 && dado_2 == 6)){
    	nuova_posizione = calcolare_proporzione(ARRIVO_PRIMO_LANCIO_3_6, NUMERO_MASSIMO_CASELLE, dimensione_percorso);
    }
    else {
    	nuova_posizione = dado_1+dado_2;
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
    // Viene comunicata la nuova casella all'utente
    printf(MESSAGGIO_NUOVA_POSIZIONE, vecchia_posizione, nuova_posizione);
    printf("\n\n");

    system("pause");

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

record_partita avanzare_turno(record_partita partita){
    int indice_successivo;
    
    indice_successivo = leggere_indice_giocatore_di_turno_record_partita(partita) + 1;

    if(leggere_posizione_record_giocatore(leggere_giocatore_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita), indice_successivo)) == POSIZIONE_GIOCATORE_NON_PARTECIPANTE){
        indice_successivo = PRIMO_INDICE_ARRAY;
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
        stampare_riga_vuota(riga);

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

record_partita gestire_menu_nuova_partita(char* percorso_file_menu_nuova_partita){
    int nuova_partita, scelta, riga;
    record_partita partita;

    nuova_partita = false; //?????????????????????????????????????????????????????
    
    do {
        if(nuova_partita){ //?????????????????????????????????????????????????????
            partita = gestire_scelta_nuova_partita(scelta); 
        } else {
        	system("cls");
        	spostare_cursore(PRIMA_COORDINATA_SCHERMO, PRIMA_COORDINATA_SCHERMO);
            riga = stampare_file_di_testo(percorso_file_menu_nuova_partita);
            scelta = chiedere_intero("Inserisci la scelta: ", SCELTA_USCIRE_DAL_MENU, 1, (riga+1), PRIMA_COORDINATA_SCHERMO);  //NUMERO MAGICO
            partita = gestire_scelta_nuova_partita(scelta); 
        }
        
        if(leggere_nuova_partita_record_partita(partita)){
            nuova_partita = true;
        } else {
            if(leggere_abbandona_partita_record_partita(partita) == false){
                scelta = SCELTA_USCIRE_DAL_MENU;
            }
        }
    } while(scelta != SCELTA_USCIRE_DAL_MENU);

    return partita;
}

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
    int trovato = false;
    int i = PRIMO_INDICE_ARRAY;

    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;

    while(i<=NUMERO_MASSIMO_GIOCATORI && trovato == false){
        giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, i);
        if((trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_POZZO) && (leggere_bloccato_record_giocatore(giocatore) == true)){
            giocatore = scrivere_bloccato_record_giocatore(giocatore, false);
            vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, i, giocatore);
            trovato = true;
        }
        i=i+1;
    }
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    giocatore = scrivere_bloccato_record_giocatore(giocatore, true);
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
    partita = scrivere_terminata_record_partita(partita, true);

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
    
    if((leggere_bloccato_record_giocatore(giocatore) == false) || (leggere_bloccato_record_giocatore(giocatore) == true && ( somma_dadi == 5 || somma_dadi == 7))){
        dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));
        vecchia_posizione = leggere_posizione_record_giocatore(giocatore);
        nuova_posizione = vecchia_posizione + dado_1 + dado_2;
        if(nuova_posizione > dimensione_percorso){
        	nuova_posizione = dimensione_percorso - (nuova_posizione - dimensione_percorso);
        }
        giocatore = scrivere_posizione_record_giocatore(giocatore, nuova_posizione);
        vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
        partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);
    }
    return partita;
}

record_partita gestire_effetti_caselle_speciali(record_partita partita, int indice_giocatore){
    if (trovare_tipo_casella_giocatore(partita, indice_giocatore)  == CASELLA_OCA || trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_PONTE){
        partita = applicare_effetto_casella_oca_ponte(partita, indice_giocatore);
        }else{
            if(trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_LABIRINTO){
                partita = applicare_effetto_casella_labirinto(partita, indice_giocatore);
                }else{
                    if(trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_POZZO){
                        partita = applicare_effetto_casella_pozzo(partita, indice_giocatore);
                        }else{
                            if (trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_PRIGIONE){
                                partita = applicare_effetto_casella_prigione(partita, indice_giocatore);
                                }else{  
                                    if(trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_LOCANDA){partita = applicare_effetto_casella_locanda(partita, indice_giocatore);
                                    }else{ 
                                        if(trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_SCHELETRO){
                                            partita = applicare_effetto_casella_scheletro(partita, indice_giocatore);
                                            }else{
                                                if (trovare_tipo_casella_giocatore(partita, indice_giocatore) == CASELLA_FINE){
                                                }else{
                                                    partita = applicare_effetto_casella_finale(partita, indice_giocatore);
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
    record_giocatore giocatore_di_turno;
    int indice_giocatore_di_turno;

    if(scelta == SCELTA_TIRARE_I_DADI){
        // Tira i dadi e aggiorna i tiri del giocatore, (potrebbe terminare la partita)
        vet_giocatori = leggere_vet_giocatori_record_partita(partita);
        indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
        giocatore_di_turno = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore_di_turno);
        giocatore_di_turno = scrivere_numero_dadi_lanciati_record_giocatore(giocatore_di_turno, (leggere_numero_dadi_lanciati_record_giocatore(giocatore_di_turno) + 1));
        vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore_di_turno, giocatore_di_turno);
        partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

        if(leggere_posizione_record_giocatore(giocatore_di_turno) == (PRIMA_POSIZIONE_PERCORSO-1)){
            partita = lanciare_primi_dadi(partita, indice_giocatore_di_turno);
            stampare_percorso(partita);
            system("pause");
        }else{
        	partita = lanciare_dadi(partita, indice_giocatore_di_turno);
            stampare_percorso(partita);
            system("pause");
        }
        while(trovare_tipo_casella_giocatore(partita, indice_giocatore_di_turno) != CASELLA_NORMALE){
        	partita = gestire_effetti_caselle_speciali(partita, indice_giocatore_di_turno);
        }
        partita = avanzare_turno(partita);
    }else{
        if(scelta == SCELTA_CREARE_NUOVA_PARTITA){
            // CREARE NUOVA PARTITA, metto il flag a true ed esco
            partita = scrivere_nuova_partita_record_partita(partita, true);
        }else{
            if(scelta == SCELTA_SALVARE_PARTITA){
                // salvare partita 
                partita = scrivere_nuova_partita_record_partita(partita, true);
            }else{
				if(scelta == SCELTA_ABBANDONARE_PARTITA){
					// abbandona partita
					// metto il flag di abbandona partita a true ed esco
					partita = scrivere_abbandona_partita_record_partita(partita, true);
				}
            }
        }
    }
    return partita;
}

record_partita gestire_scelta_nuova_partita(int scelta){
    record_partita partita;
    record_dati_nuova_partita dati_nuova_partita;
    
    if(scelta == SCELTA_INIZIARE_NUOVA_PARTITA){
        dati_nuova_partita = chiedere_dati_nuova_partita(PERCORSO_FILE_MENU_SCELTA_DATI_NUOVA_PARTITA);
        partita = creare_nuova_partita(dati_nuova_partita);
        partita = giocare_partita(partita);
    }
    return partita;
}
