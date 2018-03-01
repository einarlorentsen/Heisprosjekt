
#include "channels.h"
#include "doors.h"
#include "elev.h"
#include "elevator.h"
#include "elevatorControl.h"
#include "io.h"
#include "light.h"
#include "queue.h"
#include "timer.h"
#include <stdio.h>



int main() {
    // Initialize hardware
    printf("started main\n");
    elev_init();
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware...!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    //Setter noen globale variabler
    elev_motor_direction_t elevatorDirection = DIRN_UP; //Dette er for å ha en global variabel som vi kan endre utover i programmet.
    elev_set_motor_direction(elevatorDirection);

    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        //Starten på vårt program
        int sensedFloor = lastFloorSensed(); //Får ut den siste etasjen vi har vært i

        updateElevatorQueue(initializaElevatorQueue);
        int whereToStop = elevatorStop(initializaElevatorQueue,elevatorDirection, sensedFloor);
        checkStop(initializaElevatorQueue,elevatorDirection,whereToStop);
        time_t startStopTime = stopTheElevator(initializaElevatorQueue,elevatorDirection,sensedFloor);
        if (timerFinished(startStopTime) == 1){
          closeDoor();
          elev_set_motor_direction(elevatorDirection);
        }


        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}
