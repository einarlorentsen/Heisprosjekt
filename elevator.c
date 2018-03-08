#include "elevator.h"
#include "elev.h"
#include "fsm.h"

void openDoor() {
	elev_set_door_open_lamp(1);
}

void closeDoor() {
	elev_set_door_open_lamp(0);
}
