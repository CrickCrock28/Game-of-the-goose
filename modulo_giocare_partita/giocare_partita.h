// PERFETTO
#ifndef GIOCARE_PARTITA_H_
#define GIOCARE_PARTITA_H_

#include "..\\moduli_record\\modulo_record_partita\\record_partita.h"

#define TIPO_CASELLA_NORMALE 'N'
#define TIPO_CASELLA_OCA 'O'
#define TIPO_CASELLA_PONTE 'T'
#define TIPO_CASELLA_LOCANDA 'D'
#define TIPO_CASELLA_POZZO 'Z'
#define TIPO_CASELLA_LABIRINTO 'L'
#define TIPO_CASELLA_SCHELETRO 'S'
#define TIPO_CASELLA_PRIGIONE 'P'
#define TIPO_CASELLA_FINE 'F'
#define TIPO_CASELLA_VUOTA 'V'

#define GIOCATORE_DI_TURNO_NON_STABILITO -1

#define POSIZIONE_GIOCATORE_NON_PARTECIPANTE -2
#define POSIZIONE_INIZIO_PARTITA 0

record_partita giocare_partita(record_partita partita);

#endif
