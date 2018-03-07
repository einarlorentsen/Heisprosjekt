#pragma once

//Returnerer heisretning. Enten opp (1), i ro (0) eller ned (-1). Her KAN DET VÆRE SURR. SKAL ENUM OG 
//VARIABELNAVN PÅ heis byttes??
elev_motor_direction_t getElevatorDirection();

//Åpner og setter status til aapnet
void openDoor();

//Lukker og setter status til lukket
void closeDoor();
