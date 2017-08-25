/*
 Name:		testDelay.ino
 Created:	2017/8/25 21:11:33
 Author:	Sherlock Lee
*/
#define NOP do{__asm__ __volatile__("nop");}while(0)
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	unsigned long time1,time2;
	time1 = millis();
	delay_(10000);
	time2 = millis();
	Serial.println(time2 - time1);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}


void delay_(int n)
{
	for (; n > 0; n--)
		for (int i = 0; i < 3180; i++)
		{
			NOP;
		}
}