#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
//#include <ESPmDNS.h>
#include <ArduinoJson.h>

#include "EEPROM_AF2.h"
#include "Motor_AF2.h"
#include "Peripherals_AF2.h"

#pragma once
class Wifi_AF2
{
	private:
		EEPROM_AF2* _eeprom;
		Motor_AF2* _motor;
		Peripherals_AF2* _peri;

		//const char *_mdns = "AF2";
		const char *_ssidTpl = "DSD-AF2_%s";
		StaticJsonBuffer<400> _jsonBuffer;
		WiFiServer _server = WiFiServer(80);

		IPAddress _localIp = IPAddress(192, 168, 1, 1);
		IPAddress _gateway = IPAddress(0, 0, 0, 0);
		IPAddress _subnet = IPAddress(255, 255, 255, 0);

		WiFiClient _client;
		bool isGzip;
		char _ssid[20];
		char _url[1024];
		char _currentLine[1024];
		int _currentLineIdx = 0;
		bool _strEndsWith(const char* str, const char* suffix);
		void _writeResponse();
	public:
		void init(EEPROM_AF2 &_eeprom, Motor_AF2 &motor, Peripherals_AF2 &peri);
		bool webServerEvent();
		void setWifiMode(unsigned short mode);
		void setWifiPassword(char* password);
		void resetToDefaults();
		const char* getSsid();
};