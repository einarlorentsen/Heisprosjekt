#include "dører.h"
#include "elev.h"

bool åpen=0;

void åpne() {//Åpner og setter status til åpnet
	elev_set_door_open_lamp(1);
	åpen = 1;
}

void lukk() {//Lukker og setter status til lukket
	elev_set_door_open_lamp(0);
	åpen = 0;
}