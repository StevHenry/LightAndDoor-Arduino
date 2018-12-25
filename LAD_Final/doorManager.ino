int8_t movementID = -1; //Movement 0 = opening | Movement 1 = closing

void setupDoorSys() {
	for (int pin : motorsPins)
		pinMode(pin, OUTPUT);
	pinMode(closedDoorSensor, INPUT);
	pinMode(openedDoorSensor, INPUT);
}

void loopDoorSys() {
	switch (movementID) {
	case 0:
		if (digitalRead(closedDoorSensor) == 1){
			delay(1250); //délai après détection
			stopDoor();
		}
		break;
	case 1:
		if (digitalRead(openedDoorSensor) == 1) {
			delay(300); //délai après détection
			stopDoor();
		}
		break;
	default:
		break;
	}
}

void runMotor(int motorIndex, int sens, boolean mustStart) {
	//MotorIndex = 0 ou 1
	motorIndex *= 3;
	if (mustStart) {
		digitalWrite(motorsPins[motorIndex + 1], sens);
		digitalWrite(motorsPins[motorIndex + 2], !sens);
		analogWrite(motorsPins[motorIndex], 255);
	}
	else {
		digitalWrite(motorsPins[motorIndex + 1], LOW);
		digitalWrite(motorsPins[motorIndex + 2], LOW);
		digitalWrite(motorsPins[motorIndex], LOW);
	}
}

void activateDoor(boolean closing) {
	movementID = !closing;
	runMotor(0, closing, true); //Porte avec sens 'closing'
	runMotor(1, 0, true);  //Poignee avec sens 0 par défaut
}

void stopDoor() {
	movementID = -1;
	runMotor(0, 0, false);
	runMotor(1, 0, false);
}

/*
0 => Porte fermee totalement
1 => Porte ouverte totalement
2 => Ouverture
3 => Fermeture
4 => Porte entre-deux sans mouvement
*/
uint8_t getDoorState() {
	if (digitalRead(closedDoorSensor) == 1) {
		return 0;
	}
	else if (digitalRead(openedDoorSensor) == 1) {
		return 1;
	}
	else if (movementID == -1) {
		return 4;
	} else
		return movementID + 2;
}