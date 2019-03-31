#include <Arduino.h>
#include "Test_AF2.h"

#define ASK_YN if (!askYN()) fail++;
#define P(a) Serial.print(a)
#define PLN(a) Serial.println(a)
#define CHECK_PORT(a,b,c,d,e,f) if(!checkPort(a,b,c,d,e,f)) fail++;
#define CHECK_TEMP(a,b,c,d) if(!checkTemp(a,b,c,d)) fail++;
#define CHECK_BOARD_TEMP(a,b) if(!checkBoardTemp(a,b)) fail++;
#define CHECK_VOLTAGE(a,b,c) if(!checkVoltage(a,b,c)) fail++;

#define HC_MAX_DEV 10.0 // allow 10% deviation in HC readings

bool askYN();
bool checkPort(Peripherals_AF2 &_peri, int pin, int min, int max, int expected, float max_dev_percent);
bool checkTemp(Peripherals_AF2 &_peri, int pin, float min, float max);
bool checkBoardTemp(float min, float max);
bool checkVoltage(Peripherals_AF2 &_peri, float min, float max);

int Test_AF2::execute(EEPROM_AF2 &_eeprom, Motor_AF2 &_motor, Peripherals_AF2 &_peri, Wifi_AF2 &_wifi) {
    uint motorPos, wifiCnt = 0;
    int fail = 0;
    
    // basic info
    PLN();
    PLN("Board: " AF2_BOARD);
    PLN("FW version: " AF2_FW_VERSION);
    P("Device Id: "); PLN(AF2::getDeviceId());
    P("Board temperature: "); P(AF2::getBoardTempC()); PLN(" C");
    P("Voltage: "); P(_peri.getVoltage()); PLN(" V");
    
    // reset to defaults
    P("Reseting settings to defaults. Proceed?");
    if (!askYN()) {
        PLN("Test SKIPPED!");
        return 0;
    }
    
    _eeprom.resetToDefaults();
    _motor.resetToDefaults();
    _wifi.resetToDefaults();
    
    // print eeprom settings
    _eeprom.debug();

    // motor testing
    PLN("--- MOTOR TEST");
    motorPos = _eeprom.getPosition();
    P("Moving motor CW... ");
    _eeprom.setTargetPosition(motorPos-400);
    _motor.move();
    delay(500);
    while (_motor.isMoving())
        delay(100);
    PLN("DONE");

    P("Moving motor CCW... ");
    _eeprom.setTargetPosition(motorPos);
    _motor.move();
    delay(500);
    while (_motor.isMoving())
        delay(100);
    PLN("DONE");
    P("Did motor return to original position?"); ASK_YN;
    
    // aux port testing
    PLN("--- AUX PORT TEST");
    P("Checking PORT1: "); CHECK_PORT(_peri, PIN_JACK_1, 0, 4095, 4095, 0.1);
    P("Checking PORT2: "); CHECK_PORT(_peri, PIN_JACK_2, 0, 4095, 4095, 0.1);
    PLN("- PORT1 HC");
    P("Connect HC to PORT1: "); CHECK_PORT(_peri, PIN_JACK_1, HC_CONNECTED_MIN, HC_CONNECTED_MAX, HC_CONNECTED_VAL, HC_MAX_DEV);
    P("Press and hold + on HC on PORT1: "); CHECK_PORT(_peri, PIN_JACK_1, HC_BTNUP_MIN, HC_BTNUP_MAX, HC_BTNUP_VAL, HC_MAX_DEV);
    P("Press and hold - on HC on PORT1: "); CHECK_PORT(_peri, PIN_JACK_1, HC_BTNDOWN_MIN, HC_BTNDOWN_MAX, HC_BTNDOWN_VAL, HC_MAX_DEV);
    P("Press and hold BOTH BUTTONS on HC on PORT1: "); CHECK_PORT(_peri, PIN_JACK_1, HC_BTNBOTH_MIN, HC_BTNBOTH_MAX, HC_BTNBOTH_VAL, HC_MAX_DEV);
    PLN("- PORT2 HC");
    P("Connect HC to PORT2: "); CHECK_PORT(_peri, PIN_JACK_2, HC_CONNECTED_MIN, HC_CONNECTED_MAX, HC_CONNECTED_VAL, HC_MAX_DEV);
    P("Press and hold + on HC on PORT2: "); CHECK_PORT(_peri, PIN_JACK_2, HC_BTNUP_MIN, HC_BTNUP_MAX, HC_BTNUP_VAL, HC_MAX_DEV);
    P("Press and hold - on HC on PORT2: "); CHECK_PORT(_peri, PIN_JACK_2, HC_BTNDOWN_MIN, HC_BTNDOWN_MAX, HC_BTNDOWN_VAL, HC_MAX_DEV);
    P("Press and hold BOTH BUTTONS on HC on PORT2: "); CHECK_PORT(_peri, PIN_JACK_2, HC_BTNBOTH_MIN, HC_BTNBOTH_MAX, HC_BTNBOTH_VAL, HC_MAX_DEV);
    PLN("- PORT1 TP");
    P("Connect TP to PORT1: ");CHECK_TEMP(_peri, PIN_JACK_1, 15.0, 35.0);
    PLN("- PORT2 TP");
    P("Connect TP to PORT2: ");CHECK_TEMP(_peri, PIN_JACK_2, 15.0, 35.0);

    // wifi testing
    PLN("--- WIFI TEST");
    P("Connect to WiFi: '"); P(_wifi.getSsid()); P("', pass: '"); P(_eeprom.getWifiPassword()); PLN("' and play with user interface. Press any key to stop the test...");
    while (Serial.available() == 0) {
        if (_wifi.webServerEvent())
            wifiCnt++;
        delay(1);
    }
    Serial.read();
    P("Got "); P(wifiCnt); P(" events. ");
    if (wifiCnt == 0) {
        PLN(" No interaction detected - FAIL");
        fail++;
    }
    else {
        P("Everything OK with WiFi?"); ASK_YN;
    }

    // board temp check
    P("Checking board temp: "); CHECK_BOARD_TEMP(20.0, 80.0);

    // voltage check
    P("Checking voltage: "); CHECK_VOLTAGE(_peri, 11.0, 13.0);

    // reset setting again before ending
    P("Reseting settings to defaults... ");
    _eeprom.resetToDefaults();
    _motor.resetToDefaults();
    _wifi.resetToDefaults();
    PLN("DONE");
    
    if (fail > 0) {
        P("Test FAILED, with ");P(fail);PLN(" failures!");
        return 0;
    }

    PLN("Test SUCESSFULY COMPLETED!");
    return 1;
}

bool askYN() {
    P(" [y/n] ");

    while (Serial.available() == 0)
        delay(1);
    
    char res = Serial.read();

    if (res == 'y') {
        PLN("- OK");
        return true;
    }

    PLN("- FAIL");
    return false;
}

bool checkPort(Peripherals_AF2 &_peri, int pin, int min, int max, int expected, float max_dev_percent) {
    int val = -1;

    for (int i = 0; i < 10; i++) {
        val = _peri.readHcPin(pin);
        if (val >= min && val <= max)
            break;
        delay(1000);
    }

    P("min: ");P(min);P(", max: ");P(max);P(", expected: ");P(expected);P(", max dev: ");P(max_dev_percent);P("% - ");

    if (!(val >= min && val <= max))
    {
        P("didn't get correct reading in 10 seconds, last value: "); P(val); PLN(" - FAIL");
        return false;
    }

    float dev_percent = ((val-expected)/(float)(expected))*100;

    P("val: ");P(val);P(", dev: ");P(dev_percent);P("% - ");

    if (dev_percent >= max_dev_percent) {
        PLN("FAIL");
        return false;
    }

    PLN("OK");
    return true;
}

bool checkTemp(Peripherals_AF2 &_peri, int pin, float min, float max) {
    float val = -127.0;

    for (int i = 0; i < 10; i++) {
        val = _peri.getTempCByPin(pin);
        if (val >= min && val <= max)
            break;
        delay(1000);
    }

    P("min: ");P(min);P(", max: ");P(max);P(" - ");

    if (!(val >= min && val <= max))
    {
        P("didn't get correct reading in 10 seconds, last value: "); P(val); PLN(" - FAIL");
        return false;
    }

    P("val: ");P(val);PLN("OK");
    return true;
}

bool checkVoltage(Peripherals_AF2 &_peri, float min, float max) {
    float val = _peri.getVoltage();

    P("min: ");P(min);P(", max: ");P(max);P(" - ");

    if (!(val >= min && val <= max))
    {
        P("reading out of bounds, val: "); P(val); PLN(" - FAIL");
        return false;
    }

    P("val: ");P(val);PLN(" - OK");
    return true;
}

bool checkBoardTemp(float min, float max) {
    float val = AF2::getBoardTempC();

    P("min: ");P(min);P(", max: ");P(max);P(" - ");

    if (!(val >= min && val <= max))
    {
        P("reading out of bounds, val: "); P(val); PLN(" - FAIL");
        return false;
    }

    P("val: ");P(val);PLN(" - OK");
    return true;
}