// 
// 
// 

#include "functions.h"
#include <ArduinoJson.h>
#include "WiFi.h"

namespace Ctrl
{
	//���������ӽ��е���
	void setting(ArduinoJson::JsonObject& json)
	{
		String m_ServerAddr = json["Server_Addr"].asString();
		String m_DeviceCode = json["Device_Code"].asString();
		int	m_DeviceID		= json["Device_ID"].as<int>();
		int	m_ServerPort	= json["Server_Port"].as<int>();
		int	m_LabID			= json["Lab_ID"].as<int>();
	}
	//��������
	void run(ArduinoJson::JsonObject& json)
	{
		String actionCode = json["actionCode"].as<String>();

		Serial.println(actionCode);

	}
	//��Ϣ����

	//��ȡ����
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
	//��ȡwifi
	String WifiRead()
	{
		return wifi.Recv();
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
}