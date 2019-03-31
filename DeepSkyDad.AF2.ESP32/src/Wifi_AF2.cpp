#include <Arduino.h>
#include "Wifi_AF2.h"
#include "General_AF2.h"

void Wifi_AF2::init(EEPROM_AF2 &eeprom, Motor_AF2 &motor, Peripherals_AF2 &peri)
{
    _eeprom = &eeprom;
    _motor = &motor;
    _peri = &peri;

    WiFi.mode(WIFI_AP);
    WiFi.setTxPower(WIFI_POWER_MINUS_1dBm);

    snprintf(_ssid, sizeof(_ssid), _ssidTpl, AF2::getDeviceId());
    _ssid[sizeof(_ssid) - 1] = 0;
    WiFi.softAPConfig(_localIp, _gateway, _subnet);
    WiFi.softAP(_ssid, _eeprom->getWifiPassword());

    //MDNS.begin(_mdns);

    SPIFFS.begin();

    _server.begin();
}

bool Wifi_AF2::_strEndsWith(const char *str, const char *suffix)
{
    int len = strlen(str);
    int suffixlen = strlen(suffix);
    if (suffixlen > len)
    {
        return false;
    }

    str += (len - suffixlen);
    return strcmp(str, suffix) == 0;
}

void Wifi_AF2::_writeResponse()
{
    if (strstr(_url, "/api/"))
    {
        if (strstr(_url, "/api/status"))
        {
            //do nothing
        }
        else if (strstr(_url, "/api/up"))
        {
            if (_motor->isMoving())
            {
                //do nothing
            }
            else
            {

                _motor->moveManual(MOVEMENT_MANUAL_DIR::CW);

                while (_motor->isMoving())
                {
                    delay(100);
                }
            }
        }
        else if (strstr(_url, "/api/down"))
        {
            if (_motor->isMoving())
            {
                //do nothing
            }
            else
            {
                _motor->moveManual(MOVEMENT_MANUAL_DIR::CCW);

                while (_motor->isMoving())
                {
                    delay(100);
                }
            }
        }
        else if (strstr(_url, "/api/save"))
        {
            memset(_currentLine, 0, 1024);
            _currentLineIdx = 0;
            while (_client.available())
            {
                _currentLine[_currentLineIdx] = (char)_client.read();
                _currentLineIdx++;
            }

            //Serial.println(_currentLine);
            JsonObject &root = _jsonBuffer.parseObject(_currentLine);

            if (root.containsKey("position"))
            {
                unsigned int position = root.get<unsigned int>("position");
                _eeprom->syncPosition(position);
                //Serial.println(position);
            }

            if (root.containsKey("manualReverseDirection"))
            {
                bool manualReverseDirection = root.get<bool>("manualReverseDirection");
                _eeprom->setManualReverseDirection(manualReverseDirection);
                //Serial.println(manualReverseDirection);
            }

            if (root.containsKey("manualCoilsMode"))
            {
                unsigned short manualCoilsMode = root.get<unsigned short>("manualCoilsMode");
                _motor->setManualCoilsMode(manualCoilsMode);
                //Serial.println(manualCoilsMode);
            }

            if (root.containsKey("manualStepMode"))
            {
                unsigned short manualStepMode = root.get<unsigned short>("manualStepMode");
                _eeprom->setManualStepMode(manualStepMode);
                //Serial.println(manualStepMode);
            }

            if (root.containsKey("manualSpeedMode"))
            {
                unsigned short manualSpeedMode = root.get<unsigned short>("manualSpeedMode");
                _eeprom->setManualSpeedMode(manualSpeedMode);
                //Serial.println(manualSpeedMode);
            }

            if (root.containsKey("manualStepSize"))
            {
                unsigned short manualStepSize = root.get<unsigned short>("manualStepSize");
                _eeprom->setManualStepSize(manualStepSize);
                //Serial.println(manualStepMode);
            }

            if (root.containsKey("manualFineMoveSteps"))
            {
                unsigned int manualFineMoveSteps = root.get<unsigned int>("manualFineMoveSteps");
                _eeprom->setManualFineMoveSteps(manualFineMoveSteps);
                //Serial.println(manualFineMoveSteps);
            }

            if (root.containsKey("manualCoarseMoveSteps"))
            {
                unsigned int manualCoarseMoveSteps = root.get<unsigned int>("manualCoarseMoveSteps");
                _eeprom->setManualCoarseMoveSteps(manualCoarseMoveSteps);
                //Serial.println(manualCoarseMoveSteps);
            }

            if (root.containsKey("manualCoilsCurrentHold"))
            {
                float manualCoilsCurrentHold = root.get<float>("manualCoilsCurrentHold");
                _motor->setManualHoldCurrentPercent(manualCoilsCurrentHold);
                //Serial.println(manualCoilsCurrentHold);
            }

            if (root.containsKey("manualCoilsCurrentMove"))
            {
                float manualCoilsCurrentMove = root.get<float>("manualCoilsCurrentMove");
                _motor->setManualMoveCurrentPercent(manualCoilsCurrentMove);
                //Serial.println(manualCoilsCurrentMove);
            }

            if (root.containsKey("manualIdleCoilsTimeout"))
            {
                unsigned int manualIdleCoilsTimeout = root.get<unsigned int>("manualIdleCoilsTimeout");
                _eeprom->setManualCoilsIdleTimeoutMs(manualIdleCoilsTimeout);
                //Serial.println(manualIdleCoilsTimeout);
            }
        }
        else
        {
            _client.println("HTTP/1.1 404 Not Found");
            _client.println("Connection: close");
            _client.println();
            _client.println("Not found");
            _client.println();
            return;
        }

        JsonObject &data = _jsonBuffer.createObject();

        data["position"] = _eeprom->getPosition();
        data["temperatureC"] = _peri->getTempC();
        data["temperatureF"] = _peri->getTempF();
        data["isMoving"] = _motor->isMoving();
        data["maxPosition"] = _eeprom->getMaxPosition();
        data["maxMovement"] = _eeprom->getMaxMovement();
        data["manualCoilsMode"] = _eeprom->getManualCoilsMode();
        data["manualStepMode"] = _eeprom->getManualStepMode();
        data["manualSpeedMode"] = _eeprom->getManualSpeedMode();
        data["manualReverseDirection"] = _eeprom->getManualReverseDirection();
        data["manualStepSize"] = _eeprom->getManualStepSize();
        data["manualFineMoveSteps"] = _eeprom->getManualFineMoveSteps();
        data["manualCoarseMoveSteps"] = _eeprom->getManualCoarseMoveSteps();
        data["manualCoilsCurrentMove"] = _motor->getManualMoveCurrentPercent();
        data["manualCoilsCurrentHold"] = _motor->getManualHoldCurrentPercent();
        data["manualIdleCoilsTimeout"] = _eeprom->getManualCoilsIdleTimeoutMs();

        _client.println("HTTP/1.1 200 OK");
        _client.println("Content-type:application/json");
        _client.println("Connection: close");
        _client.println();
        data.printTo(_client);
        _client.println();

        _jsonBuffer.clear();
    }
    else
    {
        if (strlen(_url) == 1 && _url[0] == '/')
            strcpy(_url, "/www/index.htm");
        else
        {
            char base[1024] = "/www";
            strcat(base, _url);
            strcpy(_url, base);
        }

        char dataType[50];
        if (_strEndsWith(_url, ".htm"))
        {
            strcpy(dataType, "text/html");
        }
        else if (_strEndsWith(_url, ".css"))
        {
            strcpy(dataType, "text/css");
        }
        else if (_strEndsWith(_url, ".js"))
        {
            strcpy(dataType, "application/javascript");
        }
        else if (_strEndsWith(_url, ".png"))
        {
            strcpy(dataType, "image/png");
        }
        else if (_strEndsWith(_url, ".gif"))
        {
            strcpy(dataType, "image/gif");
        }
        else if (_strEndsWith(_url, ".jpg"))
        {
            strcpy(dataType, "image/jpeg");
        }
        else if (_strEndsWith(_url, ".ico"))
        {
            strcpy(dataType, "image/x-icon");
        }
        else if (_strEndsWith(_url, ".xml"))
        {
            strcpy(dataType, "text/xml");
        }
        else if (_strEndsWith(_url, ".pdf"))
        {
            strcpy(dataType, "application/pdf");
        }
        else if (_strEndsWith(_url, ".zip"))
        {
            strcpy(dataType, "application/zip");
        }
        else if (_strEndsWith(_url, ".svg"))
        {
            strcpy(dataType, "image/svg+xml");
        }
        else if (_strEndsWith(_url, ".woff2"))
        {
            strcpy(dataType, "font/woff2");
        }
        else if (_strEndsWith(_url, ".woff"))
        {
            strcpy(dataType, "font/woff");
        }

        char gzUrl[1024];
        strcpy(gzUrl, _url);
        strcat(gzUrl, ".gz");
        if (isGzip && SPIFFS.exists(gzUrl))
        {
            strcpy(_url, gzUrl);
        }
        else if (!SPIFFS.exists(_url))
        {
            _client.println("HTTP/1.1 404 Not Found");
            _client.println("Connection: close");
            _client.println();
            _client.println("Not found");
            _client.println();
            return;
        }

        File f = SPIFFS.open(_url, "r");

        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
        // and a content-type so the _client knows what's coming, then a blank line:
        _client.println("HTTP/1.1 200 OK");
        _client.print("Content-type: ");
        _client.println(dataType);
        _client.println("Connection: close");
        _client.println("Cache-Control: public, max-age=31536000");
        if (isGzip)
        {
            _client.println("Content-encoding: gzip");
        }
        else
        {
            _client.println("Content-length:" + f.size());
        }

        _client.println();

        _client.write(f);

        f.close();

        _client.println();
    }
}

bool Wifi_AF2::webServerEvent()
{
    _client = _server.available();

    if (_client)
    {
        isGzip = false;
        memset(_url, 0, 1024);
        memset(_currentLine, 0, 1024);
        _currentLineIdx = 0;

        //Serial.println("INCOMING REQUEST");

        while (_client.connected())
        {
            if (_client.available())
            {
                char c = _client.read();
                _currentLine[_currentLineIdx] = c;
                _currentLineIdx++;
                //Serial.print(_currentLineIdx);
                //Serial.print(" -> ");
                //Serial.println(c);

                if (c == '\n')
                {
                    if (_currentLineIdx == 2)
                    {
                        //Serial.println("WRITE WWW RESPONSE");
                        //Serial.print("URL: ");
                        //Serial.println(_url);
                        //Serial.print("IS GZIP: ");
                        //Serial.println(isGzip);
                        _writeResponse();
                        break;
                    }

                    char *p1 = strstr(_currentLine, "GET ");
                    char *p2 = strstr(_currentLine, " HTTP");

                    if (p2)
                    {
                        if (p1)
                        {
                            p1 += 4;
                        }
                        else
                        {
                            p1 = strstr(_currentLine, "POST ");
                            if (p1)
                                p1 += 5;
                        }
                    }

                    if (p1 && p2)
                    {

                        ptrdiff_t bytes = ((char *)p2) - ((char *)p1);
                        strncpy(_url, p1, bytes);
                    }
                    else if (strstr(_currentLine, "gzip"))
                        isGzip = true;

                    //Serial.print("WWW REQUEST LINE: ");
                    //Serial.println(_currentLine);
                    memset(_currentLine, 0, 1024);
                    _currentLineIdx = 0;
                }
            }
        }

        _client.stop();
        return true;
    }

    return false;
}

void Wifi_AF2::setWifiMode(unsigned short value)
{

    switch (value)
    {
    case (unsigned short)WIFI_MODE::OFF:
        WiFi.mode(WIFI_OFF);
        break;
    case (unsigned short)WIFI_MODE::AP:
        WiFi.mode(WIFI_AP);
        break;
    case (unsigned short)WIFI_MODE::STA:
        WiFi.mode(WIFI_STA);
        break;
    case (unsigned short)WIFI_MODE::AP_STA:
        WiFi.mode(WIFI_AP_STA);
        break;
    default:
        value = (unsigned short)WIFI_MODE::AP;
        WiFi.mode(WIFI_AP);
        break;
    }

    _eeprom->setWifiMode(value);
}

void Wifi_AF2::setWifiPassword(char *password)
{
    _eeprom->setWifiPassword(password);
    WiFi.softAP(_ssid, password);
}

const char* Wifi_AF2::getSsid() {
    return _ssid;
}

void Wifi_AF2::resetToDefaults() {
     _eeprom->setWifiPassword(_eeprom->getWifiPassword());
    WiFi.softAP(_ssid, _eeprom->getWifiPassword());
}