#pragma once

#include "elev.h"

/*Funksjonsinput:
motorDirection = Forrige registrerte DIRN_UP eller DIRN_DOWN.
floor = forrige registrerte etasje */


//Definerer hvor mange typer knapper vi har (COMMAND, BUTTON_UP og BUTTON_DOWN), alts� rader i elevatorQueue.
#define TYPE_BUTTON 3

//Oppdaterer all input fra knapper inn i elevatorQueue og setter nødvendige lys.
void inputElevatorQueue();

//Sletter bestillinger fra etasjen vi har stoppet i fra elevatorQueue
void updateElevatorQueueAfterStop(int floor);

//Setter alle verdier i emptyElevatorQueue til 0. Dette skjer ved EMERGENCY_STOP.
void emptyElevatorQueue();

//Sjekker om vi skal stoppe i en etasje. Returnerer 1 hvis vi skal stoppe. 0 Hvis ikke.
int checkStop(elev_motor_direction_t motorDirection, int floor);

//Returnerer retning på heisen til DIRN_UP eller DIRN_DOWN etter at vi har stoppet og oppdaget en ny bestilling.
elev_motor_direction_t elevatorDirection(elev_motor_direction_t motorDirection, int floor);

/*Sjekker om vi har bestillinger i elevatorQueue. Returner 1 hvis bestilling i etasje vi ikke er i.
0 hvis bestilling i etasje vi er i. Returnerer -1 hvis ingen bestilling i elevatorQueue*/
int checkQueue();

//Spesialfunksjon for å starte heis etter nødstopp når den er mellom etasjer. Returnerer motorRetning DIRN_UP eller DIRN_DOWN
elev_motor_direction_t elevatorResetAfterEmergency(elev_motor_direction_t motorDirection, int floor);
