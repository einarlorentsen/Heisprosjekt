#include <stdlib.h>
#include <time.h>
#include "timer.h"
#include "fsm.h"

time_t setTimer(int setTime) {
	time_t seconds = (time(NULL)+setTime);
	return seconds;
}


int timerFinished(time_t seconds){

	time_t presentTime = (time(NULL));
	//printf("seconds %i , presentTime %i , equal %i \n ",seconds, presentTime, seconds ==presentTime);
	if ((seconds - presentTime) <= 0 ) {
		printf("return 1\n");
		return 1;
	}
	else {
		return 0;
	}
}

void difference(time_t seconds){
	time_t presentTime = (time(NULL));
	time_t differenceTime = seconds - presentTime;
	printf("Tiden er ferdig om: %d",differenceTime);
}
