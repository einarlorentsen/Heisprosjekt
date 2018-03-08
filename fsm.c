#include "io.h"
#include "channels.h"
#include "elev.h"
#include "queue.h"
#include "elevator.h"
#include "elevator_control.h"
#include "timer.h"
#include "user_interface.h"
#include "fsm.h"

#include <stdio.h>

//Statevariable
elev_motor_direction_t motorDirection = DIRN_UP;
int lastFloorSensed = -1;
state_t state;
int timerFlag = 0;
int elevatorMoving = 0;
time_t seconds = 0;

//Funksjoner

void updateState(state_t newState){
	state = newState;
}

void initializeElevator() {
	while (elev_get_floor_sensor_signal() == -1){
		elev_set_motor_direction(DIRN_UP);
	}
	elev_set_motor_direction(DIRN_STOP);
	updateState(READY);
}



void stateMachine(){
  inputElevatorQueue();
  lightOnButtons();

  if(elev_get_floor_sensor_signal() != -1 && elev_get_floor_sensor_signal() != lastFloorSensed){
		lastFloorSensed = elev_get_floor_sensor_signal();
	}



  floorLight(lastFloorSensed);

	if(checkButtonStop()){
		updateState(EMERGENCY_STOP);
	}

  switch (state) {
		case (INITIAL): {
				initializeElevator();
				break;
		}
    case (READY): {
      int queueCheck = checkQueue();
			if(queueCheck == 1){
				updateState(MOVE);
			}
			else if(queueCheck == 0){
				updateState(STOP);
			}
      break;
    }
    case (MOVE): {
      if(elevatorMoving == 0){
        moveElevator(motorDirection, lastFloorSensed);
        elevatorMoving = 1;
        motorDirection = elevatorDirection(motorDirection,floor);
      }
      if (checkstop(motorDirection, lastFloorSensed) == 1){
        updateState(ELEV_STOP);
      }

      break;
    }

    case (ELEV_STOP): {
      elevatorMoving = 0;
      stopElevator(floor,motorDirection);
			updateState(DOORS_OPEN);
      break;
    }

    case (DOORS_OPEN): {
      if(timerFlag == 0){
        seconds = setTimer(3);
        timerFlag = 1;
      }
      if(timerFlag == 1 && timerFinished(seconds) == 1){
        timerFlag = 0;
        updateState(DOORS_CLOSED);
      }
      break;
    }

    case (DOORS_CLOSED): {
    closeDoor();
    updateState(READY);
    break;
  }

    case (EMERGENCY_STOP): {

    break;
	}
}
}
