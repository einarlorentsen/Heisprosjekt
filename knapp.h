#inlcude "elev.h"
#include "io.h"
#include "channels.h"

int huskEtasje(); //Ser hvilken etasje vi er i
void obstruksjonLys(); //Setter p� obstruksjonslys og stopplys hvis de er trykket inn
void lys(elev_button_type_t oppEllerNed, int bestilling, int stopp); //Skrur av og p� alle lys
void settBestillingsknapp(elev_button_type_t oppEllerNed);