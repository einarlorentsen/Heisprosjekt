#include "d�rer.h"
#include "elev.h"

bool �pen=0;

void �pne() {
	elev_set_door_open_lamp(1);
	�pen = 1;
}

void lukk() {
	elev_set_door_open_lamp(0);
	�pen = 0;
}