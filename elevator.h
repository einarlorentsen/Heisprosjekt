#pragma once

//Returnerer heisretning. Enten opp (1), i ro (0) eller ned (-1). Her KAN DET V�RE SURR. SKAL ENUM OG
//VARIABELNAVN P� heis byttes??
elev_motor_direction_t getElevatorDirection();

//�pner og setter status til aapnet
void openDoor();

//Lukker og setter status til lukket
void closeDoor();

int lastFloorSensed(int floor);
