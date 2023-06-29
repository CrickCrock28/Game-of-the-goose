#ifndef RECORD_GIOCATORE_H_
#define RECORD_GIOCATORE_H_

typedef struct {
    int posizione;
    int numero_turni_bloccato;
    int bloccato;
    int numero_dadi_lanciati;
} record_giocatore;

record_giocatore scrivere_posizione_record_giocatore(record_giocatore giocatore, int nuova_posizione);
record_giocatore scrivere_numero_turni_bloccato_record_giocatore(record_giocatore giocatore, int nuovo_numero_turni_bloccato);
record_giocatore scrivere_bloccato_record_giocatore(record_giocatore giocatore, int nuovo_bloccato) ;
record_giocatore scrivere_numero_dadi_lanciati_record_giocatore(record_giocatore giocatore, int nuovo_numero_dadi_lanciati) ;
int leggere_posizione_record_giocatore(record_giocatore giocatore) ;
int leggere_numero_turni_bloccato_record_giocatore(record_giocatore giocatore); 
int leggere_bloccato_record_giocatore(record_giocatore giocatore) ;
int leggere_numero_dadi_lanciati_record_giocatore(record_giocatore giocatore);

#endif /* RECORD_GIOCATORE */