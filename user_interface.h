#pragma once

//Sjekker om opp-knappen trykkes. Returnerer etasjenr der oppknapp trykkes. -1 ellers.
//Brukes i andre funksjoner
int checkFloorButtonUp();

//Sjekker om ned-knappen trykkes. Returnerer etasjenr der nedknapp trykkes. -1 ellers.
//Brukes i andre funksjoner
int checkFloorButtonDown();

// Sjekker om etasjeknappene trykkes. Etasjen p� etasjeknappen som er trykket.
int checkButtonCommand();

// Skrur p� opp og ned-lys i den etasjen der opp og ned knappene er trykt og i den etasjen vi trykker p� inne i heisen
void lightOnButtons();

// Hvis vi holder inn en knapp i samme etasje returnerer vi 0. Hvis ikke 1.
void noButtonSignalInFloor(int floor);

//Gitt at vi stopper (i main) slukk alle TYPE_BUTTONS lys i hver etasje.
void lightsOffButtons(int floor);

//Stoppknapp-funksjonalitet
void stopButtonElevator();

//Setter etasjeindikator-lysene
void floorLight(int lastFloorSensed);
