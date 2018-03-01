#include "light.h"
#include "io.h"
#include "elev.h"
#include "channels.h"
#include "queue.h"

#include <comedilib.h>

void obstructionLight() {
	elev_set_stop_lamp(elev_get_stop_signal()); //Skrur p� stopknappen hvis knappen er trykket inn
	elev_set_stop_lamp(elev_get_obstruction_signal()); //Skur p� stoppknappen hvis det kommer en obstruksjon
}

void lightsOn() {
	int floorUp = checkFloorButtonUp();
	int floorDown = checkFloorButtonDown();
	if (floorUp != -1) {
		elev_set_button_lamp(BUTTON_CALL_UP,floorUp,1);
	}
	if (floorDown != -1) {
		elev_set_button_lamp(BUTTON_CALL_DOWN, floorDown, 1);
	}
}

void lightsOff(){

}
