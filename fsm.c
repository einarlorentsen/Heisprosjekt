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
state_t state = INITIAL;
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
	printf("initialized\n");
}



void stateMachine(){

//Hjelpefunksjoner
  if(elev_get_floor_sensor_signal() != -1 && elev_get_floor_sensor_signal() != lastFloorSensed){
		lastFloorSensed = elev_get_floor_sensor_signal();
	}

  floorLight(lastFloorSensed);

	/*if(checkButtonStop()){
		updateStairectionte(EMERGENCY_STOP);
	}
	*/




//Statemachine
  switch (state) {
		case (INITIAL): {
				initializeElevator();
				break;
		}

    case (READY): {
      int queueCheck = checkQueue();
			printf("ready state\n");
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
        moveElevator(motorDirection, lastFloorSensed);
        elevatorMoving = 1;
				printf("Vi beveger oss\n");
        motorDirection = elevatorDirection(motorDirection,lastFloorSensed);
      }
			int shouldIStop = checkStop(motorDirection, lastFloorSensed);
      if (shouldIStop == 1){
				printf("Motorretning: %i\n",motorDirection);
				updateElevatorQueueAfterStop(lastFloorSensed);
				printf("HER SJEKER VI OM VI SKAL STOPPE (1 eller 0) (checkStop): %d\n",checkStop(motorDirection, lastFloorSensed));
				printQueue();
				printf("Siste etasjen vi har merket: %i\n",lastFloorSensed + 1);
        updateState(ELEV_STOP);
      }

      break;
    }

    case (ELEV_STOP): {
			printf("stopper heisen\n");
      elevatorMoving = 0;
      stopElevator(lastFloorSensed,motorDirection);
			updateState(DOORS_OPEN);
      break;
    }

    case (DOORS_OPEN): {
			//printf("DOORS_OPEN_STATE\n");
      if(timerFlag == 0){
        seconds = setTimer(3);
        timerFlag = 1;
      }
      if((timerFlag == 1) && (timerFinished(seconds) == 1)){
        timerFlag = 0;
				printf("åpner dørene\n" );
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
			if(elev_get_floor_sensor_signal() == -1){
				updateState(READY);
			}
			else {
				updateState(ELEV_STOP);
				printf("EMERGENCY SETTER STOPP");
			}
    break;
	}
}
}
