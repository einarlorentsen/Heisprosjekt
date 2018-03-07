#pragma once
#include <time.h>

//Setter timeren
time_t setTimer(int time);

//Sjekker om timer er ferdig
bool timerFinished(time_t seconds);
