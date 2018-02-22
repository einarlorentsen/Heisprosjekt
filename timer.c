#include <stdlib.h>
#include <time.h>
#include "timer.h"


time_t setTimer(int setTime) {
	time_t seconds = (time(NULL)+setTime);
	return seconds;
}


int timerFinished(time_t seconds){
	time_t presentTime = (time(NULL));
	if (seconds - presentTime == 0 || seconds - presentTime < 0) {
		return 1;
	}
	else {
		return 0;
	}
}
