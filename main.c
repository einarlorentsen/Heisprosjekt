#include "io.h"
#include "channels.h"'
#include "elev.h"'
#include "doors.h"
#include "queue.h"
#include "elevator.h"
#include "elevator_control.h"
#include "timer.h"
#include "user_interface.h"

#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

	//Kontrollvariable
	tag_elev_motor_direction  motorDirection;
	int lastFloorSensed = lastFloorSensed();
	int controllDuplicateFloor;
	int newRunThrough = 0;
	int timerFlag = 0;

    elev_set_motor_direction(DIRN_UP);

    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

		lightsOn();                         //Lytter hele tiden etter trykk og hvilken etasje vi er i
		inputElevatorQueue();
		lastFloorSensed = lastFloorSensed();
		
		if (lastFloorSensed != -1 && timerFlag == 0) { //Vi må ha egen kode for første runde! Dette gjelder også nødstopp
			motorDirection = getElevatorDirection(); //Henter motoretning FØR vi stopper
			timer _t seconds = stopElevator(lastFloorSensed, motorDirection); //Sjekker om vi skal stoppe, og hvis så: 
			                                                                  //Stopper, åpner døra og starter timer. Og oppdaterer heiskø
			if (seconds != 0) {
				timerFlag = 1; //Hvis vi stopper og setter timer, skal vi IKKE sette den igjen i samme etasje!
			}

		}
		if (startElevator() == 1 && newRunthrough == 0) { //Hvis timer ferdig og vi ikke har startet heise,  startes den
													  //Og flagg settes. 
			lightsOff(lastFloorSensed, motorDirection); //Og vi slukker lys som skal slukkes.
			newRunThrough = 1;                        //Denne blokka kjøres EN GANG ved hver etasje vi når.
			controllDuplicateFloor = lastFloorSensed; //passer 
		}

		//DETTE BLIR FEIL MED TANKE PÅ KONTROLLERE AT IKKE KJØRES FLERE GANGER PÅ BAKGRUNN AV ETASJE


    return 0;
}
