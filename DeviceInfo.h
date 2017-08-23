// DeviceInfo.h

#ifndef _DEVICEINFO_h
#define _DEVICEINFO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class DeviceInfoClass
{
 private:
	 void(*resetFunc) (void) = 0;

 protected:
	 String m_ServerAddr;
	 String m_DeviceCode;
	 int	m_DeviceID;
	 int	m_ServerPort;
	 int	m_LabID;

	 String INTtoSTR(long data);

 public:
	 DeviceInfoClass()
	 {
		 m_ServerAddr = "";
		 m_DeviceCode = "";
		 m_DeviceID = 0;
		 m_ServerPort = 0;
		 m_LabID = 0;
	 }
	 void init();
	 void loadServerAddr();
	 void loadDeviceID();
	 void loadDeviceCode();
	 void loadServerPort();
	 void loadLabID();

	void setServerAddr(String ipaddr);
	void setDeviceCode(char * code);
	void setDeviceID(int id);
	void setServerPort(int port);
	void setLabID(int id);

	String getServerAddr();
	int getDeviceID();
	String getDeviceCode();
	int getServerPort();
	int getLabID();
	void reset()
	{
		resetFunc();
	}
	
};

extern DeviceInfoClass DeviceInfo;

#endif

