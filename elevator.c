#include "elevator.h"
#include "elev.h"

elev_motor_direction_t getElevatorDirection() {
	return tag_elev_motor_direction;
}

void openDoor() {
	elev_set_door_open_lamp(1);
}

void closeDoor() {
	elev_set_door_open_lamp(0);
}

int lastFloorSensed(int floor){
	floorSensed = floor;
	if (elev_get_floor_sensor_signal(void) != -1 && elev_get_floor_sensor_signal() != floor){
		floorSensed = elev_get_floor_sensor_signal();
		return floorSensed;
	}
	return floorSensed
}
