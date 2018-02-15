#include "dører.h"
#include "elev.h"

bool åpen=0;

void åpne() {
	elev_set_door_open_lamp(1);
	åpen = 1;
}

void lukk() {
	elev_set_door_open_lamp(0);
	åpen = 0;
}