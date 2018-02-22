#include <stdlib.h>
#include <time.h>
#include <timer.h>


time_h setTimer(int tid) {
	time_h seconds = time(NULL)+tid;
	return seconds;
}


int timerFerdig(time_h seconds){
	time_h = nåværendeTid;
	if (seconds - nåværendeTid = 0 || seconds - nåværendeTid < 0) {
		return 1;
	}
	else {
		return 0;
	}
}

