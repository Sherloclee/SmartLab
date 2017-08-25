// ctrl.h

#ifndef _FUNCTIONS_h
#define _FUNCTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <ArduinoJson.h>
#include "WiFi.h"
namespace Ctrl
{
	//与计算机连接进行调试
	void setting(ArduinoJson::JsonObject& json);
	//正常运行
	void run(ArduinoJson::JsonObject& json, WiFiClass wifi);
	//读取串口
	String SerialRead();
	String WifiRead();
	void delay_(int n);
}

namespace Transform
{
	using ArduinoJson::JsonObject;
	String Prosess(String str);
	JsonObject& strParsing(String str);
	int toDig(char n);
	int toINT(String hex);
}
#endif

//{"type":"action","deviceCode":"010161901","actionCode":"0101","time":"170820185620"}
