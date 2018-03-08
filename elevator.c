#include "elevator.h"
#include "elev.h"

void openDoor() {
	elev_set_door_open_lamp(1);
}

void closeDoor() {
	elev_set_door_open_lamp(0);
}

int lastFloorSensed(int floor){
	int floorSensed = floor;
	int sensorSignal = elev_get_floor_sensor_signal();
	if (sensorSignal != -1 && sensorSignal != floor){
		floorSensed = sensorSignal;
		return floorSensed;
	}
	return floorSensed;
}
