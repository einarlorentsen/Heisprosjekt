#include "user_interface.h"
#include "elev.h"
#include "elevator.h"
#include "queue.h"

int checkFloorButtonUp() {
	for (int i = 0; i < N_FLOORS - 1; i++) {
		int success = elev_get_button_signal(BUTTON_CALL_UP, i);
		if (success == 1) {
			return i;
		}
	}
	return -1;
}

int checkFloorButtonDown() {
	for (int i = 1; i < N_FLOORS; i++) {
		int success = elev_get_button_signal(BUTTON_CALL_DOWN, i);
		if (success == 1) {
			return i;
		}
	}
	return -1;
}

int checkButtonCommand() {
	for (int i = 0; i < N_FLOORS; i++) {
		int success = elev_get_button_signal(BUTTON_COMMAND, i);
		if (success == 1) {
			return i;
		}
	}
	return -1;
}

int checkButtonStop() {
	int pushedStopButton = elev_get_stop_signal();
	return pushedStopButton;
}

void lightOnButtons() {
	int floorUp = checkFloorButtonUp();
	int floorDown = checkFloorButtonDown();
	int buttonCommand = checkButtonCommand();
	if (floorUp != -1) {
		elev_set_button_lamp(BUTTON_CALL_UP, floorUp, 1);
	}
	if (floorDown != -1) {
		elev_set_button_lamp(BUTTON_CALL_DOWN, floorDown, 1);
	}
	if (buttonCommand != -1) {
		elev_set_button_lamp(BUTTON_COMMAND, buttonCommand, 1);
	}
}

void lightsOffButtons(int floor) {

	elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
}

void floorLight(int floor){
	elev_set_floor_indicator(floor);
}
