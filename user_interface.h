#pragma once

//Sjekker om opp-knappen trykkes. Returnerer etasjenr der oppknapp trykkes. -1 ellers.
//Brukes i andre funksjoner
int checkFloorButtonUp();

//Sjekker om ned-knappen trykkes. Returnerer etasjenr der nedknapp trykkes. -1 ellers.
//Brukes i andre funksjoner
int checkFloorButtonDown();

// Sjekker om etasjeknappene trykkes. Etasjen på etasjeknappen som er trykket. 
int checkButtonCommand();

//Sjekker om stoppknapp er trykket ned.
bool checkButtonStop();

// Skrur på opp og ned-lys i den etasjen der opp og ned knappene er trykt og i den etasjen vi trykker på inne i heisen
void lightOnButtons();

//Gitt at vi stopper (i main) slukk alle TYPE_BUTTONS lys i hver etasje.
void lightsOffButtons(int floor);