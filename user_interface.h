#pragma once

//Sjekker om opp-knappen trykkes. Returnerer etasjenr der oppknapp trykkes. -1 ellers.
//Brukes i andre funksjoner
int checkFloorButtonUp();

//Sjekker om ned-knappen trykkes. Returnerer etasjenr der nedknapp trykkes. -1 ellers.
//Brukes i andre funksjoner
int checkFloorButtonDown();

// Sjekker om etasjeknappene trykkes. Etasjen på etasjeknappen som er trykket. 
int checkButtonCommand();

// Setter stopplys hvis stoppknapp trykkes og setter obstruksjonslys hvis obstruksjon
// Boer ikke dette være 2 funksjoner?? Og husk å kunne slukke dem også.
void obstructionLight();

// Skrur på opp og ned-lys i den etasjen der opp og ned knappene er trykt og i den etasjen vi trykker på inne i heisen
void lightsOn();

//Gitt at vi stopper (i main) slukk de nødvendige lysene.
void lightsOff(int lastFloorSensed, tag_elev_motor_direction motorDirection);