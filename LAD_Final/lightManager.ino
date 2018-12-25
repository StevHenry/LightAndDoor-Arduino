boolean lightState = false;
int buttonsStates[sizeof(lightButtons)];

/*
System initializer
*/
void setupLightSys() {
	int i = 0;
	for (int bu : lightButtons) {
		pinMode(bu, INPUT);
		buttonsStates[i] = digitalRead(bu);
		i++;
	}
	pinMode(lightRelay, OUTPUT);
}

/*
Changing light's Buttons checks
*/
void loopLightSys() {
	for (int i = 0; i < sizeof(lightButtons) / sizeof(lightButtons[0]); i++) {
		if (buttonsStates[i] != digitalRead(lightButtons[i])) {
			buttonsStates[i] = !buttonsStates[i];
			swapLightState("button state changed");
		}
	}
	delay(1);
}

/*
Method used to set light state
*/
void changeLightState(boolean newState, String reason) {
	lightState = newState;
	digitalWrite(lightRelay, lightState);
	Serial.print(millis());
	Serial.print(" - ");
	Serial.println(reason);
}

/*
Method used to swap light state
*/
void swapLightState(String reason) {
	changeLightState(!lightState, reason);
}

/*
0 => Eteint
1 => Allumé
*/
uint8_t getLightState() {
	return lightState;
}