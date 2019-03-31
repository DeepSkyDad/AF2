#include <Arduino.h>
#include "Peripherals_AF2.h"

void Peripherals_AF2::init(EEPROM_AF2 &eeprom, Motor_AF2 &motor)
{
	_eeprom = &eeprom;
	_motor = &motor;

	pinMode(PIN_JACK_1, INPUT);
	pinMode(PIN_JACK_2, INPUT);
	pinMode(PIN_VOLTAGE, INPUT);

	//start temperature sensor
	_sensors1.begin();
	_sensors2.begin();
}

int Peripherals_AF2::readHcPin(int hcPin) {
	//smooth out annomalies
	int x=0, i=0, xTmp;
	while (++i < 10) {
		xTmp = analogRead(hcPin);
		if(xTmp<HC_CONNECTED_MIN)
			continue;
		x+=xTmp;
		delayMicroseconds(5);
	}

	return x / 9;
}

int Peripherals_AF2::_readHcButton()
{
	int x;
	if (isHcConnected())
	{
		x = readHcPin(_hcPin);
			
		//Serial.println(x);
		if (x < HC_BTNUP_MAX && x > HC_BTNUP_MIN)
		{ // + button pressed
			return HC_BTN_UP;
		}
		else if (x < HC_BTNDOWN_MAX && x > HC_BTNDOWN_MIN)
		{ // - button pressed
			return HC_BTN_DOWN;
		}
		else if (x < HC_BTNBOTH_MAX && x > HC_BTNBOTH_MIN)
		{ // - button pressed
			return HC_BTN_BOTH;
		}
		else if (x > HC_CONNECTED_MAX || x < HC_CONNECTED_MIN)
		{ // HC disconnected
			//Serial.println("HC disconnected!");
			_hcPin = -1;
			return -1;
		}
		else
		{ // all buttons released
			return 0;
		}
	}
	return -1;
}

void Peripherals_AF2::autoDiscovery()
{
	static unsigned long lastAutoDiscovery = 0;
	int x;

	if (millis() - lastAutoDiscovery > 3000 || lastAutoDiscovery == 0)
	{
		lastAutoDiscovery = millis();

		// JACK 1
		if (PIN_JACK_1 != _hcPin && PIN_JACK_1 != _tsPin)
		{
			// if currently no HC connected, first check if HC is connected here
			if (!isHcConnected())
			{
				x = readHcPin(PIN_JACK_1);
				if (x < HC_CONNECTED_MAX && x > HC_CONNECTED_MIN)
				{
					_hcPin = PIN_JACK_1;
					//Serial.println("HC detected on JACK1!");
				}
			}

			// we might have found HC, so recheck - if not found, continue with tempC sensor discovery if we don't have it already
			if (PIN_JACK_1 != _hcPin && !isTsConnected())
			{
				_sensors1.requestTemperatures();
				float tempC = _sensors1.getTempCByIndex(0);
				//Serial.print("TEMP PIN 1: ");
				//Serial.println(tempC);
				if (tempC != -127)
				{
					_temperatureCelsius = tempC;
					_tsPin = PIN_JACK_1;
				}
			}
		}

		// JACK 2
		if (PIN_JACK_2 != _hcPin && PIN_JACK_2 != _tsPin)
		{
			// if currently no HC connected, first check if HC is connected here
			if (!isHcConnected())
			{
				x = readHcPin(PIN_JACK_2);
				if (x < HC_CONNECTED_MAX && x > HC_CONNECTED_MIN)
				{
					_hcPin = PIN_JACK_2;
					//Serial.println("HC detected on JACK2!");
				}
			}

			// we might have found HC, so recheck - if not found, continue with tempC sensor discovery if we don't have it already
			if (PIN_JACK_2 != _hcPin && !isTsConnected())
			{
				_sensors2.requestTemperatures();
				float tempC = _sensors2.getTempCByIndex(0);
				//Serial.print("TEMP PIN 2: ");
				//Serial.println(tempC);
				if (tempC != -127)
				{
					_temperatureCelsius = tempC;
					_tsPin = PIN_JACK_2;
				}
			}
		}
	}
}

void Peripherals_AF2::handleHC()
{
	static unsigned long btnUpPressed = 0;
	static unsigned long btnDownPressed = 0;
	static unsigned long lastRun = 0;
	static bool stepSizeChanged = false;
	static bool moveCanceled = false;

	if (isHcConnected() && _motor->getMovementStatus() != MOVEMENT_STATUS::MOVING)
	{
		if (millis() - lastRun < 10) // don't check every loop iteration - debouncing
			return;

		lastRun = millis();

		int btn_val = _readHcButton();

		if (btn_val <= 0)
		{
			//buttons released
			if (_motor->getMovementStatus() == MOVEMENT_STATUS::MOVING_MANUAL_CONTINUOUS)
			{
				_motor->stop();
			}
			else if (!moveCanceled && btnUpPressed != 0 && lastRun - btnUpPressed <= HC_CONTINUOUS_MOVE_TIMEOUT_MS)
			{
				_motor->moveManual(MOVEMENT_MANUAL_DIR::CW);
			}
			else if (!moveCanceled && btnDownPressed != 0 && lastRun - btnDownPressed <= HC_CONTINUOUS_MOVE_TIMEOUT_MS)
			{
				_motor->moveManual(MOVEMENT_MANUAL_DIR::CCW);
			}

			stepSizeChanged = false;
			moveCanceled = false;
			btnUpPressed = 0;
			btnDownPressed = 0;
		}
		else if (!stepSizeChanged)
		{
			if (btn_val == HC_BTN_BOTH)
			{
				_motor->stop();

				btnUpPressed = 0;
				btnDownPressed = 0;
				stepSizeChanged = true;
				_eeprom->setManualStepSize(_eeprom->getManualStepSize() == 1 ? 2 : 1);
			}
			else if (btn_val == HC_BTN_UP)
			{
				//button up
				if (_motor->getMovementStatus() == MOVEMENT_STATUS::MOVING_MANUAL)
				{
					_motor->stop();
					moveCanceled = true;
				}
				else if (btnUpPressed == 0)
				{
					btnUpPressed = millis();
				}
				else if (_motor->getMovementStatus() != MOVEMENT_STATUS::MOVING_MANUAL_CONTINUOUS && (lastRun - btnUpPressed) > HC_CONTINUOUS_MOVE_TIMEOUT_MS)
				{
					_motor->moveManualContinuous(MOVEMENT_MANUAL_DIR::CW);
				}
			}
			else if (btn_val == HC_BTN_DOWN)
			{
				//button down
				if (_motor->getMovementStatus() == MOVEMENT_STATUS::MOVING_MANUAL)
				{
					_motor->stop();
					moveCanceled = true;
				}
				else if (btnDownPressed == 0)
				{
					_motor->stop();
					btnDownPressed = millis();
				}
				else if (_motor->getMovementStatus() != MOVEMENT_STATUS::MOVING_MANUAL_CONTINUOUS && (lastRun - btnDownPressed) > HC_CONTINUOUS_MOVE_TIMEOUT_MS)
				{
					_motor->moveManualContinuous(MOVEMENT_MANUAL_DIR::CCW);
				}
			}
		}
	}
}

void Peripherals_AF2::handleTS()
{
	static unsigned long lastRun = 0;
	static float tempC;
	static float tempF;

	if (isTsConnected())
	{
		if (millis() - lastRun < 5000)
			return;

		lastRun = millis();
		if (_tsPin == PIN_JACK_1)
		{
			_sensors1.requestTemperatures();
			tempC = _sensors1.getTempCByIndex(0);
			tempF = _sensors1.getTempFByIndex(0);
			//Serial.print("TEMP PIN 1: ");
			//Serial.println(tempC);
		}
		else if (_tsPin == PIN_JACK_2)
		{
			_sensors2.requestTemperatures();
			tempC = _sensors2.getTempCByIndex(0);
			tempF = _sensors2.getTempFByIndex(0);
			//Serial.print("TEMP PIN 2: ");
			//Serial.println(tempC);
		}

		if (tempC != -127 && tempC < 60 && tempC > -60)
		{
			_temperatureCelsius = tempC;
			_temperatureFahrenheit = tempF;
		}
		else
		{
			_tsPin = -1;
			_temperatureCelsius = -127;
			_temperatureFahrenheit = -127;
		}
	}
}

bool Peripherals_AF2::isHcConnected()
{
	return _hcPin != -1;
}

bool Peripherals_AF2::isTsConnected()
{
	return _tsPin != -1;
}

float Peripherals_AF2::getTempC()
{
	return _temperatureCelsius;
}

float Peripherals_AF2::getTempF()
{
	return _temperatureFahrenheit;
}

float Peripherals_AF2::getTempCByPin(int pin) 
{
	if (pin == PIN_JACK_1)
	{
		_sensors1.requestTemperatures();
		return _sensors1.getTempCByIndex(0);
	}
	else if (pin == PIN_JACK_2)
	{
		_sensors2.requestTemperatures();
		return _sensors2.getTempCByIndex(0);
	}

	return -130.0;
}

float Peripherals_AF2::getVoltage() {
    return analogRead(PIN_VOLTAGE) / VOLTAGE_DIVISOR;
}