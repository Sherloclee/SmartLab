#include "functions.h"
#include "DeviceInfo.h"
#include "Light.h"
#include <SoftwareSerial.h>
#include <MsTimer2.h>
#include <EEPROM.h>
#include "WiFi.h"
#include <ArduinoJson.h>

#define ON 1
#define OFF 0

extern WiFiClass wifi(10, 11);
extern LightClass Light(4, 5);
DeviceInfoClass device;

String	serverIP;
int		serverPort;
String	deviceCode;
int		deviceID;
int		mode = 0;

void setup()
{
	//��ʼ����Ϣ
	Serial.begin(9600);
	device.init();
	serverIP	= device.getServerAddr();
	serverPort	= device.getServerPort();
	deviceCode	= device.getDeviceCode();
	deviceID	= device.getDeviceID();
	//����wifi
	Serial.println(serverIP);
	Serial.println(serverPort);
	wifi.init(serverIP, serverPort);
	//���ô���
	
	while (!Serial);
	//���ö�ʱ�ж�
	MsTimer2::set(10000, heartpack);
	MsTimer2::start();
}

void loop()
{
	if (Serial.available())
	{
		String message;
		String type;
		message = Ctrl::SerialRead();
		Serial.println(message.begin());
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
			Ctrl::run(json);
	}
	delay(2);
}

//������
void heartpack()
{
	String Heart;
	String json;
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& object = jsonBuffer.createObject();
	object["type"] = "heart";
	object["deviceCode"] = deviceCode;
	object["time"] = String(millis()/1000);
	object.printTo(Heart);
	Heart = "<"+Heart+">";
	wifi.Send(Heart);
	Serial.println(Heart);
}