#include <Arduino.h>

#include "EEPROM_AF2.h"
#include "Motor_AF2.h"
#include "Peripherals_AF2.h"
#include "StringProxy_AF2.h"
#include "Serial_AF2.h"
#include "Wifi_AF2.h"

#define LED_PIN 5

EEPROM_AF2 _eeprom;
Motor_AF2 _motor;
Peripherals_AF2 _peri;
StringProxy_AF2 _stringProxy;
Serial_AF2 _serial;
Wifi_AF2 _wifi;
Test_AF2 _test;

void loop()
{
	delay(1000);
	// empty - we want to keep core 1 free for motor task
}

void loopMotor(void *parameter)
{
	while (true)
	{
		_motor.handleMove();

		delay(100);
	}
}

void loopMain(void *parameter)
{
	while (true)
	{
		_serial.serialEvent();
		_wifi.webServerEvent();
		_eeprom.handleEepromWrite();

		_peri.autoDiscovery();
		_peri.handleHC();
		_peri.handleTS();

		delay(1);
	}
}

void setup()
{
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	_eeprom.init();
	_motor.init(_eeprom);
	_peri.init(_eeprom, _motor);
	_stringProxy.init(_eeprom, _motor, _peri, _wifi, _test);
	_serial.init(_stringProxy);
	_wifi.init(_eeprom, _motor, _peri);

	//run motor turning in core 1 at high priority and everything else on core 0
	xTaskCreatePinnedToCore(
		loopMotor,   /* Task function. */
		"loopMotor", /* name of task. */
		10000,		 /* Stack size of task */
		NULL,		 /* parameter of the task */
		1,			 /* priority of the task */
		NULL,		 /* Task handle to keep track of created task */
		1);			 /* pin task to core 1 */

	xTaskCreatePinnedToCore(
		loopMain,   /* Task function. */
		"loopMain", /* name of task. */
		10000,		/* Stack size of task */
		NULL,		/* parameter of the task */
		1,			/* priority of the task */
		NULL,		/* Task handle to keep track of created task */
		0);			/* pin task to core 0 */
}