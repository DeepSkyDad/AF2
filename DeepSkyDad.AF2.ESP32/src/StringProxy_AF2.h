#include "EEPROM_AF2.h"
#include "Motor_AF2.h"
#include "Peripherals_AF2.h"
#include "Wifi_AF2.h"
#include "Test_AF2.h"
#include "General_AF2.h"

#pragma once
class StringProxy_AF2
{
	private:
                EEPROM_AF2* _eeprom;
                Motor_AF2* _motor;
                Peripherals_AF2* _peri;
                Wifi_AF2* _wifi;
                Test_AF2* _test;
                char* _uintToChar(unsigned int value);
                char* _floatToChar(float value);
                bool _commandEndsWith(char c, char commandParam[], int commandParamLength);
	public:
		void init(EEPROM_AF2 &eeprom, Motor_AF2 &motor, Peripherals_AF2 &peri, Wifi_AF2 &wifi, Test_AF2 &test);
                char const* processCommand(char command[], char commandParam[], int commandParamLength);
};