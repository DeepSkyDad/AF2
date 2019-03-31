#include <Arduino.h>
#include "Serial_AF2.h"

void Serial_AF2::init(StringProxy_AF2 &stringProxy)
{
    _stringProxy = &stringProxy;

    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    //Serial.setDebugOutput(0); // TODO enable this for production
}

void Serial_AF2::serialEvent()
{
    while (Serial.available())
    {
        char c = Serial.read();

        if (c == '[')
        {
            _serialCommandRawIdx = 0;
            memset(_serialCommandRaw, 0, 70);
        }
        else if (c == ']')
        {
            _serialCommandRawLength = strlen(_serialCommandRaw);
            _commandParamLength = 0;
            memset(_command, 0, 5);
            memset(_commandParam, 0, 65);

            if (_serialCommandRawLength >= 4)
            {
                strncpy(_command, _serialCommandRaw, 4);
            }
            if (_serialCommandRawLength > 4)
            {
                _commandParamLength = _serialCommandRawLength - 4;
                strncpy(_commandParam, _serialCommandRaw + 4, _commandParamLength);
            }

            Serial.print("(");
            Serial.print(_stringProxy->processCommand(_command, _commandParam, _commandParamLength));
            Serial.print(")");
        }
        else
        {
            _serialCommandRaw[_serialCommandRawIdx] = c;
            _serialCommandRawIdx++;
        }
    }
}

bool Serial_AF2::commandEndsWith(char character) {
    return _commandParam[_commandParamLength - 1] == character;
}