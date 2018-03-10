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

//Statevariable
elev_motor_direction_t motorDirection = DIRN_UP;
int lastFloorSensed = -1;
state_t state = INITIAL;
int timerFlag = 0;
int elevatorMoving = 0;
time_t seconds = 0;
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
	printf("initialized\n");
}

void checkButtonStop(){
	if(elev_get_stop_signal() == 1){
		updateState(EMERGENCY_STOP);
	}
}

void stateMachine(){

//Hjelpefunksjoner
  if(elev_get_floor_sensor_signal() != -1 && elev_get_floor_sensor_signal() != lastFloorSensed){
		lastFloorSensed = elev_get_floor_sensor_signal();
	}

  floorLight(lastFloorSensed);




//Statemachine
  switch (state) {
		case (INITIAL): {
			printf("INITIAL state:");
				initializeElevator();
				break;
		}

    case (READY): {
			printf("ready state\n");
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
			printf("MOVE state: \n");
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
			}
      if (shouldIStop == 1){
        updateState(ELEV_STOP);
      }

      break;
    }

    case (ELEV_STOP): {
			printf("ELEV_STOP state:\n");
      elevatorMoving = 0;
			updateElevatorQueueAfterStop(lastFloorSensed);
      stopElevator(lastFloorSensed,motorDirection);
			updateState(DOORS_OPEN);
      break;
    }

    case (DOORS_OPEN): {
			printf("DOORS_OPEN_STATE\n");
			openDoor();
      if(timerFlag == 0){
				printf("Setter timeren \n");
        seconds = setTimer(3);
        timerFlag = 1;
      }

			difference(seconds);
			
      if((timerFlag == 1) && (timerFinished(seconds) == 1)){
				printf("Timeren er ferdig");
        timerFlag = 0;
        updateState(DOORS_CLOSED);
      }
      break;
    }

    case (DOORS_CLOSED): {
			printf("lukker dørene\n");
	    closeDoor();
	    updateState(READY);
	    break;
  }

    case (EMERGENCY_STOP): {
			printf("EMERGENCY!!!\n");
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
