#include "user_interface.h"
#include "elev.h"
#include "elevator"
#include "queue.h"

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
	for (int i = 1; i < 4; i++) {
		int success = elev_get_button_signal(BUTTON_CALL_DOWN, i);
		if (success == 1) {
			return i;
		}
	}
	return -1;
}

int checkButtonCommand() {
	for (int i = 0; i < 4; i++) {
		int success = elev_get_button_signal(BUTTON_COMMAND, i);
		if (success == 1) {
			return i;
		}
	}
	return -1;
}

void obstructionLight() {
	elev_set_stop_lamp(elev_get_stop_signal()); 
	elev_set_stop_lamp(elev_get_obstruction_signal()); 
}

void lightsOn() {
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

void lightsOff(int lastFloorSensed, tag_elev_motor_direction motorDirection) {
	if (motorDirection == 1) {                                  //Hvis jeg beveger meg OPP FRA en etasje
		elev_set_button_lamp(BUTTON_CALL_UP, lastFloorSensed, 0);
		elev_set_button_lamp(BUTTON_COMMAND, lastFloorSensed, 0);
	}
	if (motorDirection == -1) {
		elev_set_button_lamp(BUTTON_CALL_DOWN, lastFloorSensed, 0);
		elev_set_button_lamp(BUTTON_COMMAND, lastFloorSensed, 0);
	}
}