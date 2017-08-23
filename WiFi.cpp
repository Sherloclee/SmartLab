// 
// 
// 

#include "WiFi.h"
#include "functions.h"
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <stdio.h>

#define _SERVERADDR_STORE 8	//服务器IP地址存放位置
#define _DEVICE_ID 12		//设备ID
#define _DEVICE_CODE 16		//设备代号
#define _DEVICE_NAME 20		//设备名称
#define _DEVICE_LAB 40		//实验室编号

union ipdata
{
	long data;
	byte b[4];
};
//初始化Wi-Fi参数设置
int WiFiClass::init(String server, int port)
{
	int n=0;
	setServer(server);
	setPort(port);
	while (!connectWiFi())
	{
		n++;
		Serial.println("connectingWiFi");
		if (n == 10)
			return 0;
	};
	while (!connectSocket(server, port)) 
	{
		Serial.println("connectingSocket");
	};
	Serial.println("Connected");
}
//停止socket
void WiFiClass::stop()
{
	print("AT+CLOSE\r\n");
}
//连接到路由器
int WiFiClass::connectWiFi()
{
	String _message;
	Serial.write("connect WIFI\n");
	write("AT+RST\r\n");
	for(int i=0;i<7;i++)
		delay(1000);
	_message = "";
	while (available())
	{
		read();
	}
	write("AT+CIFSR=?\r\n");
	delay(5);
	while (available())
	{
		_message = readString();
		delay(1);
	}
	String str = "";
	for (int i = 0; i < _message.length(); i++)
	{
		if (_message[i] == '\n')
		{
			i++;
			i++;
			i++;
			str += _message[i];
			i++;
			str += _message[i];
			break;
		}
	}

	Serial.println(str.length());
	Serial.println(str);
	/*for (int i = 0; i < 5; i++)
		delay(1000);
	_message = "";
	while (available())
	{
		delay(8);
		_message = _message + char(read());
		delay(2);
	}*/
	//Serial.println(_message.begin());
	if (str == "OK")
	{
		Serial.println("Connected");
		return 1;
	}
	return 0;
}

int WiFiClass::connectWiFi(String SSID, String PW)
{
	String ATCode;
	ATCode = "AT+CWJAP=\"";
	ATCode += SSID;
	ATCode += "\",\"";
	ATCode += PW;
	ATCode += "\"\r\n";
	Serial.println(ATCode);
	println(ATCode.begin());
	delay(5);
	while (available())
	{
		Serial.print(read());
		delay(2);
	}
	return 1;
}
//连接到服务器
int WiFiClass::connectSocket(String server,int port)
{
	String messages;
	String WiFiMessage; 
	messages = "AT+CIPSTART=\"TCP\",\"";
	messages = messages + m_Server;
	messages = messages + "\",";
	messages = messages + m_port; 
	messages = messages + "\r\n";
	print(messages);
	delay(1000);
	while (available())
	{
		WiFiMessage = "";
		while (available())
		{
			
			WiFiMessage = String(readStringUntil('\n'));
			delay(2);
		}
	}
	flush();
	Serial.println(WiFiMessage.begin());
	if(WiFiMessage == "OK\r")
		return 1;
	return 1;
}
//set ServerIP
void WiFiClass::setServer(String server)
{
	m_Server = server;
	return ;
}
//set ServerPort
void WiFiClass::setPort(int port)
{
	String str;
	str = port;
	m_port = str;
	delay(100);
	return ;
}
//发送数据到服务器
String WiFiClass::Send(String Message)
{
	String lenth;
	String _message;
	lenth = Message.length()+1;
	_message = lenth;
	_message = "AT+CIPSEND=" + lenth;
	_message = _message + "\r\n";
	Serial.println(_message);
	print(_message);
	delay(1000);
	if (available())
	{
		while (available())
		{
			read();
			delay(2);
		}
	}
	print(Message+'\n');
	print("\r");
	Serial.println("SendOK");
	while(available())
		read();
	return String();
}
//接受服务器数据
String WiFiClass::Recv()
{
	String WiFiMessage;
	WiFiMessage = "";
	while (available())
	{
		WiFiMessage = WiFiMessage + char(read());
		delay(1);
	}
	flush();
	WiFiMessage = Transform::Prosess(WiFiMessage);
	return WiFiMessage;
}
//判断Wi-Fi串口是否有数据
int WiFiClass::is_available()
{
	return available();
}
