// WiFi.h

#ifndef _WIFI_h
#define _WIFI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <SoftwareSerial.h>

class WiFiClass:public SoftwareSerial
{
 protected:
	 String m_Server;
	 String m_port;

 public:
	WiFiClass(int rx, int tx) :SoftwareSerial(rx, tx) { begin(9600); };
	int init(String server, int port );
	void stop();
	void setServer(String Server);
	void setPort(int port);

	String Send(String Message);
	String Recv();
	int is_available();
	int connectWiFi();
	int connectWiFi(String SSID, String PW);
	int connectSocket(String server,int port);

};
extern WiFiClass wifi;
#endif

