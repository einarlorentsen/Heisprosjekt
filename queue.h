#pragma once

//Sjekk om vi har lov til � endre p� queue uten � innkludere den i en funksjon!

//Oppdaterer heisk�en. Hvis noen har trykket opp eller ned i en etasje vil etasjeskuffen i k�en i opp-eller
//ned-retning settes til 1. Stopp i den etasjen settes ogs� til 1. Etasjeknapper setter kun stopp til 1 i den etasjen. 
void inputElevatorQueue();

//Denne tar hensyn til alle mulige slettinger i queue N�R VI HAR STOPPET og skal sette verdier til null. 
//Med innvendige heisknapper ogs�. Kj�res kun om vi ER I EN ETASJE.
void updateElevatorQueueAfterStop(int lastFloorSensed);

//Dette er en j�vel av en funksjon, men den styrer ALT av stoppelogikk samtidig som den er modularisert.
//Den tar ogs� hensyn til diverse hendelser som kan pr�ve � "lure" logikken.
int checkStop(elev_motor_direction_t motorDirection, int floor);


//Sm�j�vlig denne ogs�. Bestemmer om heisens retning skal settes til opp, ned eller st� i ro etter at den har stoppet!
elev_motor_direction_t elevatorDirection(tag_elev_motor_direction motorDirection, int floor);

//Returnerer 1 hvis vi kj�rer opp fra en etasje og ikke skal stoppe i samme etasje senere for nedfart. Returnerer 0 hvis 
//vi skal stoppe. Hjelpefunksjon til ligtsOff()
/*
int queueLightsOff(int motorDirection, int lastFloorSensed);

*/