#include <stdlib.h>
#include <time.h>
#include <timer.h>


time_h setTimer(int setTime) {
	time_h seconds = time(NULL)+setTime;
	return seconds;
}


int timerFinished(time_h seconds){
	time_h = presentTime;
	if (seconds - presentTime == 0 || seconds - presentTime < 0) {
		return 1;
	}
	else {
		return 0;
	}
}

