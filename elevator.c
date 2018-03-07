#include "elevator.h"
#include "elev.h"

elev_motor_direction_t getElevatorDirection() {
	return tag_elev_motor_direction;
}

int lastFloorSensed() {
	int sensedFloor = -1;
	if (elev_get_floor_sensor_signal() != -1) {
		sensedFloor = elev_get_floor_sensor_signal();
	}
	return sensedFloor;
}

