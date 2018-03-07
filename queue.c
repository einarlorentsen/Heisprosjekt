#include "queue.h"
#include "elev.h"
#include "user_interface.h"
#include "elevator.h"

static int elevatorQueue[3][4] = { { 0 } };

void inputElevatorQueue() {
	int floorUp = checkFloorButtonUp();
	int floorDown = checkFloorButtonDown();
	int buttonCommand = checkButtonCommand();
	if (floorUp != -1) {
		elevatorQueue[BUTTON_CALL_UP][floorUp] = 1;
	}
	if (floorDown != -1) {
		elevatorQueue[BUTTON_CALL_DOWN][floorDown] = 1;
	}
	if (buttonCommand != -1) {
		elevatorQueue[BUTTON_COMMAND][buttonCommand] = 1;
	}
}

void updateElevatorQueueAfterStop(int floor) {
	elevatorQueue[BUTTON_CALL_DOWN][floor] = 0;
	elevatorQueue[BUTTON_CALL_UP][floor] = 0;
	elevatorQueue[BUTTON_COMMAND][floor] = 0;
}


bool checkStop(elev_motor_direction_t motorDirection, int floor) {
	switch (motorDirection) {
		case(DIRN_UP) {
			if (elevatorQueue[BUTTON_CALL_UP][floor] == 1 || elevatorQueue[BUTTON_COMMAND][floor] == 1 || floor == 3) {
				return true;
			}
			else if (elevatorQueue[BUTTON_CALL_DOWN][floor] == 1){
				for (int i = floor; i < 4; i++) {                          // og du vil ned, selv om heisretning er opp
					if (i != floor && (elevatorQueue[BUTTON_CALL_UP][i] == 1 || elevatorQueue[BUTTON_CALL_DOWN][i] == 1 || elevatorQueue[BUTTON_COMMAND][i] == 1)) {
						return false;
					}
					if (i == 3) {
						return true;
					}
			break;
		}
		case(DIRN_DOWN) {
			if (elevatorQueue[BUTTON_CALL_DOWN][floor] == 1 || elevatorQueue[BUTTON_COMMAND][floor] == 1 || floor == 0) {
				return true;
			}
			else if (elevatorQueue[BUTTON_CALL_UP][floor] == 1) { //Sjekker om ingen under deg har trykket stopp
				for (int k = floor; k > -1; k--) {                           //og du vil opp, selv om heisretning er ned.
					if (k != floor && (elevatorQueue[BUTTON_CALL_DOWN][k] == 1 || elevatorQueue[BUTTON_CALL_UP][k] == 1 || elevatorQueue[BUTTON_COMMAND][k] == 1)) {
						return false;
					}
					if (k == 0) {
						return true;
					}
				}
			}
			break;
		}
		default:
			return false;
			break;
	


// Vi må GET elevatorDirection FØR vi stopper og så lagre denne og jobbe med denne her.
elev_motor_direction_t elevatorDirection(elev_motor_direction_t motorDirection, int floor) {
	switch (motorDirection) {
	case(DIRN_UP):
		for (int i = floor; i < 4; i++) {
			if (i != floor && (elevatorQueue[BUTTON_CALL_UP][i] == 1 || elevatorQueue[BUTTON_CALL_DOWN][i] == 1 || elevatorQueue[BUTTON_COMMAND][i] == 1)) {
				return DIRN_UP;
			}
		}
		for (int k = floor; k > -1; k--) {
			if (k != floor && (elevatorQueue[BUTTON_CALL_DOWN][k] == 1 || elevatorQueue[BUTTON_CALL_UP][k] == 1 || elevatorQueue[BUTTON_COMMAND][k] == 1)) {
				return DIRN_DOWN;
			}
		}
		break;
	case(DIRN_DOWN):
		for (int k = floor; k > -1; k--) {
			if (k != floor && (elevatorQueue[BUTTON_CALL_DOWN][k] == 1 || elevatorQueue[BUTTON_CALL_UP][k] == 1 || elevatorQueue[BUTTON_COMMAND][k] == 1)) {
				return DIRN_DOWN;
			}
		}
		for (int i = floor; i < 4; i++) {
			if (i != floor && (elevatorQueue[BUTTON_CALL_UP][i] == 1 || elevatorQueue[BUTTON_CALL_DOWN][i] == 1 || elevatorQueue[BUTTON_COMMAND][i] == 1)) {
				return DIRN_UP;
			}
		}

	default: return DIRN_STOP;
		break;
	}
}
	
