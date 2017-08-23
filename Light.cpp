// 
// 
// 

#include "Light.h"

LightClass::LightClass(uint8_t input, uint8_t output)
{
	m_input = input;
	m_output = output;
	pinMode(input, INPUT);
	pinMode(output, OUTPUT);
	m_status = digitalRead(input);
	if (m_status == HIGH)
		digitalWrite(output, HIGH);
	else
		digitalWrite(output, LOW);
}

void LightClass::init()
{

}

void LightClass::on()
{
	if (m_status == HIGH)
		return;
	else
		digitalWrite(m_output, !digitalRead(m_output));
}

void LightClass::off()
{
	if (m_status == LOW)
		return;
	else
		digitalWrite(m_output, !digitalRead(m_output));
}

