/*
 Name:		testLight.ino
 Created:	2017/8/24 12:17:41
 Author:	Sherlock Lee
*/

// the setup function runs once when you press reset or power the board

#include "Light.h"
#include "functions.h"
LightClass light;
void setup() {
	light.init(5, 4);
	light.on();
	delay(2000);
	light.off();
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
