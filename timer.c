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
	if ((seconds == presentTime)  ) {
		printf("return 1\n");
		return 1;
	}
	else {
		return 0;
	}
}
