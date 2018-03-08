
#include "elev.h"

void initializeElevator();


//Stopper heis, �pner d�rene og setter p� en timer som varer i 3sekunder og oppdaterer heisk�.
// Tror ikke kompilator liker m�ten denne er skrevet p�
// Hjelpevariabler for � KUN kj�re denne en gang mens timer ikke har g�tt ut?
void stopElevator(int floor, elev_motor_direction_t motorDirection);

void moveElevator(elev_motor_direction_t motorDirection, int lastFloorSensed);

//Stoppknapp-funksjonen
void stopButtonElevator();
