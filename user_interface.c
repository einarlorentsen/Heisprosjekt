#include "user_interface.h"
#include "elev.h"
#include "elevator.h"
#include "queue.h"
#include "fsm.h"


int checkButtonHoldInFloor(int floor){
	for (int button = 0; button < TYPE_BUTTON; button ++){
		if (floor == 0 && button == 1) continue;
		if (floor == 3 && button == 0) continue;
		if (elev_get_button_signal(button,floor) == 1){
			return 0;
		}
	}
	return 1;
}

void lightsOffButtons(int floor) {
	if (floor < 3 && floor > -1){
		elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
	}
	if (floor > 0){
		elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
	}
	if (floor > -1){
		elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
	}
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

	while(1) {
		if (elev_get_stop_signal() != 1) {
            elev_set_stop_lamp(0);
            break;
        }
	}
}

void floorLight(int floor){
	if (floor != -1){
		elev_set_floor_indicator(floor);
	}
}
