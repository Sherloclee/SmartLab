/*
 Name:		testWiFi.ino
 Created:	2017/8/20 13:12:53
 Author:	Sherlock Lee
*/

// the setup function runs once when you press reset or power the board
#include "WiFi.h"
#include <ArduinoJson.h>

void setup() {
	WiFiClass wifi(10, 11);
	wifi.init("10.66.106.118", 8080);
	Serial.begin(9600);
	String Heart;
	String json;
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& object = jsonBuffer.createObject();
	object["type"] = "heart";
	object["deviceCode"] = "010161901";
	object["time"] = "100";
	object.printTo(Heart);
	Heart = "<" + Heart + ">";
	Serial.println(Heart);
	wifi.Send(Heart);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	
}
