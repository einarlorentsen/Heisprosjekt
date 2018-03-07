#pragma once

#define TYPE_BUTTON 3 //Definerer hvor mange typer knapper vi har (COMMAND, BUTTON_UP og BUTTON_DOWN), altså rader i elevatorQueue.

//Sjekk om vi har lov til å endre på queue uten å innkludere den i en funksjon!

//Oppdaterer heiskøen. Hvis noen har trykket opp eller ned i en etasje vil etasjeskuffen i køen i opp-eller
//ned-retning settes til 1. Stopp i den etasjen settes også til 1. Etasjeknapper setter kun stopp til 1 i den etasjen. 
void inputElevatorQueue();

//Denne tar hensyn til alle mulige slettinger i queue NÅR VI HAR STOPPET og skal sette verdier til null. 
//Med innvendige heisknapper også. Kjøres kun om vi ER I EN ETASJE.
void updateElevatorQueueAfterStop(int lastFloorSensed);

//Setter alle verdier i køen til 0
void emptyElevatorQueue();

//Dette er en jævel av en funksjon, men den styrer ALT av stoppelogikk samtidig som den er modularisert.
//Den tar også hensyn til diverse hendelser som kan prøve å "lure" logikken.
int checkStop(elev_motor_direction_t motorDirection, int floor);


//Småjævlig denne også. Bestemmer om heisens retning skal settes til opp, ned eller stå i ro etter at den har stoppet!
elev_motor_direction_t elevatorDirection(elev_motor_direction_t motorDirection, int floor);