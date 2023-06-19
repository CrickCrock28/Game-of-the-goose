#include "giocare_partita.h"

char tipo_casella(record_partita partita, int indice_giocatore){
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

        if(trovare_tipo_casella_giocatore(giocatore) == CASELLA_PRIGIONE && leggere_bloccato_record_giocatore(giocatore)){
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

    int indice_giocatore_di_turno;
    int scelta;

    if(!verificare_partita_iniziata(partita)){
        partita = stabilire_primo_giocatore(partita);
    }

    while(!leggere_terminata_record_partita(partita) &&
           !leggere_nuova_partita_record_partita(partita) &&
           !leggere_abbandona_partita_record_partita(partita) &&
           !leggere_salvare_partita_record_partita(partita)){
        indice_giocatore_di_turno = leggere_indice_giocatore_di_turno_record_partita(partita);
        stampare_file_di_testo(PERCORSO_FILE_MENU_PARTITA);
        scelta = chiedere_intero("Inserisci la scelta: ", 0, 3);    //DA RIVEDERE
        partita = gestire_scelta_partita(partita, scelta);          //DA RIVEDERE
    }

    return partita;
}


record_partita lanciare_primi_dadi(record_partita partita, int indice_giocatore){
    
    int dado_1;
    int dado_2;
    record_vet_giocatori vet_giocatori;
    record_giocatore giocatore;
    int dimensione_percorso;

    dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);      //DA RIVEDERE
    dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);      //DA RIVEDERE
    
    partita = scrivere_ultimo_lancio_dado_1_record_partita(partita, dado_1);
    partita = scrivere_ultimo_lancio_dado_2_record_partita(partita, dado_2);

    vet_giocatori = leggere_vet_giocatori_record_partita(partita);
    giocatore = leggere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore);
    dimensione_percorso = leggere_dimensione_record_percorso(leggere_percorso_record_partita(partita));

    if(dado_1 == 5 && dado_2 == 4){
        giocatore = scrivere_posizione_record_giocatore(giocatore, calcolare_proporzione(ARRIVO_PRIMO_LANCIO_4_5, NUMERO_MASSIMO_CASELLE, dimensione_percorso));
    }
    else if(dado_1 == 6 && dado_2 == 3){
        giocatore = scrivere_posizione_record_giocatore(giocatore, calcolare_proporzione(ARRIVO_PRIMO_LANCIO_3_6, NUMERO_MASSIMO_CASELLE, dimensione_percorso));
    }
    else {
        giocatore = scrivere_posizione_record_giocatore(giocatore, dado_1 + dado_2);
    }
    
    vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore, giocatore);
    partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);

    return partita;
}


void stampare_percorso(char* caselle, int dimensione, int posizione_giocatore_1, int posizione_giocatore_2, int posizione_giocatore_3, int posizione_giocatore_4){
	int x = 0;
	int y = 0;
	int i = 0;
	while(i<=dimensione){
		GoToXY(x,y);
		printf("-----");
		
		GoToXY(x, y+1);
		if(posizione_giocatore_1 == i)
			printf("|& ");
		else
			printf("|  ");
		
		if(posizione_giocatore_2 == i)
			printf("*|");
		else
			printf(" |");
		
		GoToXY(x, y+2);
		if(posizione_giocatore_3 == i)
			printf("|# ");
		else
			printf("|  ");
		
		if(posizione_giocatore_4 == i)
			printf("$|");
		else
			printf(" |");
		
		GoToXY(x, y+3);
		if(i==0)
			printf("| %2d|", i);
		else
			printf("|%c%2d|", caselle[i-1], i);
		
		GoToXY(x, y+4);
		printf("-----");
		x = x + 4;
		
		i++;
		
		if(i%19 == 0){
			y = y + 4;
			x = 0;
		}		
	}
}


record_partita avanzare_turno(record_partita partita){
    int indice_successivo;
    
    indice_successivo = leggere_indice_giocatore_di_turno(partita) + 1;

    if(indice_successivo > leggere_dimensione_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita))){
        indice_successivo = PRIMO_INDICE_ARRAY;
    }

    partita = scrivere_indice_giocatore_di_turno_record_partita(partita, indice_successivo);

    return partita;
}


record_partita stabilire_primo_giocatore(record_partita partita){
    int dado_1;
    int dado_2;
    int massimo_lancio_dadi;
    int indice_inizio;
    int i;
    
    indice_inizio = PRIMO_INDICE_ARRAY;
    dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
    dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
    massimo_lancio_dadi = dado_1 + dado_2;

    i = PRIMO_INDICE_ARRAY + 1;
    while(i <= leggere_dimensione_record_vet_giocatori(leggere_vet_giocatori_record_partita(partita))){
        dado_1 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);
        dado_2 = generare_numero_casuale(NUMERO_MINIMO_DADO, NUMERO_MASSIMO_DADO);

        if(massimo_lancio_dadi > dado_1 + dado_2){
            massimo_lancio_dadi = dado_1 + dado_2;
            indice_inizio = i;
        }

        i++;
    }

    partita = scrivere_indice_giocatore_di_turno_record_partita(partita, indice_inizio);

    return partita;
}


record_partita gestire_menu_nuova_partita(const char* menu_nuova_partita, const char* menu_partita_in_corso, int riprendere_partita){
    int nuova_partita;
    int scelta;
    record_partita partita;
    
    nuova_partita = false;
    do {
        if(nuova_partita){
            partita = gestire_scelta_nuova_partita(scelta); //DA RIVEDERE
        } else {
            if(riprendere_partita == 0){
                stampare_file_di_testo(PERCORSO_FILE_MENU_PARTITA);
                scelta = chiedere_intero("Inserisci la scelta: ", 0, 1); //DA RIVEDERE
                partita = gestire_scelta_nuova_partita(scelta); //DA RIVEDERE
            } else {
                partita = giocare_partita(partita); //DA RIVEDERE
            }
        }

        if(leggere_nuova_partita_record_partita(partita)){
            nuova_partita = true;
        } else {
            if(leggere_abbandona_partita_record_partita(partita) == false){
                scelta = 0;
            }
        }
    } while(scelta != 0);

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
        if(trovare_tipo_casella_giocatore(giocatore) == CASELLA_POZZO && leggere_bloccato_record_giocatore(giocatore) = true){
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
    
    if((leggere_bloccato_record_giocatore(giocatore) == false) || (leggere_bloccato_record_giocatore(giocatore) == true && ( somma_dadi== 5 || somma_dadi= = 7))){
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
                                partita = applicare_effetto_casella_prigione(partita, indice_giocatore);
                                }else{  
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
    record_giocatore giocatore_di_turno;
    int indice_giocatore_di_turno;

    if(scelta == 1){
        // tira i dadi, potrebbe terminare la partita
        vet_giocatori = leggere_vet_giocatori_record_partita(partita);
        giocatore_di_turno = leggere_record_giocatore_vet_giocatori(vet_giocatori, indice_giocatore_di_turno);
        giocatore_di_turno = scrivere_numero_dadi_lanciati_record_giocatore(leggere_numero_dadi_lanciati_record_giocatore(giocatore_di_turno) + 1);
        vet_giocatori = scrivere_giocatore_record_vet_giocatori(vet_giocatori, indice_giocatore_di_turno, giocatore_di_turno);
        partita = scrivere_vet_giocatori_record_partita(partita, vet_giocatori);
        if(leggere_posizione_record_giocatore(giocatore_da_incrementare) == (PRIMA_POSIZIONE_PERCORSO - 1)){
            partita = lanciare_primi_dadi(partita, indice_giocatore_di_turno);
            }else{
                partita = lanciare_dadi(partita, indice_giocatore_di_turno);
                }
                while(trovare_tipo_casella_giocatore(partita, indice_giocatore_di_turno) != CASELLA_NORMALE)){
                partita = gestire_effetti_caselle_speciali(partita, indice_giocatore_di_turno);
                }
                partita = avanzare_turno(partita);
    }else{
        if(scelta == 2){
            // CREARE NUOVA PARTITA, metto il flag a true ed esco
            partita = scrivere_nuova_partita_record_partita(partita, true);
        }else{
            if(scelta = 3){
                // salvare partita 
                partita = scrivere_salvare_partita_record_partita(partita, true);
            }else{
                // abbandona partita
                // metto il flag di abbandona partita a true ed esco
                partita = scrivere_abbandona_partita_record_partita(partita, true);
            }
        }
    }
    return partita;
}


record_partita gestire_scelta_partita(int scelta){
    if(scelta==1){
        record_partita partita;
        record_dati_nuova_partita dati_nuova_partita;

        dati_nuova_partita = chiedere_dati_nuova_partita();
        partita = creare_partita(dati_nuova_partita);
        partita = giocare_partita(partita);
    }
    return partita;
}