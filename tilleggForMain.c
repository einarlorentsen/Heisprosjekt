



if (lastFloorSensed != -1 && firstRunThrough == 0) { //Vi m� ha egen kode for f�rste runde! Dette gjelder ogs� n�dstopp
	motorDirection = getElevatorDirection(); //Henter motoretning F�R vi stopper
	timer _t seconds = stopElevator(lastFloorSensed, motorDirection); //Stopper, �pner d�ra og starter timer. Og oppdaterer heisk�
	if (startElevator() == 1 && timerflag == 0) { //Hvis timer ferdig og timerflagg ikke satt startes heisen
												  //Og timerflagg settes. 
		lightsOff(lastFloorSensed, motorDirection); //Og vi slukker lys som skal slukkes.
		firstRunThrough = 1;                        //Denne blokka kj�res EN GANG ved f�rste etasje vi n�r.
		controllDuplicateFloor = lastFloorSensed;
	}
}

if (lastFloorSensed != -1 && lastFloorSensed != controllDuplicateFloor) {
	motorDirection = getElevatorDirection();
	timer _t seconds = stopElevator(lastFloorSensed, motorDirection);
	if (startElevator() == 1 && timerflag == 0) {
		lightsOff(lastFloorSensed, motorDirection);
		controllDuplicateFloor = lastFloorSensed;
	}
}

	}