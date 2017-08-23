/*
 Name:		testEEPROM.ino
 Created:	2017/8/16 19:39:09
 Author:	Sherlock Lee

 */
#define SERVER_ADDR 0//������IP��ַ���λ��
#define SERVER_PORT 4
#define DEVICE_CODE 12		//�豸����
#define DEVICE_NAME 32		//�豸����
#define LAB_ID 82		//ʵ���ұ��

#include "DeviceInfo.h"
#include <EEPROM.h>
// the setup function runs once when you press reset or power the board
void setup() {
	write();
	//read();
}
void(*resetFunc) (void) = 0;
// the loop function runs over and over again until power down or reset
void loop() {
}

void clearEEPROM()
{
	for (int i = 0; i < 1024; i++)
	{
		EEPROM.write(i, 0x00);
	}
}

void write()
{
	Serial.begin(9600);
	DeviceInfoClass device;
	clearEEPROM();
	device.setServerAddr("10.66.106.118");
	device.setDeviceCode("01016191");
	device.setDeviceID(100);
	device.setServerPort(8080);
}

void read()
{
	Serial.begin(9600);
	DeviceInfoClass device;
	device.init();
}