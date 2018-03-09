#include "queue.h"
#include "elev.h"
#include "user_interface.h"
#include "elevator.h"
#include "elevator_control.h"
#include "fsm.h"

static int elevatorQueue[TYPE_BUTTON][N_FLOORS] = { { 0 } };

void printQueue(){
	for (int i = 0; i < TYPE_BUTTON; i++) {
		for (int k = 0; k < N_FLOORS; k++) {
			printf("%d", elevatorQueue[i][k]);
		}
		printf("\n");
	}
}

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
	printf("Går inn i checkStop\n");
	switch (motorDirection) {
		case(DIRN_UP):
			/*printf("Retningen er opp, og vi går inn i switchen\n");
			printf("elevatorQueue[BUTTON_CALL_UP][floor] = %i\n", elevatorQueue[BUTTON_CALL_UP][floor]);
			printf("elevatorQueue[BUTTON_COMMAND][floor] = %i\n", elevatorQueue[BUTTON_COMMAND][floor]);
			printf("floor = %i\n", floor);
			if (elevatorQueue[BUTTON_CALL_UP][floor] == 1 || elevatorQueue[BUTTON_COMMAND][floor] == 1 || floor == 3) {
				printf("På vei opp. Noen skal opp, command eller øverste\n");
				return 1;
			}
			else if (elevatorQueue[BUTTON_CALL_DOWN][floor] == 1) {
				for (int i = floor; i < N_FLOORS; i++) {                          // og du vil ned, selv om heisretning er opp
					if (i != floor && (elevatorQueue[BUTTON_CALL_UP][i] == 1 || elevatorQueue[BUTTON_CALL_DOWN][i] == 1 || elevatorQueue[BUTTON_COMMAND][i] == 1)) {
						return 0;
					}
					if (i == N_FLOORS - 1) { //Retning opp, men vil ned. Hvis ingen bestilling over oss - stopp.
						printf("På vei opp. Bestilling under oss\n");
						return 1;
					}
				}
			}
			*/
			break;
		/*case(DIRN_DOWN):
			printf("retningen er ned og vi går inn i switchen\n");
			if (elevatorQueue[BUTTON_CALL_DOWN][floor] == 1 || elevatorQueue[BUTTON_COMMAND][floor] == 1 || floor == 0) {
				printf("På vei ned. Noen skal ned, command eller nederste\n");
				return 1;
			}
			else if (elevatorQueue[BUTTON_CALL_UP][floor] == 1) { //Sjekker om ingen under deg har trykket stopp
				for (int k = floor; k > -1; k--) {                           //og du vil opp, selv om heisretning er ned.
					if (k != floor && (elevatorQueue[BUTTON_CALL_DOWN][k] == 1 || elevatorQueue[BUTTON_CALL_UP][k] == 1 || elevatorQueue[BUTTON_COMMAND][k] == 1)) {
						return 0;
					}
					if (k == 0) {
						printf("På vei ned.  Bestilling over oss\n");
						return 1;
					}
				}
			}
			break;
			*/
		default:
			printf("Vi er i default i switch\n");
			return 0;
			break;
	}

}



// Hjelpefunksjon, sier hvilken retning vi skal i etter vi har stoppet
elev_motor_direction_t elevatorDirection(elev_motor_direction_t motorDirection, int floor) {
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
