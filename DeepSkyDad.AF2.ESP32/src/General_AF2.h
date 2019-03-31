#pragma once

#define AF2_FW_VERSION "1.0.1"
#define AF2_BOARD "DeepSkyDad.AF2"

class AF2 {
    public:
        static const char* getDeviceId();
        static float getBoardTempC();
};

