#include "elevator_control.h"
#include "queue.h"
#include "doors.h"
#include "timer.h"

time_t stopElevator(int lastFloorSensed, int motorDirection) {
	if (checkStop() == 1) {
		elev_set_motor_direction(DIRN_STOP);
		openDoor();
		time_t seconds = setTimer(3);
		updateElevatorQueue(lastFloorSensed, motorDirection);
	}
	else {
		time_t seconds = 0;
	}
	return seconds;
}



int startElevator() {
	int startet = 0;
	if (timerFinished(stopElevator() == 1)) { //Hvis timerFinished(seconds) er 1, med andre ord hvis timer er ferdig!
		startet = 1;
		closeDoor();
		int retningsverdi = elevatorDirection(elevatorDirection, lastFloorSensed); //Husk å få med argumentene på denne!
		if (retningsverdi == 1) {
			elev_set_motor_direction(DIRN_UP);
		}
		else if (retningsverdi == -1) {
			elev_set_motor_direction(DIRN_DOWN);
		}
		else if (retningsverdi == 0) {
			elev_set_motor_direction(DIRN_STOP);
		}
	}
	return startet;
}