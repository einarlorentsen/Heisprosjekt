#pragma once

//Funksjonsinput: floor = forrige registrerte etasje

// Hvis vi holder inn en knapp i samme etasje som vi står i returnerer vi 0. Hvis ikke 1.
int checkButtonHoldInFloor(int floor);

//Slukker lys i etasje vi stopper
void lightsOffButtons(int floor);

/*Stoppknapp-funksjonalitet. Setter stopplys, motorretning = DIRN_STOP, skrur av lys,
tømmer kø og åpner dør hvis vi står i etasje. Blokkerer for input fra bruker så lenge
stoppknappen holdes inne.*/
void stopButtonElevator();

//Setter etasjeindikator-lysene
void floorLight(int floor);
