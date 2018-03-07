



if (lastFloorSensed != -1 && firstRunThrough == 0) { //Vi må ha egen kode for første runde! Dette gjelder også nødstopp
	motorDirection = getElevatorDirection(); //Henter motoretning FØR vi stopper
	timer _t seconds = stopElevator(lastFloorSensed, motorDirection); //Stopper, åpner døra og starter timer. Og oppdaterer heiskø
	if (startElevator() == 1 && timerflag == 0) { //Hvis timer ferdig og timerflagg ikke satt startes heisen
												  //Og timerflagg settes. 
		lightsOff(lastFloorSensed, motorDirection); //Og vi slukker lys som skal slukkes.
		firstRunThrough = 1;                        //Denne blokka kjøres EN GANG ved første etasje vi når.
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