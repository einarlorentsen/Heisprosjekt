#include "queue.h"
#include "elev.h"
#include "user_interface.h"
#include "elevator.h"
#include "elevator_control.h"
#include "fsm.h"

static int elevatorQueue[TYPE_BUTTON][N_FLOORS] = { { 0 } };


void inputElevatorQueue() {
	for (int floor = 0; floor < N_FLOORS ; floor ++){
		for (int button = 0; button < TYPE_BUTTON; button ++){
			if (floor == 0 && button == 1) continue;
			if (floor == 3 && button == 0) continue;
			if (elevatorQueue[button][floor] == 0){
				if (elev_get_button_signal(button,floor) == 1){
					elevatorQueue[button][floor] = 1;
					elev_set_button_lamp(button,floor,1);
				}
			}
		}
	}
}


int checkQueue(){
	for(int i = 0; i < TYPE_BUTTON ; i++){
		for (int k = 0; k < N_FLOORS ; k++){
			if (elevatorQueue[i][k] == 1){
				 if(k == elev_get_floor_sensor_signal()){
					 return 0;
				 }
				 else {
					 return 1;
				 }
			}
		}
	}
	return -1;
}


void updateElevatorQueueAfterStop(int floor) {
	if(floor == -1){
		return;
	}
	elevatorQueue[BUTTON_CALL_DOWN][floor] = 0;
	elevatorQueue[BUTTON_CALL_UP][floor] = 0;
	elevatorQueue[BUTTON_COMMAND][floor] = 0;
}

void emptyElevatorQueue() {
	for (int i = 0; i < TYPE_BUTTON; i++) {
		for (int k = 0; k < N_FLOORS; k++) {
			elevatorQueue[i][k] = 0;
		}
	}
}

int checkStop(elev_motor_direction_t motorDirection, int floor) {
	if (floor == -1){
		return 0;
	}
	int stop = 0;
	switch (motorDirection) {
		case(DIRN_UP):
			if (elevatorQueue[BUTTON_CALL_UP][floor] == 1 || elevatorQueue[BUTTON_COMMAND][floor] == 1) {
				stop = 1;
				return stop;
			}
			else if (elevatorQueue[BUTTON_CALL_DOWN][floor] == 1) {
				for (int i = floor; i < N_FLOORS; i++) {
					if ((i != floor) && ((elevatorQueue[BUTTON_CALL_UP][i] == 1 || (elevatorQueue[BUTTON_CALL_DOWN][i] == 1) || elevatorQueue[BUTTON_COMMAND][i] == 1))) {
					stop = 0;
					return stop;
					}
					if (i == N_FLOORS - 1) {
						stop = 1;
						return stop;
					}
				}
			}

		case(DIRN_DOWN):
			if (elevatorQueue[BUTTON_CALL_DOWN][floor] == 1 || elevatorQueue[BUTTON_COMMAND][floor] == 1) {
				stop = 1;
				return stop;
			}
			else if (elevatorQueue[BUTTON_CALL_UP][floor] == 1) {
				for (int k = floor; k > -1; k--) {
					if (k != floor && (elevatorQueue[BUTTON_CALL_DOWN][k] == 1 || elevatorQueue[BUTTON_CALL_UP][k] == 1 || elevatorQueue[BUTTON_COMMAND][k] == 1)) {
						stop = 0;
						return stop;
					}
					if (k == 0) {
						stop = 1;
						return stop;
					}
				}
			}

		default:
			return stop;
			break;
	}

}


elev_motor_direction_t elevatorDirection(elev_motor_direction_t motorDirection, int floor) {
	if(floor == -1){
		exit(0);
	}
	switch (motorDirection) {
		case(DIRN_UP):
			for (int i = floor; i < N_FLOORS; i++) {
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
			for (int i = floor; i < N_FLOORS; i++) {
				if (i != floor && (elevatorQueue[BUTTON_CALL_UP][i] == 1 || elevatorQueue[BUTTON_CALL_DOWN][i] == 1 || elevatorQueue[BUTTON_COMMAND][i] == 1)) {
					return DIRN_UP;
				}
			}
			break;
		default:{
			return DIRN_STOP;
			break;
		}
	}
}

elev_motor_direction_t elevatorResetAfterEmergency(elev_motor_direction_t motorDirection, int floor){
	printf("motorDirection: %d\n", motorDirection);
	printf("floor: %i\n",floor);
	switch (motorDirection) {
		case(DIRN_UP):
			for(int i = floor; i < N_FLOORS; i++){
				if ((i != floor) && (elevatorQueue[BUTTON_CALL_UP][i] == 1 || elevatorQueue[BUTTON_CALL_DOWN][i] == 1 || elevatorQueue[BUTTON_COMMAND][i] == 1)){
					printf("1 case\n");
					return DIRN_UP;
				}
			}
			for (int j = floor; j > -1; j--){
				if (elevatorQueue[BUTTON_CALL_UP][j] == 1 || elevatorQueue[BUTTON_CALL_DOWN][j] == 1 || elevatorQueue[BUTTON_COMMAND][j] == 1){
					printf("2 case\n");
					return DIRN_DOWN;
				}
			}
		case(DIRN_DOWN):
			for (int k = floor; k > -1; k--) {
				if ((k != floor) && (elevatorQueue[BUTTON_CALL_DOWN][k] == 1 || elevatorQueue[BUTTON_CALL_UP][k] == 1 || elevatorQueue[BUTTON_COMMAND][k] == 1)) {
					printf("3 case\n");
					return DIRN_DOWN;
				}
			}
			for(int l = floor; l < N_FLOORS; l++) {
				if (elevatorQueue[BUTTON_CALL_UP][l] == 1 || elevatorQueue[BUTTON_CALL_DOWN][l] == 1 || elevatorQueue[BUTTON_COMMAND][l] == 1){
					printf("4 case\n");
					return DIRN_UP;
				}
			}
	}
}
