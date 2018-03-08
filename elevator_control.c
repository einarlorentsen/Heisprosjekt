#include "elevator_control.h"
#include "user_interface.h"
#include "elev.h"
#include "queue.h"
#include "timer.h"
#include "queue.h"
#include "elev.h"
#include "fsm.h"
#include "elevator.h"


void initializeElevator(){
	while (elev_get_floor_sensor_signal() == -1){
		elev_set_motor_direction(DIRN_UP);
	}
	elev_set_motor_direction(DIRN_STOP);
	updateState(READY);
}


void stopElevator(int floor, elev_motor_direction_t motorDirection) {
		elev_set_motor_direction(DIRN_STOP);
		openDoor();
		updateElevatorQueueAfterStop(floor);
		lightsOffButtons(floor);
		updateState(DOORS_OPEN);
	}




void moveElevator(elev_motor_direction_t motorDirection, int lastFloorSensed) {
		closeDoor();
		elev_set_motor_direction(elevatorDirection(motorDirection, lastFloorSensed));
	}

void stopButtonElevator() {
	elev_set_stop_lamp(1);
	elev_set_motor_direction(DIRN_STOP);
	emptyElevatorQueue();
	for (int i = 0; i < N_FLOORS; i++) {
		lightsOffButtons(i);
	}
	if (elev_get_floor_sensor_signal() != -1) {
		openDoor();
	}
	while (checkButtonStop()) {

	}


}
