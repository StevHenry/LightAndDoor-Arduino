#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x49, 0x1C, 0x99, 0xAA, 0x99, 0x8c };

IPAddress ip(192, 254, 182, 124);
EthernetServer server(550);

void setupConnectionSys() {
	Ethernet.begin(mac, ip);
	server.begin();
}

void loopConnectionSys() {
	EthernetClient client = server.available();
	if (client) {
		boolean currentLineIsBlank = true;
		if (client.connected() && client.available()) {
			switch (client.read()) {
			case '0':
				changeLightState(0, "received ethernet request: off");
				break;
			case '1':
				changeLightState(1, "received ethernet request: on");
				break;
			case '2':
				swapLightState("received ethernet request: swap");
				break;
			case '3':
				activateDoor(true);
				break;
			case '4':
				activateDoor(false);
				break;
			case '10':
			case 'G':
			case '\n':
				  if (currentLineIsBlank) {
						client.println("HTTP/1.1 200 OK");
						client.println("Content-Type: text/xml");
						client.println("Connection: close");
						client.println();
						client.println("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>");
						client.println("<informations>");
						client.print("<light>");
						client.print(getLightState());
						client.println("</light>");
						client.print("<door>");
						client.print(getDoorState());
						client.println("</door>");
						client.print("</informations>");
					}
				currentLineIsBlank = true;
				break;
			case '\r':
				currentLineIsBlank = false;
				break;
			default:
				break;
			}
		}
		delay(1);
		client.stop();
	}
}