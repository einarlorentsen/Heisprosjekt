#include "elev.h"
#include "heis.h"
#include "dører.h"


elev_button_type_t retning;

int nåværendeEtasje;

void setNåværendeEtasje() {//Etasje lik nåværende signal
	nåværendeEtasje= elev_get_floor_sensor_signal(void);
}

void kjørStopp() { //Kjør eller stopp avhengig av motorretning
	elev_set_motor_direction(elev_motor_direction_t retning);
}


void nødstopp() {
	retning = 0;
	elev_set_motor_direction(elev_motor_direction_t retning); //Disse to linjene stopper heisen
	//Tøm kø
	if (elev_get_floor_sensor_signal(void)>=0){ //Hvis i etasje åpne dør
		åpne();
	}
	//Hva med 3sek regel etterpå? Se 4.6
}