#pragma once

//Stopper heis, �pner d�rene og setter p� en timer som varer i 3sekunder og oppdaterer heisk�.
// Tror ikke kompilator liker m�ten denne er skrevet p�
// Hjelpevariabler for � KUN kj�re denne en gang mens timer ikke har g�tt ut?
time_t stopElevator(int lastFloorSensed, int motorDirection);


//Lukker d�rene, starter i neste retning. GJ�R NOE MED TIMEREN HER, HVIS IKKE FUNKER DEN IKKE!
int startElevator();