#include "queue.h"
#include "timer.h"
#include "elev.h"

static int elevatorQueue[3][4]={{0}}; //Lager den første heiskøen

int getElevatorQueue(){
	return elevatorQueue;
}

int checkFloorButtonUp() {
	for (int i = 0; i < 3; i++) {
		int success = elev_get_button_signal(BUTTON_CALL_UP, i);
		if (success == 1) {
			return i;
		}
	}
	return -1;
}

int checkFloorButtonDown() {
	//printf("test...\n");
	for (int i = 1; i < 4; i++) {
		int success = elev_get_button_signal(BUTTON_CALL_DOWN, i);
		if (success == 1) {
			return i;
		}
	}
	return -1;
}

void updateElevatorQueue() {
	int floorUp = checkFloorButtonUp();
	int floorDown = checkFloorButtonDown();
	if (floorUp != -1) {
		elevatorQueue[floorUp][BUTTON_CALL_UP] = 1;
	}
	if (floorDown != -1) {
		elevatorQueue[floorDown][BUTTON_CALL_DOWN] = 1;
	}
}

void checkStop(elev_motor_direction_t elevatorDirection, int floor) {
	for (int j = 0; j < 4; j++) {
		if (elevatorDirection == 1 && floor <= j && elevatorQueue[1][j] == 0) { //Hvis retningen er opp, og etasjen vi er i er lavere enn den vi sjekker i tabellen +
			elevatorQueue[0][j] = 1;
		}
	}
	for (int k = 0; k < 4; k++) {
		if (elevatorDirection == -1 && floor >= k && elevatorQueue[1][k] == 1) {
			elevatorQueue[0][k] = 1;
		}
	}
}

int elevatorStop(elev_motor_direction_t elevatorDirection, int floor){
	if (elevatorDirection == 1){
		for(int i = floor; i < 4; i++){
			if (elevatorQueue[0][i] == 0){
				continue;
			}
			return i;
		}
	}
	if (elevatorDirection == -1){
		for(int k = floor; k > 0; k--){
			if (elevatorQueue[0][k] == 0){
				continue;
			}
			return k;
		}
	}
}

time_t stopTheElevator(elev_motor_direction_t elevatorDirection, int floor){
	timer_t setupTime;
	if (elev_get_floor_sensor_signal() == floor){
		elev_set_motor_direction(DIRN_STOP);
		openDoor();
		if(elev_get_floor_sensor_signal() == floor){
			timer_t setupTime = setTimer(3);
		}
		elevatorQueue[0][floor] = 0;
		if (elevatorDirection == 1){ //Sletter stoppsignalet fra den etasjen signalet kom fra slik at if setningen ovenfor ikke gås inn i flere ganger
			elevatorQueue[1][floor] = 0; //Vil dermed ha en eksklusiv if-lykke sånn at heisen kan BARE stoppe i 3 sek.
		}
		if (elevatorDirection == -1){ //Samme som ovenfor bare for "vil ned" signalet
			elevatorQueue[2][floor] = 0;
		}
	}
	return setupTime;
}

int lastFloorSensed() {
	int sensedFloor;
	if (elev_get_floor_sensor_signal() != -1){
		sensedFloor = elev_get_floor_sensor_signal();
	}
	return sensedFloor;
}
