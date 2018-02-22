#include "queue.h"
#include "elev.h"


int checkButtonUp() {
	int success = 0;
	for (int i = 0; i < 3; i++) {
		success = elev_get_button_signal(BUTTON_CALL_UP, i);
		if (success == 1) {
			return i;
		}
	}
	return 0;
}

int checkButtonDown() {
	for (int i = 1; i < 4; i++) {
		success = elev_get_button_signal(BUTTON_CALL_DOWN, i);
		if (success == 1) {
			return i;
		}
	}
	return 0;
}

void makeElevatorQueue(int elevatorQueue) {
	int floorUp = checkButtonUp();
	int floorDown = checkButtonDown();
	if (floorUp != 0) {
		elevatorQueue[floorUp][BUTTON_CALL_UP] = 1;
	}
	if (floorDown != 0) {
		elevatorQueue[floorDown][BUTTON_CALL_DOWN] = 1;
	}
}

void checkStop(int elevatorQueue, elev_motor_direction_t elevatorDirection, int floor) {
	for (int j = 0; j < 4; j++) {
		if (elevatorDirection == 1 && floor =< i && elevatorQueue[1][j] == 0) {
			elevatorQueue[0][j] = 1;
		}
	}
	for (int k = 0; k < 4; k++) {
		if (elevatorDirection == -1 && floor => i && elevatorQueue[1][k] == 1) {
			elevatorQueue[0][k] = 1;
		}
	}
}
