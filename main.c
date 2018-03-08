#include "io.h"
#include "channels.h"'
#include "elev.h"'
#include "queue.h"
#include "elevator.h"
#include "elevator_control.h"
#include "timer.h"
#include "user_interface.h"
#include "fsm.h"

#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");



  initializeElevator();

    while (1) {
        stateMachine();

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

    return 0;
}
