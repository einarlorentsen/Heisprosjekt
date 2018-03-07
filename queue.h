#pragma once

//Sjekk om vi har lov til å endre på queue uten å innkludere den i en funksjon!

//Oppdaterer heiskøen. Hvis noen har trykket opp eller ned i en etasje vil etasjeskuffen i køen i opp-eller
//ned-retning settes til 1. Stopp i den etasjen settes også til 1. Etasjeknapper setter kun stopp til 1 i den etasjen. 
void inputElevatorQueue();

//Denne tar hensyn til alle mulige slettinger i queue når vi har stoppet og skal sette verdier til null. 
//Med innvendige heisknapper også.
void updateElevatorQueue(int lastFloorSensed, elev_motor_direction_t motorDirection);

//Dette er en jævel av en funksjon, men den styrer ALT av stoppelogikk samtidig som den er modularisert.
//Den tar også hensyn til diverse hendelser som kan prøve å "lure" logikken.
int checkStop(elev_motor_direction_t motorDirection, int lastFloorSensed);


//Småjævlig denne også. Bestemmer om heisens retning skal settes til opp, ned eller stå i ro etter at den har stoppet!
int elevatorDirection(tag_elev_motor_direction motorDirection, int lastFloorSensed);

//Returnerer 1 hvis vi kjører opp fra en etasje og ikke skal stoppe i samme etasje senere for nedfart. Returnerer 0 hvis 
//vi skal stoppe. Hjelpefunksjon til ligtsOff()
/*
int queueLightsOff(int motorDirection, int lastFloorSensed);

*/