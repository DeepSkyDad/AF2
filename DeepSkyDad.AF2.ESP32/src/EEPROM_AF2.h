#define EEPROM_SIZE 4096
#define EEPROM_WRITE_PERIOD_MS 5000

#pragma once

//use strong enum ("enum class") instead of leagy, which has issues
enum class STEP_MODE : unsigned short
{
	FULL = 1,
    HALF = 2,
    QUARTER = 4,
	EIGHT = 8
};

//use strong enum ("enum class") instead of leagy, which has issues
enum class SPEED_MODE : unsigned short
{
	SLOW = 1,
    MEDIUM = 2,
    FAST = 3
};

//use strong enum ("enum class") instead of leagy, which has issues
enum class COILS_MODE : unsigned short
{
	IDLE_OFF,
    ALWAYS_ON,
    IDLE_TIMEOUT_OFF
};

//use strong enum ("enum class") instead of leagy, which has issues
enum class WIFI_MODE : unsigned short
{
	OFF,
    AP,
    STA,
	AP_STA
};

enum class MANUAL_STEP_SIZE : unsigned short
{
	FINE = 1,
    COARSE = 2
};


class EEPROM_STATE
{
	public:
		unsigned int position;
		unsigned int targetPosition;
		unsigned int maxPosition;
		unsigned int maxMovement;
		unsigned short stepMode;
		unsigned short speedMode;
		unsigned int settleBufferMs; 
		bool isManualControl;
		unsigned short wifiMode;
		char wifiAPPassword[20];
		bool reverseDirection;
		unsigned int eepromWriteTimeoutMs;
		unsigned short coilsMode;
		unsigned int coilsIdleTimeoutMs;
		unsigned short coilsCurrentMove;
		unsigned short coilsCurrentHold;
		unsigned short manualStepMode;
		unsigned short manualSpeedMode;
		bool manualReverseDirection;
		unsigned short manualStepSize;
		unsigned int manualFineMoveSteps;
		unsigned int manualCoarseMoveSteps;
		unsigned short manualCoilsMode;
		unsigned int manualCoilsIdleTimeoutMs;
		unsigned short manualCoilsCurrentMove;
		unsigned short manualCoilsCurrentHold;
		unsigned long checksum;
};

class EEPROM_AF2
{
	private:
		EEPROM_STATE _state;
		EEPROM_STATE _stateDefaults;
		EEPROM_STATE _stateCurrent;
		bool _isDirty;
		unsigned int _lastEepromWriteMs;
		unsigned int _nextWriteDelayMs;
		int _eepromAfStateAdressesCount;
		int _eepromAfStateCurrentAddress;
		void _writeState(const EEPROM_STATE& st);
		void _readState(EEPROM_STATE& st);
		bool _writeEeprom();
		bool _writeEeprom(bool isForceWrite);
		void _nextAddress();
		int _calculateChecksum(EEPROM_STATE& st);
		void _cloneState(EEPROM_STATE& from, EEPROM_STATE& to);
	public:
		void init();
		void handleEepromWrite();
		void resetToDefaults();
		void delayEepromWrite();
		void debug();
		
		unsigned int getPosition();
		void setPosition(unsigned int value);
		void syncPosition(unsigned int value);
		unsigned int getTargetPosition();
		bool setTargetPosition(unsigned int value);
		unsigned int getMaxPosition();
		void setMaxPosition(unsigned int value);
		unsigned int getMaxMovement();
		void setMaxMovement(unsigned int value);
		unsigned short getStepMode();
		void setStepMode(unsigned short value);
		unsigned short getSpeedMode();
		void setSpeedMode(unsigned short value);
		unsigned int getSettleBufferMs();
		void setSettleBufferMs(unsigned int value); 
		bool getIsManualControl();
		void setIsManualControl(bool value); 
		unsigned short getWifiMode();
		void setWifiMode(unsigned short value);
		char* getWifiPassword();
		void setWifiPassword(char* value); 
		bool getReverseDirection();
		void setReverseDirection(bool value);
		unsigned int getEepromWriteTimeoutMs();
		void setEepromWriteTimeoutMs(unsigned int value);
		unsigned short getCoilsMode();
		void setCoilsMode(unsigned short value);
		unsigned int getCoilsIdleTimeoutMs();
		void setCoilsIdleTimeoutMs(unsigned int value);
		unsigned short getCoilsCurrentMove();
		void setCoilsCurrentMove(unsigned short value);
		unsigned short getCoilsCurrentHold();
		void setCoilsCurrentHold(unsigned short value);
		unsigned short getManualStepMode();
		void setManualStepMode(unsigned short value);
		unsigned short getManualSpeedMode();
		void setManualSpeedMode(unsigned short value);
		bool getManualReverseDirection();
		void setManualReverseDirection(bool value);
		unsigned short getManualStepSize();
		void setManualStepSize(unsigned short value);
		unsigned int getManualFineMoveSteps();
		void setManualFineMoveSteps(unsigned int value);
		unsigned int getManualCoarseMoveSteps();
		void setManualCoarseMoveSteps(unsigned int value);
		unsigned short getManualCoilsMode();
		void setManualCoilsMode(unsigned short value);
		unsigned int getManualCoilsIdleTimeoutMs();
		void setManualCoilsIdleTimeoutMs(unsigned int value);
		unsigned short getManualCoilsCurrentMove();
		void setManualCoilsCurrentMove(unsigned short value);
		unsigned short getManualCoilsCurrentHold();
		void setManualCoilsCurrentHold(unsigned short value);
		unsigned long getChecksum();
		void setChecksum(unsigned long value);
};