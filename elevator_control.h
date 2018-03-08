#pragma once

typedef enum tag_state {
  INITIAL = 0,
  READY = 1,
  MOVE = 2,
  STOP = 3,
  DOORS_OPEN = 4,
  DOORS_CLOSED = 5,
  EMERGENCY_STOP = 6
} state_t;

void updateState(state_t newState);

void initializeElevator();

void elevatorReady();


//Stopper heis, �pner d�rene og setter p� en timer som varer i 3sekunder og oppdaterer heisk�.
// Tror ikke kompilator liker m�ten denne er skrevet p�
// Hjelpevariabler for � KUN kj�re denne en gang mens timer ikke har g�tt ut?
void stopElevator(int floor, elev_motor_direction_t motorDirection);

//Stoppknapp-funksjonen
time_t stopButtonElevator();

//Lukker d�rene, starter i neste retning. GJ�R NOE MED TIMEREN HER, HVIS IKKE FUNKER DEN IKKE!
int startElevator(elev_motor_direction_t motorDirection, int lastFloorSensed);

time_t stopButtonElevator();
