#include "d�rer.h"
#include "elev.h"

bool �pen=0;

void �pne() {//�pner og setter status til �pnet
	elev_set_door_open_lamp(1);
	�pen = 1;
}

void lukk() {//Lukker og setter status til lukket
	elev_set_door_open_lamp(0);
	�pen = 0;
}