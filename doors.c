#include "doors.h"
#include "elev.h"

void open() {
	elev_set_door_open_lamp(1);
	bool_open = 1;
}

void close() {
	elev_set_door_open_lamp(0);
	bool_open = 0;
}
