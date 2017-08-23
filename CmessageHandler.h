// CmessageHandler.h

#ifndef _CMESSAGEHANDLER_h
#define _CMESSAGEHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class CmessageHandlerClass:private String
{
private:
	char * m_message = begin();
	protected:

	public:
		CmessageHandlerClass():String(){}
		CmessageHandlerClass(String str):String(str){}
		String Prosess(String str);
		void Parsing();
		void init();
};

extern CmessageHandlerClass CmessageHandler;

#endif

