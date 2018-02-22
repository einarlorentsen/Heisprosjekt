#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int checkButtonUp();
int checkButtonDown();
void makeElevatorQueue(int elevatorQueue);
void checkStop(int elevatorQueue, elev_motor_direction_t elevatorDirection, int floor);
