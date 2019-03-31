#include "EEPROM_AF2.h"

#pragma once
#define MP6500_PIN_EN 14
#define MP6500_PIN_DIR 23
#define MP6500_PIN_STEP 22
#define MP6500_PIN_I1 25 //current limiting pin. To set specific current, change PWM to specific voltage. Equation: CURRENT=2.2−0.63*MP6500_PIN_I1
#define MP6500_PIN_I1_CHANNEL 1
#define MP6500_PIN_MS2 26
#define MP6500_PIN_MS1 27
#define MP6500_PIN_SLP 21

#define MP6500_PIN_I1_MOVE_MIN 4000
#define MP6500_PIN_I1_MOVE_MAX 4052
#define MP6500_PIN_I1_MOVE_RANGE (MP6500_PIN_I1_MOVE_MAX - MP6500_PIN_I1_MOVE_MIN)
#define MP6500_PIN_I1_HOLD_MIN 4052
#define MP6500_PIN_I1_HOLD_MAX 4096
#define MP6500_PIN_I1_HOLD_RANGE (MP6500_PIN_I1_HOLD_MAX - MP6500_PIN_I1_HOLD_MIN)

/*#define MP6500_PIN_I1_MOVE_MIN 2500
#define MP6500_PIN_I1_MOVE_MAX 4052
#define MP6500_PIN_I1_MOVE_RANGE (MP6500_PIN_I1_MOVE_MAX - MP6500_PIN_I1_MOVE_MIN)
#define MP6500_PIN_I1_HOLD_MIN 3760
#define MP6500_PIN_I1_HOLD_MAX 4052
#define MP6500_PIN_I1_HOLD_RANGE (MP6500_PIN_I1_HOLD_MAX - MP6500_PIN_I1_HOLD_MIN)*/


//use strong enum ("enum class") instead of leagy, which has issues
enum class MOVEMENT_STATUS
{
	STOP,
    MOVING,
    MOVING_MANUAL,
    MOVING_MANUAL_CONTINUOUS
};

//use strong enum ("enum class") instead of leagy, which has issues
enum class MOVEMENT_MANUAL_DIR
{
	CW,
	CCW
};

class Motor_AF2
{
	private:
        EEPROM_AF2* _eeprom;
        volatile MOVEMENT_STATUS _movementStatus = MOVEMENT_STATUS::STOP;
        unsigned long _lastStopMs;
        bool _coilsOn;
        bool _settled;
        void _writeCoilsMode();
        void _writeStepMode(unsigned short stepMode);
	public:
		void init(EEPROM_AF2 &eeprom);

        //GENERAL
        void handleMove();
        void stop();
        bool isMoving();
        MOVEMENT_STATUS getMovementStatus();
        void resetToDefaults();

        //EXTERNAL (ASCOM or INDI via Serial/Wifi)
        void move();
        void setCoilsMode(unsigned short mode);
        int getMoveCurrentPercent();
        void setMoveCurrentPercent(float percent);
        void setMoveCurrent(unsigned int percent);
        int getHoldCurrentPercent();
        void setHoldCurrentPercent(float percent);
        void setHoldCurrent(unsigned int value);
        
        //MOVING_MANUAL MOVEMENT (HC or Wifi GUI)
        void moveManual();
        void moveManual(MOVEMENT_MANUAL_DIR dir);
        void moveManualContinuous(MOVEMENT_MANUAL_DIR dir);
        void setManualCoilsMode(unsigned short mode);
        int getManualMoveCurrentPercent();
        void setManualMoveCurrentPercent(float percent);
        void setManualMoveCurrent(unsigned int percent);
        int getManualHoldCurrentPercent();
        void setManualHoldCurrentPercent(float percent);
        void setManualHoldCurrent(unsigned int value);
};