// 
// 
// 

#include "functions.h"
#include "Light.h"
#include <ArduinoJson.h>
#include "WiFi.h"
#define NOP do{__asm__ __volatile__("nop");}while(0)
namespace Ctrl
{
	//与计算机连接进行调试
	void setting(ArduinoJson::JsonObject& json)
	{
		String m_ServerAddr = json["Server_Addr"].asString();
		String m_DeviceCode = json["Device_Code"].asString();
		int	m_DeviceID		= json["Device_ID"].as<int>();
		int	m_ServerPort	= json["Server_Port"].as<int>();
		int	m_LabID			= json["Lab_ID"].as<int>();
	}
	//正常运行
	void run(ArduinoJson::JsonObject& json,WiFiClass wifi)
	{
		String actionCode = json["actionCode"].as<String>();
		int action = Transform::toINT(actionCode)&(0x00FF);
		Serial.println(action);
		switch (action)
		{
		case 1:
			light.on();
			wifi.Send("<{\"type\":\"recvAction\",\"result\":\"1\"}>");
			break;
		case 0:
			light.off();
			wifi.Send("<{\"type\":\"recvAction\",\"result\":\"1\"}>");
			break;
		default:
			break;
		}
	}
	//消息处理

	//读取串口
	String SerialRead()
	{
		String message;
		while (Serial.available())
		{
			message += char(Serial.read());
			delay(1);
		}
		message = Transform::Prosess(message);
		return message;
	}
	//读取wifi
	String WifiRead()
	{
		return wifi.Recv();
	}

	void delay_(int n)
	{
		for (; n >0;n--)
			for (int i = 0; i < 3180; i++)
			{
				NOP;
			}
	}
}

namespace Transform
{
	using ArduinoJson::JsonObject;
	String Prosess(String str)
	{
		String _str;
		int index;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '<')
			{
				index = i + 1;
				break;
			}
		}
		for (int i = index; i <= str.length(); i++)
		{
			if (str[i] == '>')
				return _str;
			_str += str[i];
		}
		return "";
	}
	JsonObject& strParsing(String str)
	{
		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& json = jsonBuffer.parse(str);
		return json;
	}
	int toINT(String hex)
	{
		int sum = 0;
		for (int i = 0;i<hex.length();i++)
		{
			sum = sum * 16 + toDig(hex[i]);
		}
		return sum;
	}
	int toDig(char n)
	{
		if ((n >= '0') && (n <= '9'))
		{
			return n - 48;
		}
		if (isalpha(n))
			return isupper(n) ? n - 55 : n - 87;
	}
}