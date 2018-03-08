#include "io.h"
#include "channels.h"'
#include "elev.h"'
#include "queue.h"
#include "elevator.h"
#include "elevator_control.h"
#include "timer.h"
#include "user_interface.h"

#include <stdio.h>




//Statevariable
tag_elev_motor_direction  motorDirection = DIRN_UP;
int lastFloorSensed = elev_get_floor_sensor_signal();
state_t state;
int timerFlag = 0;
int elevatorMoving = 0;


void stateMachine(){
  inputElevatorQueue();
  lightOnButtons();
  lastFloorSensed = lastFloorSensed(lastFloorSensed);

  switch (state) {
    case (READY):
    checkQueue();
    break;

    case (MOVE):
    if(elevatorMoving == 0){
      moveElevator(motorDirection, lastFloorSensed);
      elevatorMoving = 1;
      motorDirection = elevatorDirection(motorDirection,floor);
    }
    if (checkstop(motorDirection, lastFloorSensed) == 1){
      updateState(STOP);
    }

    break;

    case (STOP):
    elevatorMoving = 0;
    stopElevator(floor,motorDirection);
    break;

    case (DOORS_OPEN):

    break;

    case (DOORS_CLOSED):

    break;

    case (EMERGENCY_STOP):

    break;
  }
}
