#include "EEPROM_AF2.h"
#include "Motor_AF2.h"
#include "Peripherals_AF2.h"
#include "Wifi_AF2.h"
#include "General_AF2.h"

#pragma once
class Test_AF2
{
    public:
        int execute(EEPROM_AF2 &_eeprom, Motor_AF2 &_motor, Peripherals_AF2 &_peri, Wifi_AF2 &_wifi);
};