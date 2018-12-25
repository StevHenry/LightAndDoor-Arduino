//DOOR
#define closedDoorSensor A3
#define openedDoorSensor A4
const int motorsPins[] = { 9, 8, 7, 3, 4, 2 };
//3 pins par moteur |#| ENABLE_A(PWM) - IN1 - IN2 - ENABLE_B(PWM) - IN3 - IN4 |#| Moteur 0 = Porte / Moteur 1 = Poignee


//LIGHT
#define lightRelay A1
const int lightButtons[] = { A2 };

//CONNECTION
/*Shield pose sur l'arduino*/

void setup() {
	setupConnectionSys();
	setupDoorSys();
	setupLightSys();

	Serial.begin(19200);
	Serial.print("Beggined on ");
	Serial.println(millis());
}

void loop() {
	loopConnectionSys();
	loopDoorSys();
	loopLightSys();
}