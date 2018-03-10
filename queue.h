#pragma once

#include "elev.h"

#define TYPE_BUTTON 3 //Definerer hvor mange typer knapper vi har (COMMAND, BUTTON_UP og BUTTON_DOWN), alts� rader i elevatorQueue.

//Oppdaterer all input fra knapper inn i heiskøen
void inputElevatorQueue();

//Sletter bestillinger fra etasjen vi har stoppet i fra elevatorQueue
void updateElevatorQueueAfterStop(int lastFloorSensed);

//Setter alle verdier i emptyElevatorQueue til 0
void emptyElevatorQueue();

//Sjekker om vi skal stoppe i en etasje. Returnerer 1 hvis vi skal stoppe. 0 Hvis ikke.
int checkStop(elev_motor_direction_t dir, int floor);


//Setter retning på heisen til DIRN_UP eller DIRN_DOWN etter at vi har stoppet og oppdaget en ny bestilling.
elev_motor_direction_t elevatorDirection(elev_motor_direction_t motorDirection, int floor);

//Sjekker om vi har bestillinger i elevatorQueue. 0 hvis ikke stopp, 1 hvis stopp.
int checkQueue();

//Spesialfunksjon for å starte heis etter nødstopp når den er mellom etasjer.
elev_motor_direction_t elevatorResetAfterEmergency(elev_motor_direction_t motorDirection, int lastFloorSensed);
