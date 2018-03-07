#pragma once

//Returnerer heisretning. Enten opp (1), i ro (0) eller ned (-1). Her KAN DET VÆRE SURR. SKAL ENUM OG 
//VARIABELNAVN PÅ heis byttes??
elev_motor_direction_t getElevatorDirection();

//Returnerer hvilken etasje heisen er i. Returnerer -1 hvis ikke i en etasje. 
//TRENGER LOGIKK I MAIN SOM GJØR AT VI IKKE KJØRER DIVERSE FUNKSJONER HVIS lastfloorSensed()=-1
//Må også ha logikk så vi ikke kjører funksjoner mange ganger MED MINDRE lastFLoorSensed får en NY VERDI!!!
//Dette gjelder spesielt checkstop
int lastFloorSensed();

//Åpner og setter status til aapnet
void openDoor();

//Lukker og setter status til lukket
void closeDoor();
