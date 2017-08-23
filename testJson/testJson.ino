/*
 Name:		testJson.ino
 Created:	2017/8/20 17:30:37
 Author:	Sherlock Lee
*/
#include <ArduinoJson.h>
using namespace ArduinoJson;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	String json;
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& object = jsonBuffer.createObject();
	object["hello"] = "word";
	object.printTo(json);
	json = "<" + json + ">";
	Serial.print(json);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
