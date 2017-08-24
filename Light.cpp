// 
// 
// 

#include "Light.h"

LightClass::LightClass()
{
	m_input = 5;
	m_output = 4;
	m_status = 0;
	m_problem = 0;
}

void LightClass::init(uint8_t input, uint8_t output)
{
	m_input = input;
	m_output = output;
	pinMode(m_input, INPUT);
	pinMode(m_output, OUTPUT);
	m_status = digitalRead(m_input);
	digitalWrite(m_output, HIGH);
	delay(500);
	if (m_status != digitalRead(input))
		digitalWrite(m_output, LOW);
	delay(500);
}

void LightClass::on()
{
	m_status = digitalRead(m_input);
	if (m_status == HIGH)
		return;
	else
		digitalWrite(m_output, !digitalRead(m_output));
	delay(200);
	m_status = digitalRead(m_input);
	return;
}

void LightClass::off()
{
	m_status = digitalRead(m_input);
	if (m_status == LOW)
		return;
	else
		digitalWrite(m_output, !digitalRead(m_output));
	delay(200);
	m_status == digitalRead(m_input);
	return;
}
