#include "doors.h"
#include "elev.h"
#include <stdbool.h>

void open() {
	elev_set_door_open_lamp(1);
	bool bool_open = 1;
}

void close() {
	elev_set_door_open_lamp(0);
	bool bool_open = 0;
}
