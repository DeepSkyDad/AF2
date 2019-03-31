#include <OneWire.h>
#include <DallasTemperature.h>

#include "EEPROM.h"
#include "Motor_AF2.h"

#pragma once
#define PIN_JACK_1 32
#define PIN_JACK_2 33

#define PIN_VOLTAGE 35
#define VOLTAGE_DIVISOR 100.0

// BTNUP
#define HC_BTNUP_VAL 1680
#define HC_BTNUP_MIN 1450
#define HC_BTNUP_MAX 1850
// BTNDOWN
#define HC_BTNDOWN_VAL 2150
#define HC_BTNDOWN_MIN 1950
#define HC_BTNDOWN_MAX 2550
// BTNBOTH
#define HC_BTNBOTH_VAL 1370
#define HC_BTNBOTH_MIN 1130
#define HC_BTNBOTH_MAX 1420
// CONNECTED
#define HC_CONNECTED_VAL 3000
#define HC_CONNECTED_MIN 1000
#define HC_CONNECTED_MAX 3500

#define HC_BTN_UP 1
#define HC_BTN_DOWN 2
#define HC_BTN_BOTH 3

#define HC_CONTINUOUS_MOVE_TIMEOUT_MS 500

class Peripherals_AF2
{
	private:
        EEPROM_AF2* _eeprom;
        Motor_AF2* _motor;
        OneWire _ds1 = OneWire(PIN_JACK_1);
        OneWire _ds2 = OneWire(PIN_JACK_2);
        DallasTemperature _sensors1 = DallasTemperature(&_ds1);
        DallasTemperature _sensors2 = DallasTemperature(&_ds2);
    	float _temperatureCelsius = -127;
        float _temperatureFahrenheit = -127;
        int _tsPin = -1; //temp sensor
        int _hcPin = -1; // hand controller
        int _readHcButton();
	public:
		void init(EEPROM_AF2 &eeprom, Motor_AF2 &motor);
        void autoDiscovery();
        void handleHC();
        void handleTS();
        bool isHcConnected();
        bool isTsConnected();
        float getTempC();
        float getTempF();
        int readHcPin(int hcPin);
        float getTempCByPin(int pin);
        float getVoltage();
};