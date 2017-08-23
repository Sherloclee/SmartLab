
#define SERVER_ADDR 0		//服务器IP地址存放位置
#define SERVER_PORT_HIGH 4	//服务器端口高八位
#define SERVER_PORT_LOW 5	//服务器端口第八位
#define DEVICE_ID_HIGH 8	//设备ID高八位
#define DEVICE_ID_LOW  10	//设备ID第八位
#define DEVICE_CODE 12		//设备代号
#define LAB_ID 82			//实验室编号

#include "DeviceInfo.h"
#include <EEPROM.h>

//初始化载入信息到内存
void DeviceInfoClass::init()
{
	loadServerAddr();
	loadDeviceID();
	loadDeviceCode();
	loadServerPort();
	loadLabID();
}

/*设备信息写入EEPROM储存器中*/

void DeviceInfoClass::setServerAddr(String ipaddr)
{
	unsigned long ip=0;
	byte bytecode;
	String part[4];
	int n = 0;
	int lenth = ipaddr.length();
	for (int i = 0; i < 4; i++)
	{
		part[i] = "";
	}
	for (int i = 0; i < lenth; i++)
	{
		if (ipaddr[i] != '.')
			part[n] += ipaddr[i];
		else
			n++;
	}
	for (int i = 0; i < 4; i++)//写入EEPROM
	{
		bytecode = part[i].toInt();
		EEPROM.write(SERVER_ADDR+i,bytecode);
	}
}

void DeviceInfoClass::setDeviceCode(char * code)
{
	int n;
	n = 0;
	while (code[n])
	{
		EEPROM.write(DEVICE_CODE + n, code[n]);
		n++;
	}
	EEPROM.write(DEVICE_CODE + n, 0x00);
}

void DeviceInfoClass::setDeviceID(int id)
{
	EEPROM.write(DEVICE_ID_HIGH, id / 256);
	EEPROM.write(DEVICE_ID_LOW , id % 256);
}

void DeviceInfoClass::setServerPort(int port)
{
	EEPROM.write(SERVER_PORT_HIGH, port / 256);
	EEPROM.write(SERVER_PORT_LOW, port % 256);
}

void DeviceInfoClass::setLabID(int id)
{
	EEPROM.write(LAB_ID, id / 256);
	EEPROM.write(LAB_ID + 1, id % 256);
}


/*加载EEPROM中信息到对象*/

void DeviceInfoClass::loadServerAddr()
{
	String part[4];
	for (int i = 0; i < 4; i++)
	{
		part[i] = EEPROM.read(SERVER_ADDR + i);
	}
	m_ServerAddr = part[0] + "." + part[1] + "." + part[2] + "." + part[3];
}

void DeviceInfoClass::loadDeviceID()
{
	int low;
	int high;
	high = EEPROM.read(DEVICE_ID_HIGH);
	low  = EEPROM.read(DEVICE_ID_LOW);
	m_DeviceID = high * 256 + low;
}

void DeviceInfoClass::loadDeviceCode()
{
	int n = 0;
	char bytecode;
	m_DeviceCode = "";
	do
	{
		bytecode = EEPROM.read(DEVICE_CODE + n);
		if(bytecode!=0x00)
			m_DeviceCode += bytecode;
		n++;
	} while (bytecode);
}

void DeviceInfoClass::loadServerPort()
{
	int low;
	int high;
	high = EEPROM.read(SERVER_PORT_HIGH);
	low = EEPROM.read(SERVER_PORT_LOW);
	m_ServerPort = high * 256 + low;
}

void DeviceInfoClass::loadLabID()
{
	int low;
	int high;
	high = EEPROM.read(LAB_ID);
	low = EEPROM.read(LAB_ID + 1);
	m_LabID = high * 256 + low;
}
//获取设备信息
String DeviceInfoClass::getServerAddr()
{
	return m_ServerAddr;
}

int DeviceInfoClass::getDeviceID()
{
	return m_DeviceID;
}

String DeviceInfoClass::getDeviceCode()
{
	return m_DeviceCode;
}

int DeviceInfoClass::getServerPort()
{
	return m_ServerPort;
}

int DeviceInfoClass::getLabID()
{
	return m_LabID;
}

String DeviceInfoClass::INTtoSTR(long data)
{
	String part[4];
	String ip;
	for (int i = 3; i >=0; i--)
	{
		part[i] = data & 0x000000ff;
		data = data >> 8;
	}
	ip = part[0] + '.' + part[1] + '.' + part[2] + '.' + part[3];
	Serial.println(ip.begin());
	return ip;
}
