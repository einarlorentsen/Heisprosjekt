#pragma once

//Returnerer heisretning. Enten opp (1), i ro (0) eller ned (-1). Her KAN DET V�RE SURR. SKAL ENUM OG 
//VARIABELNAVN P� heis byttes??
elev_motor_direction_t getElevatorDirection();

//Returnerer hvilken etasje heisen er i. Returnerer -1 hvis ikke i en etasje. 
//TRENGER LOGIKK I MAIN SOM GJ�R AT VI IKKE KJ�RER DIVERSE FUNKSJONER HVIS lastfloorSensed()=-1
//M� ogs� ha logikk s� vi ikke kj�rer funksjoner mange ganger MED MINDRE lastFLoorSensed f�r en NY VERDI!!!
//Dette gjelder spesielt checkstop
int lastFloorSensed();

//�pner og setter status til aapnet
void openDoor();

//Lukker og setter status til lukket
void closeDoor();
