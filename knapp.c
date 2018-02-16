#include "knapp.h"
#include "io.h"
#include "elev.h"
#include "channels.h"

#include <comedilib.h>

int huskEtasje() {
	int etasje = -1
	while (etasje == -1) {
		etasje = elev_get_floor_sensor_signal();
	}
	return etasje;
}

void obstruksjonLys() {
	elev_set_stop_lamp(elev_get_stop_signal()); //Skrur på stopknappen hvis knappen er trykket inn
	elev_set_stop_lamp(elev_get_obstruction_signal()); //Skur på stoppknappen hvis det kommer en obstruksjon
}

void lys(elev_button_type_t oppEllerNed, int bestilling, int stopp) {//Tanken er at når en kar trykker på en bestillingsknapp får vi vite gjennom bestilling hvilken etasje han vil til
	int etasje = huskEtasje();                                      //og gjennom oppOgNed hvilken vei han vil. Vet ikke om stopp skal være "int", se mer info om stopp i if-setningen
	int knappTrykk = elev_get_button_signal(oppEllerNed, etasje);
	obstruksjonLys();
	elev_set_button_lamp(oppEllerNed, bestilling, 1); //Skrur på bestillingsknappene
	if (etasje == bestilling && stopp) { //Må sjekke om heisen også skal stoppe, siden hvis heisen bare passerer, men ikke skal stoppe kan vi ikke skru av lampa
		elev_set_button_lamp(oppEllerNed, etasje, 0); //Skrur av bestillingsknappene
	}
	elev_set_floor_indicator(etasje); //Ser hvilken etasje heisen er i
}

void settBestillingsknapp(elev_button_type_t oppEllerNed) {
	
}