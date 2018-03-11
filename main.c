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


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    while (1) {
      //Lytter etter input fra knapper og setter tilsvarende lys
      inputElevatorQueue();

      //Lytter etter stoppknapp
      checkButtonStop();

      //Kjører statemaskinen heis
      stateMachine();

  }
  return 1;
}
