#include "elev.h"
#include "heis.h"
#include "d�rer.h"


elev_button_type_t retning;

int n�v�rendeEtasje;

void setN�v�rendeEtasje() {//Etasje lik n�v�rende signal
	n�v�rendeEtasje= elev_get_floor_sensor_signal(void);
}

void kj�rStopp() { //Kj�r eller stopp avhengig av motorretning
	elev_set_motor_direction(elev_motor_direction_t retning);
}


void n�dstopp() {
	retning = 0;
	elev_set_motor_direction(elev_motor_direction_t retning); //Disse to linjene stopper heisen
	//T�m k�
	if (elev_get_floor_sensor_signal(void)>=0){ //Hvis i etasje �pne d�r
		�pne();
	}
	//Hva med 3sek regel etterp�? Se 4.6
}