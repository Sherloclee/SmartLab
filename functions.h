// ctrl.h

#ifndef _FUNCTIONS_h
#define _FUNCTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <ArduinoJson.h>
namespace Ctrl
{
	//���������ӽ��е���
	void setting(ArduinoJson::JsonObject& json);
	//��������
	void run(ArduinoJson::JsonObject& json);
	//��ȡ����
	String SerialRead();
	String WifiRead();
}

namespace Transform
{
	using ArduinoJson::JsonObject;
	String Prosess(String str);
	JsonObject& strParsing(String str);
}
#endif

//{"type":"action","deviceCode":"010161901","actionCode":"0101","time":"170820185620"}
