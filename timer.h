#pragma once
#include <time.h>

//Setter timeren i "time" sekunder
time_t setTimer(int time);

//Sjekker om timer er ferdig
int timerFinished(time_t seconds);
