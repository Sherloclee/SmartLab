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
	 uint8_t m_input, m_output;
	 boolean m_status;
	 boolean m_problem;

 public:
	LightClass(uint8_t input,uint8_t output);
	void init();
	void on();
	void off();
};

#endif

