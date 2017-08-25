#include "functions.h"
#include "DeviceInfo.h"
#include "Light.h"
#include <SoftwareSerial.h>
#include <MsTimer2.h>
#include <EEPROM.h>
#include "WiFi.h"
#include <ArduinoJson.h>
#include <avr/interrupt.h>

#define ON 1
#define OFF 0
#define NOP do{__asm__ __volatile__("nop");}while(0)

extern WiFiClass wifi(10, 11);
LightClass light;
DeviceInfoClass device;

String	serverIP;
int		serverPort;
String	deviceCode;
int		deviceID;
int		mode = 0;
int		time;

void setup()
{
	light.init(5,4);
	//初始化信息
	Serial.begin(9600);
	Serial.println("setup");
	device.init();
	serverIP	= device.getServerAddr();
	serverPort	= device.getServerPort();
	deviceCode	= device.getDeviceCode();
	deviceID	= device.getDeviceID();
	//启动wifi
	Serial.println(serverIP);
	Serial.println(serverPort);
	wifi.init(serverIP, serverPort);
	//启用串口
	
	while (!Serial);
	//启用定时中断
	//MsTimer2::set(10000, heartpack);
	//MsTimer2::start();
	time = millis()/1000;
}

void loop()
{
	if ((millis()/1000)-time >= 10)
	{
		time = millis()/1000;
		Serial.println(millis()/1000);
		heartpack(time);
		for (int i = 0; i < 500;i++)
		{
			Ctrl::delay_(10);
			if (wifi.available())
			{
				Ctrl::WifiRead();
				break;
			}
		}

	}
	if (Serial.available())
	{
		String message;
		String type;
		message = Ctrl::SerialRead();
		Serial.println(message);
		ArduinoJson::JsonObject& json = Transform::strParsing(message);
		type = json["type"].as<String>();
		if (type == "setting")
			Ctrl::setting(json);
	}
	if (wifi.available())
	{
		String message;
		String type;
		message = Ctrl::WifiRead();
		Serial.println(message);
		ArduinoJson::JsonObject& json = Transform::strParsing(message);
		type = json["type"].as<String>();
		if (type == "action")
		{
			Ctrl::run(json,wifi);
		}
	}
	delay(2);
}

//心跳包
void heartpack(int time)
{
	String Heart;
	String json;
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& object = jsonBuffer.createObject();
	object["type"] = "heart";
	object["deviceCode"] = deviceCode;
	object["time"] = String(time);
	object.printTo(Heart);
	Heart = "<"+Heart+">";
	wifi.Send(Heart);
	Serial.println(Heart);
}

//<{"type":"action","deviceCode":"010161901","actionCode":"0101","time":"20"}>
//<{"type":"recvAction","deviceCode":"0101","actionCode":"0101","result":0,"time":"20"}>
//<{"type":"heart","deviceCode":"01016191","time":"20"}>
//<{"type":"recvheart","deviceCode":"01016191","time":"20"}>