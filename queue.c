#include "queue.h"
#include "elev.h"
#include "user_interface.h"
#include "elevator.h"

static int elevatorQueue[3][4] = { { 0 } };

void inputElevatorQueue() {
	int floorUp = checkFloorButtonUp(); //HUSK Å LEGGE TIL ETASJEKNAPPER-input!
	int floorDown = checkFloorButtonDown();
	int buttonCommand = checkButtonCommand();
	if (floorUp != -1) {
		elevatorQueue[1][floorUp] = 1; //Hva med tallverdi istedet for call_up? Funker dette. Vil vi ha bare
		elevatorQueue[0][floorUp] = 1;              //tall eller bare kodeord??
	}
	if (floorDown != -1) {
		elevatorQueue[2][floorDown] = 1;
		elevatorQueue[0][floorDown] = 1;
	}
	if (buttonCommand != -1) {
		elevatorQueue[0][buttonCommand] = 1;
	}
}

void updateElevatorQueue(int lastFloorSensed, elev_motor_direction_t motorDirection) {
	if (motorDirection == 1 && elevatorQueue[1][lastFloorSensed] == 1 && elevatorQueue[2][lastFloorSensed] == 0) {
		elevatorQueue[0][lastFloorSensed] = 0;
		elevatorQueue[1][lastFloorSensed] = 0; //Hvis på vei opp og bare opp knapp. F.eks nederst.
	}

	else if (motorDirection == 1 && elevatorQueue[1][lastFloorSensed] == 1 && elevatorQueue[2][lastFloorSensed] == 1) {
		elevatorQueue[1][lastFloorSensed] = 0; //Hvis på vei opp, men både opp og ned knapp
	}

	else if (motorDirection == 1 && elevatorQueue[1][lastFloorSensed] == 1 && elevatorQueue[2][lastFloorSensed] == 1) {
		elevatorQueue[0][lastFloorSensed] = 0; //Hvis er på vei opp, men nå skal vi ned. F.eks øverst.
		elevatorQueue[2][lastFloorSensed] = 0;
	}

	else if (motorDirection == 1 && elevatorQueue[0][lastFloorSensed] == 1) {
		elevatorQueue[0][lastFloorSensed] = 0; //Hvis KUN lys på stopp og ikke opp eller ned. AKA Noen har trykket etasjeknapp
	}

	if (motorDirection == -1 && elevatorQueue[2][lastFloorSensed] == 1 && elevatorQueue[2][lastFloorSensed] == 0) {
		elevatorQueue[0][lastFloorSensed] = 0; //Hvis på vei ned og bare ned knapp
		elevatorQueue[2][lastFloorSensed] = 0;
	}
	else if (motorDirection == -1 && elevatorQueue[2][lastFloorSensed] == 1 && elevatorQueue[2][lastFloorSensed] == 1) {
		elevatorQueue[2][lastFloorSensed] = 0; //Hvis på vei ned, men både opp og ned knapp
	}
	else if (motorDirection == -1 && elevatorQueue[1][lastFloorSensed] == 1) {
		elevatorQueue[0][lastFloorSensed] = 0;
		elevatorQueue[1][0] = 0;
	}

	else if (motorDirection == -1 && elevatorQueue[0][lastFloorSensed] == 1) {
		elevatorQueue[0][lastFloorSensed] = 0;
	}
}

int checkStop(elev_motor_direction_t motorDirection, int lastFloorSensed) {
	if (lastFloorSensed == 0 || lastFloorSensed == 3) { //Antar stopp hvis oeverst eller nederst fordi vi ikke skal opp
		return 1;                                       //dit hvis ingen skal stoppe der
	}
	if (motorDirection == 1 && elevatorQueue[1][lastFloorSensed] == 1) { // Sjekker basic stopp for oppoverretning.
		return 1;
	}
	else if (motorDirection == 1 && elevatorQueue[0][lastFloorSensed] == 1) { // Sjekker om ingen over deg har trykket stopp
		for (int i = lastFloorSensed; i < 4; i++) {                          // og du vil ned, selv om heisretning er opp
			if (i != lastFloorSensed && elevatorQueue[0][i] == 1) {
				break;
			}
			if (i == 3) {
				return 1;
			}
		}

	}
	if (motorDirection == -1 && elevatorQueue[2][lastFloorSensed] == 1) { //Sjekker basic stopp for nedoverretning
		return 1;
	}
	else if (motorDirection == -1 && elevatorQueue[0][lastFloorSensed] == 1) { //Sjekker om ingen under deg har trykket stopp
		for (int k = lastFloorSensed; k > -1; k--) {                           //og du vil opp, selv om heisretning er ned.
			if (k != lastFloorSensed && elevatorQueue[0][k] == 1) {
				break;
			}
			if (k == 0) {
				return 1;
			}
		}
	}
	return 0;
}


// Vi må GET elevatorDirection FØR vi stopper og så lagre denne og jobbe med denne her.
int elevatorDirection(elev_motor_direction_t motorDirection, int lastFloorSensed) {
	if (motorDirection == 1) {
		for (int i = lastFloorSensed; i < 4; i++) {
			if (i != lastFloorSensed && elevatorQueue[0][i] == 1) {
				return 1;
			}
		}
	}                                           //Retning opp. Noen over oss? Isåfall kjør opp. Ingen over oss, 
	else if (motorDirection == 1){              //Men noen under? Kjør ned!
		for (int k = lastFloorSensed; k > -1; k--) {
			if (k != lastFloorSensed && elevatorQueue[0][k] == 1) {
				return -1;
			}
		}
	}

	if (motorDirection == -1){
		for (int k = lastFloorSensed; k > -1; k--) {
			if (k != lastFloorSensed && elevatorQueue[0][k] == 1) {
				return -1;
			}
		}
	}                                            //Retning ned. Noen under oss? Isåfall kjør ned. Ingen under oss, men noen 
	else if (motorDirection == -1) {             //over? Isåfall, kjør opp!
		for (int i = lastFloorSensed; i < 4; i++) {
			if (i != lastFloorSensed && elevatorQueue[0][i] == 1) {
				return 1;
			}
		}
	}
	return 0;
}

/*int queueLightsOff(int motorDirection, int lastFloorSensed) {
	if (motorDirection == 1 && elevatorQueue[2][lastFloorSensed] == 0) {
		return 1;
	}
	if (motorDirection == -1 && elevatorQueue[1][lastFloorSensed] == 0) {
		return 1;
	}
	return 0;
}
*/