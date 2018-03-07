#include "elevator_control.h"
#include "user_interface.h"
#include "elev.h"
#include "queue.h"
#include "doors.h"
#include "timer.h"
#include "queue.h"
#include "elev.h"

state_t state;

void updateState(state_t newState){
	state = newState;
}

void initializeElevator(){
	while (elev_get_floor_sensor_signal() == -1){
		elev_set_motor_direction(DIRN_UP);
	}
	elev_set_motor_direction(DIRN_STOP))
	updateState(READY);
}

void elevatorReady(){
	if(inputElevatorQueue()){
		if(checkStop(motorDirection, elev_get_floor_sensor_signal)){
			updateState(STOP);
		}
		else {
			updateState(MOVE);
		}
	}
}

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



bool startElevator(elev_motor_direction_t motorDirection, int lastFloorSensed) {
	if (timerFinished(stopElevator()) { //Hvis timerFinished(seconds) er true, med andre ord hvis timer er ferdig!
		closeDoor();
		elev_set_motor_direction(elevatorDirection(motorDirection, lastFloorSensed));
		return true;
	}
	return false;
}

time_t stopButtonElevator() {
	time_t seconds = 0;
	elev_set_stop_lamp(1);
	elev_set_motor_direction(DIRN_STOP);
	emptyElevatorQueue();
	for (int i = 0; i < N_FLOORS; i++) {
		lightsOffButtons(i)
	}
	if (elev_get_floor_sensor_signal() != -1) {
		openDoor();
	}
	while (checkButtonStop()) {

	}

	if (elev_get_floor_sensor_signal() != -1) {
		timer_t seconds = setTimer(3);
	}
	return seconds;
}
