// 
// 
// 

#include "CmessageHandler.h"
#include <ArduinoJson.h>
using namespace ArduinoJson;

void CmessageHandlerClass::init()
{
	
}

void CmessageHandlerClass::Parsing()
{
	StaticJsonBuffer<200> jbuffer;
	JsonObject& root = jbuffer.parseObject(m_message);
	String deviceCode;
}

String CmessageHandlerClass::Prosess(String str)
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
		return "";
	}
	for (int i = index; i <= str.length(); i++)
	{
		if (str[i] == '>')
			return _str;
		_str += str[i];
	}
	return "";
}
CmessageHandlerClass CmessageHandler;

