#pragma once

//Stopper heis, åpner dørene og setter på en timer som varer i 3sekunder og oppdaterer heiskø.
// Tror ikke kompilator liker måten denne er skrevet på
// Hjelpevariabler for å KUN kjøre denne en gang mens timer ikke har gått ut?
time_t stopElevator(int lastFloorSensed, int motorDirection);


//Lukker dørene, starter i neste retning. GJØR NOE MED TIMEREN HER, HVIS IKKE FUNKER DEN IKKE!
int startElevator();