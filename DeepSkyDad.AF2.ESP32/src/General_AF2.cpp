#include <Arduino.h>
#include <WiFi.h>
#include "General_AF2.h"

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

const char* AF2::getDeviceId() {
    static char id[7] = {0};
    if (id[0] == 0) {
        uint8_t softApMac[6];
        WiFi.softAPmacAddress(softApMac);
        snprintf(id, sizeof(id), "%02X%02X%02X", softApMac[3], softApMac[4], softApMac[5]);
        id[sizeof(id) - 1] = 0;
    }
    return id;
}

float AF2::getBoardTempC() {
    return (temprature_sens_read() - 32) / 1.8;
}