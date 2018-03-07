#pragma once

//Sjekker om opp-knappen trykkes. Returnerer etasjenr der oppknapp trykkes. -1 ellers.
//Brukes i andre funksjoner
int checkFloorButtonUp();

//Sjekker om ned-knappen trykkes. Returnerer etasjenr der nedknapp trykkes. -1 ellers.
//Brukes i andre funksjoner
int checkFloorButtonDown();

// Sjekker om etasjeknappene trykkes. Etasjen p� etasjeknappen som er trykket. 
int checkButtonCommand();

// Setter stopplys hvis stoppknapp trykkes og setter obstruksjonslys hvis obstruksjon
// Boer ikke dette v�re 2 funksjoner?? Og husk � kunne slukke dem ogs�.
void obstructionLight();

// Skrur p� opp og ned-lys i den etasjen der opp og ned knappene er trykt og i den etasjen vi trykker p� inne i heisen
void lightsOn();

//Gitt at vi stopper (i main) slukk de n�dvendige lysene.
void lightsOff(int lastFloorSensed, tag_elev_motor_direction motorDirection);