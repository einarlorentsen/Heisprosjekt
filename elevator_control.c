#include "elevator_control.h"
#include "elev.h"
#include "queue.h"
#include "doors.h"
#include "timer.h"
#include "queue.h"
#include "elev.h"

time_t stopElevator(int floor, elev_motor_direction_t motorDirection) {
	if (checkStop(motorDirection,floor)) {
		elev_set_motor_direction(DIRN_STOP);
		openDoor();
		time_t seconds = setTimer(3);
		updateElevatorQueue(floor, motorDirection);
	}
	else {
		time_t seconds = 0;
	}
	return seconds;
}



bool startElevator() {
	if (timerFinished(stopElevator()) { //Hvis timerFinished(seconds) er true, med andre ord hvis timer er ferdig!
		closeDoor();
		elev_set_motor_direction(elevatorDirection(elevatorDirection, lastFloorSensed));
		return true;
	}
	return false;
}