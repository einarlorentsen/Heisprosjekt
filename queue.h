#include "elev.h"

int checkFloorButtonUp(); //Sjekker om en av nedknappene er trykket
int checkFloorButtonDown(); //Sjekker om en av oppknappene er trykket
void updateElevatorQueue(int elevatorQueue[3][4]); //Lager heiskøen
void checkStop(int elevatorQueue[3][4], elev_motor_direction_t elevatorDirection, int floor); //Sjekker om vi skal stoppe på en gitt etasje
