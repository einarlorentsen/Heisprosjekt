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
#include <unistd.h>

//Hjelpevariable
elev_motor_direction_t motorDirection = DIRN_UP;
int lastFloorSensed = -1;
state_t state = INITIAL;
int elevatorMoving = 0;
time_t seconds = 0;

int timerFlag = 0;
int sameFloorButtonHoldFlag = 0;
int emergencyStopFlag = 0;

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

void checkButtonStop(){
	if(elev_get_stop_signal() == 1){
		updateState(EMERGENCY_STOP);
	}
}

void stateMachine(){

	//Lagrer forrige registrerte etasje
  if(elev_get_floor_sensor_signal() != -1 && elev_get_floor_sensor_signal() != lastFloorSensed){
		lastFloorSensed = elev_get_floor_sensor_signal();
	}

	//Setter etasjeindikator-lys
  floorLight(lastFloorSensed);




//Statemachine
  switch (state) {
		case (INITIAL): {
				initializeElevator();
				break;
		}

    case (READY): {
      int queueCheck = checkQueue();
			if((queueCheck == 0 || queueCheck == 1) && emergencyStopFlag == 1){
				updateState(MOVE);
			}
			if(queueCheck == 1){
				updateState(MOVE);
			}
			else if(queueCheck == 0){
				updateState(ELEV_STOP);
			}
      break;
    }

    case (MOVE): {
      if(elevatorMoving == 0){
				if (emergencyStopFlag == 1){
					elev_set_motor_direction(elevatorResetAfterEmergency(motorDirection,lastFloorSensed));
					emergencyStopFlag = 0;
					elevatorMoving = 1;
        	motorDirection = elevatorResetAfterEmergency(motorDirection,lastFloorSensed);
					lastFloorSensed = -1;
				}
				else{
					moveElevator(motorDirection, lastFloorSensed);
					elevatorMoving = 1;
					motorDirection = elevatorDirection(motorDirection,lastFloorSensed);
				}

      }
			int shouldIStop = 0;
			if(elev_get_floor_sensor_signal() != -1){
				shouldIStop = checkStop(motorDirection, lastFloorSensed);
				checkStop(motorDirection,lastFloorSensed);
			}
      if (shouldIStop == 1){
        updateState(ELEV_STOP);
      }

      break;
    }

    case (ELEV_STOP): {
      elevatorMoving = 0;
			updateElevatorQueueAfterStop(lastFloorSensed);
      stopElevator(lastFloorSensed,motorDirection);
			updateState(DOORS_OPEN);
      break;
    }

    case (DOORS_OPEN): {
			openDoor();
			if(sameFloorButtonHoldFlag == 0 && checkButtonHoldInFloor(lastFloorSensed) == 0){
					timerFlag = 0;
					sameFloorButtonHoldFlag = 1;
					updateElevatorQueueAfterStop(lastFloorSensed);
			}
      else if(timerFlag == 0 && sameFloorButtonHoldFlag == 1 && checkButtonHoldInFloor(lastFloorSensed) == 1){
				lightsOffButtons(lastFloorSensed);
        seconds = setTimer(3);
				sameFloorButtonHoldFlag = 0;
        timerFlag = 1;
      }
			else if (timerFlag == 0 && sameFloorButtonHoldFlag == 0){
        seconds = setTimer(3);
        timerFlag = 1;
			}
      if((timerFlag == 1) && (timerFinished(seconds) == 1)){
				lightsOffButtons(lastFloorSensed);
				updateElevatorQueueAfterStop(lastFloorSensed);
				sameFloorButtonHoldFlag = 0;
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
			timerFlag = 0;
			sameFloorButtonHoldFlag = 0;
			stopButtonElevator();
			elevatorMoving = 0;
			if(elev_get_floor_sensor_signal() == -1){
				emergencyStopFlag = 1;
				updateState(READY);
			}
			else {
				updateState(ELEV_STOP);
			}
    break;
	}
}
}
