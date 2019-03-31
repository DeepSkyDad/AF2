#include <Arduino.h>
#include "StringProxy_AF2.h"

void StringProxy_AF2::init(EEPROM_AF2 &eeprom, Motor_AF2 &motor, Peripherals_AF2 &peri, Wifi_AF2 &wifi, Test_AF2 &test)
{
    _eeprom = &eeprom;
    _motor = &motor;
    _peri = &peri;
    _wifi = &wifi;
    _test = &test;
}

char *StringProxy_AF2::_uintToChar(unsigned int value)
{
    char *buffer = new char[50];
    sprintf(buffer, "%d", value);
    return buffer;
}

char *StringProxy_AF2::_floatToChar(float value)
{
    char *buffer = new char[50];
    sprintf(buffer, "%.2f", value);
    return buffer;
}

bool StringProxy_AF2::_commandEndsWith(char c, char commandParam[], int commandParamLength)
{
    return commandParam[commandParamLength - 1] == c;
}

char const *StringProxy_AF2::processCommand(char command[], char commandParam[], int commandParamLength)
{
    if (strcmp("GFRL", command) == 0)
    {
        return "Board=" AF2_BOARD ", Version=" AF2_FW_VERSION;
    }
    else if (strcmp("GFRS", command) == 0)
    {
        return "(" AF2_FW_VERSION ")";
    }
    else if (strcmp("GPOS", command) == 0)
    {
        return _uintToChar(_eeprom->getPosition());
    }
    else if (strcmp("GTRG", command) == 0)
    {
        return _uintToChar(_eeprom->getTargetPosition());
    }
    else if (strcmp("STRG", command) == 0)
    {
        if (_eeprom->setTargetPosition((unsigned int)atoi(commandParam)))
            return "OK";
        else
            return "!101";
    }
    else if (strcmp("GMOV", command) == 0)
    {
        return _motor->isMoving() ? "1" : "0";
    }
    else if (strcmp("SMOV", command) == 0)
    {
        _motor->move();
        return "OK";
    }
    else if (strcmp("STOP", command) == 0)
    {
        _motor->stop();
        return "OK";
    }
    else if (strcmp("GMXP", command) == 0)
    {
        return _uintToChar(_eeprom->getMaxPosition());
    }
    else if (strcmp("SMXP", command) == 0)
    {
        _eeprom->setMaxPosition((unsigned int)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("GMXM", command) == 0)
    {
        return _uintToChar(_eeprom->getMaxMovement());
    }
    else if (strcmp("SMXM", command) == 0)
    {
        _eeprom->setMaxMovement((unsigned int)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("GSTP", command) == 0)
    {
        return _uintToChar(_eeprom->getStepMode());
    }
    else if (strcmp("GSPD", command) == 0)
    {
        return _uintToChar(_eeprom->getSpeedMode());
    }
    else if (strcmp("SSTP", command) == 0)
    {
        _eeprom->setStepMode((unsigned short)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("SSPD", command) == 0)
    {
        _eeprom->setSpeedMode((unsigned short)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("RSET", command) == 0)
    {
        _eeprom->resetToDefaults();
        _motor->resetToDefaults();
        _wifi->resetToDefaults();

        return "OK";
    }
    else if (strcmp("RBOT", command) == 0)
    {
        ESP.restart();
    }
    else if (strcmp("GCLM", command) == 0)
    {
        return _uintToChar(_eeprom->getCoilsMode());
    }
    else if (strcmp("SCLM", command) == 0)
    {
        _motor->setCoilsMode((unsigned short)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("GBUF", command) == 0)
    {
        return _uintToChar(_eeprom->getSettleBufferMs());
    }
    else if (strcmp("SBUF", command) == 0)
    {
        _eeprom->setSettleBufferMs((unsigned int)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("GREV", command) == 0)
    {
        return _eeprom->getReverseDirection() ? "1" : "0";
    }
    else if (strcmp("SREV", command) == 0)
    {
        _eeprom->setReverseDirection(atoi(commandParam) == 1 ? true : false);
        return "OK";
    }
    else if (strcmp("SPOS", command) == 0)
    {
        _eeprom->syncPosition((unsigned int)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("GIDC", command) == 0)
    {
        return _uintToChar(_eeprom->getCoilsIdleTimeoutMs());
    }
    else if (strcmp("SIDC", command) == 0)
    {
        _eeprom->setCoilsIdleTimeoutMs((unsigned int)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("GIDE", command) == 0)
    {
        return _uintToChar(_eeprom->getEepromWriteTimeoutMs());
    }
    else if (strcmp("SIDE", command) == 0)
    {
        _eeprom->setEepromWriteTimeoutMs((unsigned int)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("GCMV", command) == 0)
    {
        if (_commandEndsWith('%', commandParam, commandParamLength))
        {
            char *buffer = new char[4];
            sprintf(buffer, "%d%%", _motor->getMoveCurrentPercent());
            return buffer;
        }
        else
        {
            return _uintToChar(_eeprom->getCoilsCurrentMove());
        }
    }
    else if (strcmp("SCMV", command) == 0)
    {
        if (_commandEndsWith('%', commandParam, commandParamLength))
        {
            int length = strlen(commandParam) - 1;
            char percentValue[length];
            strncpy(percentValue, commandParam, length);
            _motor->setMoveCurrentPercent(atof(percentValue));
        }
        else
        {
            _eeprom->setCoilsCurrentMove((unsigned short)atoi(commandParam));
        }

        return "OK";
    }
    else if (strcmp("GCHD", command) == 0)
    {
        if (_commandEndsWith('%', commandParam, commandParamLength))
        {
            char *buffer = new char[4];
            sprintf(buffer, "%d%%", _motor->getHoldCurrentPercent());
            return buffer;
        }
        else
        {
            return _uintToChar(_eeprom->getCoilsCurrentHold());
        }
    }
    else if (strcmp("SCHD", command) == 0)
    {
        if (_commandEndsWith('%', commandParam, commandParamLength))
        {
            int length = strlen(commandParam) - 1;
            char percentValue[length];
            strncpy(percentValue, commandParam, length);
            _motor->setHoldCurrentPercent(atof(percentValue));
        }
        else
        {
            _motor->setHoldCurrent((unsigned short)atoi(commandParam));
        }

        return "OK";
    }
    else if (strcmp("GTMC", command) == 0)
    {
        return _floatToChar(_peri->getTempC());
    }
    else if (strcmp("GTMF", command) == 0)
    {
        return _floatToChar(_peri->getTempF());
    }
    else if (strcmp("GVOL", command) == 0)
    {
        return _floatToChar(_peri->getVoltage());
    }
    else if (strcmp("GWFM", command) == 0)
    {
        return _uintToChar(_eeprom->getWifiMode());
    }
    else if (strcmp("SWFM", command) == 0)
    {
        _wifi->setWifiMode((unsigned short)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("GWFP", command) == 0)
    {
        return _eeprom->getWifiPassword();
    }
    else if (strcmp("SWFP", command) == 0)
    {
        _wifi->setWifiPassword(commandParam);
        return "OK";
    }
    else if (strcmp("DEBG", command) == 0)
    {
        _eeprom->debug();
        return "";
    }
    //manual movement
    else if (strcmp("MGST", command) == 0)
    {
        return _uintToChar(_eeprom->getManualStepMode());
    }
    else if (strcmp("MSST", command) == 0)
    {
        _eeprom->setManualStepMode((unsigned short)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("MGSP", command) == 0)
    {
        return _uintToChar(_eeprom->getManualSpeedMode());
    }
    else if (strcmp("MSSP", command) == 0)
    {
        _eeprom->setManualSpeedMode((unsigned short)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("MSRV", command) == 0)
    {
        _eeprom->setManualReverseDirection(atoi(commandParam) == 1 ? true : false);
        return "OK";
    }
    else if (strcmp("MGRV", command) == 0)
    {
        return _eeprom->getManualReverseDirection() ? "1" : "0";
    }
      else if (strcmp("MSCL", command) == 0)
    {
        _motor->setManualCoilsMode((unsigned short)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("MGCL", command) == 0)
    {
         return _uintToChar(_eeprom->getManualCoilsMode());
    }
     else if (strcmp("MGCM", command) == 0)
    {
        if (_commandEndsWith('%', commandParam, commandParamLength))
        {
            char *buffer = new char[4];
            sprintf(buffer, "%d%%", _motor->getManualMoveCurrentPercent());
            return buffer;
        }
        else
        {
            return _uintToChar(_eeprom->getManualCoilsCurrentMove());
        }
    }
    else if (strcmp("MSCM", command) == 0)
    {
        if (_commandEndsWith('%', commandParam, commandParamLength))
        {
            int length = strlen(commandParam) - 1;
            char percentValue[length];
            strncpy(percentValue, commandParam, length);
            _motor->setManualMoveCurrentPercent(atof(percentValue));
        }
        else
        {
            _eeprom->setManualCoilsCurrentMove((unsigned short)atoi(commandParam));
        }

        return "OK";
    }
    else if (strcmp("MGCH", command) == 0)
    {
        if (_commandEndsWith('%', commandParam, commandParamLength))
        {
            char *buffer = new char[4];
            sprintf(buffer, "%d%%", _motor->getManualHoldCurrentPercent());
            return buffer;
        }
        else
        {
            return _uintToChar(_eeprom->getManualCoilsCurrentHold());
        }
    }
    else if (strcmp("MSCH", command) == 0)
    {
        if (_commandEndsWith('%', commandParam, commandParamLength))
        {
            int length = strlen(commandParam) - 1;
            char percentValue[length];
            strncpy(percentValue, commandParam, length);
            _motor->setManualHoldCurrentPercent(atof(percentValue));
        }
        else
        {
            _motor->setManualHoldCurrent((unsigned short)atoi(commandParam));
        }

        return "OK";
    }
     else if (strcmp("MGIC", command) == 0)
    {
        return _uintToChar(_eeprom->getManualCoilsIdleTimeoutMs());
    }
    else if (strcmp("MSIC", command) == 0)
    {
        _eeprom->setManualCoilsIdleTimeoutMs((unsigned int)atoi(commandParam));
        return "OK";
    }
    else if (strcmp("MSMV", command) == 0)
    {
        _motor->moveManual();
        return "OK";
    }
    else if (strcmp("MMCW", command) == 0)
    {
        _motor->moveManualContinuous(MOVEMENT_MANUAL_DIR::CW);
        return "OK";
    }
    else if (strcmp("MMCC", command) == 0)
    {
        _motor->moveManualContinuous(MOVEMENT_MANUAL_DIR::CCW);
        return "OK";
    }
    else if (strcmp("TEST", command) == 0)
    {
        if(_test->execute(*_eeprom, *_motor, *_peri, *_wifi) == 1)
            return "OK";
        else
            return "FAIL";
    }

    return "100";
}