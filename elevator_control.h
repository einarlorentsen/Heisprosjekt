
#include "elev.h"

/*Funksjonsinput:
motorDirection = Forrige registrerte DIRN_UP eller DIRN_DOWN.
floor = forrige registrerte etasje */


//Stopper heis, åpner heisdør, skrur av nødvendige lys og oppdaterer elevatrorQueue.
void stopElevator(int floor, elev_motor_direction_t motorDirection);

//Lukker heisdør og setter heisen i opp eller ned-retning
void moveElevator(elev_motor_direction_t motorDirection, int floor);
