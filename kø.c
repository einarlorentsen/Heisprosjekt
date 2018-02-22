#include "kø.h"
#include "elev.h"


int sjekkKnappOpp() {
	int suksess = 0;
	for (int i = 0; i < 3; i++) {
		suksess = elev_get_button_signal(BUTTON_CALL_UP, i);
		if (suksess == 1) {
			return i;
		}
	}
	return 0;
}

int sjekkKnappNed() {
	for (int i = 1; i < 4; i++) {
		suksess = elev_get_button_signal(BUTTON_CALL_DOWN, i);
		if (suksess == 1) {
			return i;
		}
	}
	return 0;
}

void heisKø(int heiskø) {
	int etasjeOpp = sjekkKnappOpp();
	int etasjeNed = sjekkKnappNed();
	if (etasjeOpp != 0) {
		heiskø[etasjeOpp][BUTTON_CALL_UP];
	}
	if (etasjeNed != 0) {
		heiskø[etasjeNed][BUTTON_CALL_DOWN];
	}
}

void sjekkStopp(int heiskø, elev_motor_direction_t heisRetning, int etasje) {
	for (int j = 0; j < 4; j++) {
		if (heisRetning == 1 && etasje =< i && heiskø[1][j] == 0) {
			heiskø[0][j] = 1;
		}
	}
	for (int k = 0; k < 4; k++) {
		if (heisRetning == -1 && etasje => i && heiskø[1][k] == 1) {
			heiskø[0][k] = 1;
		}
	}
}