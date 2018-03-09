#include "elevator_control.h"
#include "user_interface.h"
#include "elev.h"
#include "queue.h"
#include "timer.h"
#include "queue.h"
#include "elev.h"
#include "fsm.h"
#include "elevator.h"


void stopElevator(int floor, elev_motor_direction_t motorDirection) {
		elev_set_motor_direction(DIRN_STOP);
		openDoor();
		updateElevatorQueueAfterStop(floor);
		lightsOffButtons(floor);
	}




void moveElevator(elev_motor_direction_t motorDirection, int lastFloorSensed) {
		closeDoor();
		elev_set_motor_direction(elevatorDirection(motorDirection, lastFloorSensed));
	}
