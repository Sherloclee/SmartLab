// Light.h

#ifndef _LIGHT_h
#define _LIGHT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class LightClass
{
 protected:
	uint8_t m_input	=5;
	uint8_t m_output=4;
	boolean m_status=0;
	boolean m_problem=0;

 public:
	LightClass();
	void init(uint8_t input, uint8_t output);
	void on();
	void off();
};
extern LightClass light;
#endif

