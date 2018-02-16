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
	elev_set_stop_lamp(elev_get_stop_signal()); //Skrur p� stopknappen hvis knappen er trykket inn
	elev_set_stop_lamp(elev_get_obstruction_signal()); //Skur p� stoppknappen hvis det kommer en obstruksjon
}

void lys(elev_button_type_t oppEllerNed, int bestilling, int stopp) {//Tanken er at n�r en kar trykker p� en bestillingsknapp f�r vi vite gjennom bestilling hvilken etasje han vil til
	int etasje = huskEtasje();                                      //og gjennom oppOgNed hvilken vei han vil. Vet ikke om stopp skal v�re "int", se mer info om stopp i if-setningen
	int knappTrykk = elev_get_button_signal(oppEllerNed, etasje);
	obstruksjonLys();
	elev_set_button_lamp(oppEllerNed, bestilling, 1); //Skrur p� bestillingsknappene
	if (etasje == bestilling && stopp) { //M� sjekke om heisen ogs� skal stoppe, siden hvis heisen bare passerer, men ikke skal stoppe kan vi ikke skru av lampa
		elev_set_button_lamp(oppEllerNed, etasje, 0); //Skrur av bestillingsknappene
	}
	elev_set_floor_indicator(etasje); //Ser hvilken etasje heisen er i
}

void settBestillingsknapp(elev_button_type_t oppEllerNed) {
	
}