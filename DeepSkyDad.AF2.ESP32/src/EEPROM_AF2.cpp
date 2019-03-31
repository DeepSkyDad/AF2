#include <EEPROM.h>
#include "EEPROM_AF2.h"

void EEPROM_AF2::_writeState(const EEPROM_STATE &st)
{
    int address = _eepromAfStateCurrentAddress;
    const byte *pntr = (const byte *)(const void *)&st;
    for (unsigned short idx = 0; idx < sizeof(st); idx++)
    {
        EEPROM.write(address++, *pntr++);
    }
}

void EEPROM_AF2::_readState(EEPROM_STATE &st)
{
    int address = _eepromAfStateCurrentAddress;
    byte *pntr = (byte *)(void *)&st;
    unsigned int idx;
    for (idx = 0; idx < sizeof(st); idx++)
    {
        *pntr++ = EEPROM.read(address++);
    }
}

bool EEPROM_AF2::_writeEeprom()
{
    return _writeEeprom(false);
}

bool EEPROM_AF2::_writeEeprom(bool isForce)
{
    _lastEepromWriteMs = millis();
    _nextWriteDelayMs = 0;

    /*
        Due to concurrency issues, DO NOT write to EEPROM if motor is moving ( unless force write is requested).
        
        Details (https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/storage/spi_flash.html):
        To avoid reading flash cache accidentally, when one CPU commences a flash write or erase operation the other CPU is
        put into a blocked state and all non-IRAM-safe interrupts are disabled on both CPUs, until the flash operation completes.
    */
    if(!isForce && _state.position != _state.targetPosition) {
        //Serial.println("MOTOR MOVING - SKIP EEPROM WRITE");
        return false;
    }

    if (!isForce)
    {
        if (!_isDirty)
        {
            //Serial.println("EEPROM NOT DIRTY");
            return false;
        }

        _isDirty = false;

        //prevent unneccessary writes
        if (_state.position == _stateCurrent.position &&
            _state.targetPosition == _stateCurrent.targetPosition &&
            _state.maxPosition == _stateCurrent.maxPosition &&
            _state.maxMovement == _stateCurrent.maxMovement &&
            _state.stepMode == _stateCurrent.stepMode &&
            _state.speedMode == _stateCurrent.speedMode &&
            _state.settleBufferMs == _stateCurrent.settleBufferMs &&
            _state.isManualControl == _stateCurrent.isManualControl &&
            _state.wifiMode == _stateCurrent.wifiMode &&
            _state.wifiAPPassword == _stateCurrent.wifiAPPassword &&
            _state.reverseDirection == _stateCurrent.reverseDirection &&
            _state.eepromWriteTimeoutMs == _stateCurrent.eepromWriteTimeoutMs &&
            _state.coilsMode == _stateCurrent.coilsMode &&
            _state.coilsIdleTimeoutMs == _stateCurrent.coilsIdleTimeoutMs &&
            _state.coilsCurrentMove == _stateCurrent.coilsCurrentMove &&
            _state.coilsCurrentHold == _stateCurrent.coilsCurrentHold &&
            _state.manualStepMode == _stateCurrent.manualStepMode &&
            _state.manualSpeedMode == _stateCurrent.manualSpeedMode &&
            _state.manualReverseDirection == _stateCurrent.manualReverseDirection &&
            _state.manualStepSize == _stateCurrent.manualStepSize &&
            _state.manualFineMoveSteps == _stateCurrent.manualFineMoveSteps &&
            _state.manualCoarseMoveSteps == _stateCurrent.manualCoarseMoveSteps &&
            _state.manualCoilsMode == _stateCurrent.manualCoilsMode &&
            _state.manualCoilsIdleTimeoutMs == _stateCurrent.manualCoilsIdleTimeoutMs &&
            _state.manualCoilsCurrentMove == _stateCurrent.manualCoilsCurrentMove &&
            _state.manualCoilsCurrentHold == _stateCurrent.manualCoilsCurrentHold)
        {
            //Serial.println("EEPROM NOT CHANGED");
            return false;
        }
    }

    //invalidate previous state
    if (_stateCurrent.checksum == _calculateChecksum(_stateCurrent))
    {
        _stateCurrent.checksum -= 1;
    }
    _writeState(_stateCurrent);
    EEPROM.commit();

    _nextAddress();

    _state.checksum = _calculateChecksum(_state);
    _writeState(_state);
    EEPROM.commit();
    _cloneState(_state, _stateCurrent);
    //Serial.print("EEPROM WRITE TO ADDRESS ");
    //Serial.println(_eepromAfStateCurrentAddress);

    return true;
}

void EEPROM_AF2::_nextAddress()
{
    _eepromAfStateCurrentAddress += sizeof(EEPROM_STATE);
    if (_eepromAfStateCurrentAddress > EEPROM_SIZE)
        _eepromAfStateCurrentAddress = 0;
}

int EEPROM_AF2::_calculateChecksum(EEPROM_STATE &st)
{
    return st.position +
           st.targetPosition +
           st.maxPosition +
           st.maxMovement +
           st.stepMode +
           st.speedMode +
           st.settleBufferMs +
           st.isManualControl +
           st.wifiMode +
           st.reverseDirection +
           st.eepromWriteTimeoutMs +
           st.coilsMode +
           st.coilsIdleTimeoutMs +
           st.coilsCurrentMove +
           st.coilsCurrentHold +
           st.manualStepMode +
           st.manualSpeedMode +
           st.manualReverseDirection +
           st.manualStepSize +
           st.manualFineMoveSteps +
           st.manualCoarseMoveSteps +
           st.manualCoilsMode +
           st.manualCoilsCurrentMove +
           st.manualCoilsCurrentHold;
}

void EEPROM_AF2::_cloneState(EEPROM_STATE &from, EEPROM_STATE &to)
{
    to.position = from.position;
    to.targetPosition = from.targetPosition;
    to.maxPosition = from.maxPosition;
    to.maxMovement = from.maxMovement;
    to.stepMode = from.stepMode;
    to.speedMode = from.speedMode;
    to.settleBufferMs = from.settleBufferMs;
    to.isManualControl = from.isManualControl;
    to.wifiMode = from.wifiMode;
    strcpy(to.wifiAPPassword, from.wifiAPPassword);
    to.reverseDirection = from.reverseDirection;
    to.eepromWriteTimeoutMs = from.eepromWriteTimeoutMs;
    to.coilsMode = from.coilsMode;
    to.coilsIdleTimeoutMs = from.coilsIdleTimeoutMs;
    to.coilsCurrentMove = from.coilsCurrentMove;
    to.coilsCurrentHold = from.coilsCurrentHold;
    to.manualStepMode = from.manualStepMode;
    to.manualSpeedMode = from.manualSpeedMode;
    to.manualReverseDirection = from.manualReverseDirection;
    to.manualStepSize = from.manualStepSize;
    to.manualFineMoveSteps = from.manualFineMoveSteps;
    to.manualCoarseMoveSteps = from.manualCoarseMoveSteps;
    to.manualCoilsMode = from.manualCoilsMode;
    to.manualCoilsIdleTimeoutMs = from.manualCoilsIdleTimeoutMs;
    to.manualCoilsCurrentMove = from.manualCoilsCurrentMove;
    to.manualCoilsCurrentHold = from.manualCoilsCurrentHold;
    to.checksum = from.checksum;
}

void EEPROM_AF2::init()
{
    EEPROM.begin(EEPROM_SIZE);

    //defaults
    _stateDefaults.position = 50000;
    _stateDefaults.targetPosition = 50000;
    _stateDefaults.maxPosition = 100000;
    _stateDefaults.maxMovement = 5000;
    _stateDefaults.stepMode = (unsigned short)STEP_MODE::HALF;
    _stateDefaults.speedMode = (unsigned short)SPEED_MODE::FAST;
    _stateDefaults.settleBufferMs = 0;
    _stateDefaults.isManualControl = false;
    _stateDefaults.wifiMode = (unsigned short)WIFI_MODE::AP;
    strcpy(_stateDefaults.wifiAPPassword, "AF2pwd123");
    _stateDefaults.reverseDirection = false;
    _stateDefaults.eepromWriteTimeoutMs = 180000;
    _stateDefaults.coilsMode =(unsigned short) COILS_MODE::ALWAYS_ON;
    _stateDefaults.coilsIdleTimeoutMs = 60000;
    _stateDefaults.coilsCurrentMove = 4039;
    _stateDefaults.coilsCurrentHold = 4085;
    _stateDefaults.manualStepMode = (unsigned short)STEP_MODE::EIGHT;
    _stateDefaults.manualSpeedMode = (unsigned short)SPEED_MODE::SLOW;
    _stateDefaults.manualReverseDirection = false;
    _stateDefaults.manualStepSize = (unsigned short)MANUAL_STEP_SIZE::FINE;
    _stateDefaults.manualFineMoveSteps = 10;
    _stateDefaults.manualCoarseMoveSteps = 100;
    _stateDefaults.manualCoilsMode = (unsigned short)COILS_MODE::ALWAYS_ON;
    _stateDefaults.manualCoilsIdleTimeoutMs = 60000;
    _stateDefaults.manualCoilsCurrentMove = 4039;
    _stateDefaults.manualCoilsCurrentHold = 4085;
    _stateDefaults.checksum = _calculateChecksum(_stateDefaults);

    bool afStateFound = false;
    _eepromAfStateAdressesCount = EEPROM_SIZE / sizeof(EEPROM_STATE);
    _eepromAfStateCurrentAddress = 0;
    for (int i = 0; i < _eepromAfStateAdressesCount; i++)
    {
        _readState(_state);
        if (_state.checksum == _calculateChecksum(_state))
        {
            _cloneState(_state, _stateCurrent);
            afStateFound = true;
            break;
        }

        _nextAddress();
    }

    if (!afStateFound)
        resetToDefaults();

    _lastEepromWriteMs = millis();
    _nextWriteDelayMs = 0;
}

void EEPROM_AF2::handleEepromWrite()
{
    if ((_lastEepromWriteMs + EEPROM_WRITE_PERIOD_MS + _nextWriteDelayMs) < millis())
    {
        _writeEeprom();
    }
}

void EEPROM_AF2::resetToDefaults()
{
    _cloneState(_stateDefaults, _state);
    _cloneState(_stateDefaults, _stateCurrent);
    _writeEeprom(true);
}

void EEPROM_AF2::delayEepromWrite() {
    _nextWriteDelayMs = _state.eepromWriteTimeoutMs;
}

void EEPROM_AF2::debug()
{
    Serial.println("---------------------");
    Serial.print("ADDRESS: ");
    Serial.println(_eepromAfStateCurrentAddress);
    Serial.print("Is dirty: ");
    Serial.println(_isDirty);
    Serial.print("position: ");
    Serial.println(_state.position);
    Serial.print("target position: ");
    Serial.println(_state.targetPosition);
    Serial.print("maxPosition: ");
    Serial.println(_state.maxPosition);
    Serial.print("maxMovement: ");
    Serial.println(_state.maxMovement);
    Serial.print("stepMode: ");
    Serial.println(_state.stepMode);
    Serial.print("speedMode: ");
    Serial.println(_state.speedMode);
    Serial.print("settleBufferMs: ");
    Serial.println(_state.settleBufferMs);
    Serial.print("isManualControl: ");
    Serial.println(_state.isManualControl);
    Serial.print("wifiMode: ");
    Serial.println(_state.wifiMode);
    Serial.print("wifiAPPassword: ");
    Serial.println(_state.wifiAPPassword);
    Serial.print("reverseDirection: ");
    Serial.println(_state.reverseDirection);
    Serial.print("eepromWriteTimeoutMs: ");
    Serial.println(_state.eepromWriteTimeoutMs);
    Serial.print("coilsMode: ");
    Serial.println(_state.coilsMode);
    Serial.print("coilsIdleTimeoutMs: ");
    Serial.println(_state.coilsIdleTimeoutMs);
    Serial.print("coilsCurrentMove: ");
    Serial.println(_state.coilsCurrentMove);
    Serial.print("coilsCurrentHold: ");
    Serial.println(_state.coilsCurrentHold);
    Serial.print("manualCoilsMode: ");
    Serial.println(_state.manualCoilsMode);
    Serial.print("manualStepMode: ");
    Serial.println(_state.manualStepMode);
    Serial.print("manualSpeedMode: ");
    Serial.println(_state.manualSpeedMode);
    Serial.print("manualReverseDirection: ");
    Serial.println(_state.manualReverseDirection);
    Serial.print("manualStepSize: ");
    Serial.println(_state.manualStepSize);
    Serial.print("manualFineMoveSteps: ");
    Serial.println(_state.manualFineMoveSteps);
    Serial.print("manualCoarseMoveSteps: ");
    Serial.println(_state.manualCoarseMoveSteps);
    Serial.print("manualCoilsMode: ");
    Serial.println(_state.manualCoilsMode);
    Serial.print("manualCoilsCurrentMove: ");
    Serial.println(_state.manualCoilsCurrentMove);
    Serial.print("manualCoilsCurrentHold: ");
    Serial.println(_state.manualCoilsCurrentHold);
    Serial.print("manualCoilsIdleTimeoutMs: ");
    Serial.println(_state.manualCoilsIdleTimeoutMs);
    Serial.println("---------------------");
}

unsigned int EEPROM_AF2::getPosition()
{
    return _state.position;
}
void EEPROM_AF2::setPosition(unsigned int value)
{
    if (value > _state.maxPosition)
    {
        value = _state.maxPosition;
    }

    _isDirty = true;
    _state.position = value;
}
void EEPROM_AF2::syncPosition(unsigned int value)
{
    if (value > _state.maxPosition)
    {
        value = _state.maxPosition;
    }

    _isDirty = true;
    _state.targetPosition = value;
    _state.position = value;
    _nextWriteDelayMs = 0;
}
unsigned int EEPROM_AF2::getTargetPosition()
{
    return _state.targetPosition;
}
bool EEPROM_AF2::setTargetPosition(unsigned int value)
{
    if ((unsigned int)abs((int)(_state.position - (int)value)) > _state.maxMovement)
    {
        return false;
    }

    if (value > _state.maxPosition)
    {
        value = _state.maxPosition;
    }

    _isDirty = true;
    _state.targetPosition = value;
    return true;
}
unsigned int EEPROM_AF2::getMaxPosition()
{
    return _state.maxPosition;
}
void EEPROM_AF2::setMaxPosition(unsigned int value)
{
    if (value < 10000)
        value = 10000;

    if (_state.targetPosition > value)
        _state.targetPosition = value;

    if (_state.position > value)
        _state.position = value;

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.maxPosition = value;
}
unsigned int EEPROM_AF2::getMaxMovement()
{
    return _state.maxMovement;
}
void EEPROM_AF2::setMaxMovement(unsigned int value)
{
    if (value < 1000)
        value = 1000;

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.maxMovement = value;
}
unsigned short EEPROM_AF2::getStepMode()
{
    return _state.stepMode;
}
void EEPROM_AF2::setStepMode(unsigned short value)
{
    if (value != (unsigned short)STEP_MODE::FULL && value != (unsigned short)STEP_MODE::HALF && value != (unsigned short)STEP_MODE::QUARTER && value != (unsigned short)STEP_MODE::EIGHT)
    {
        return;
    }

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.stepMode = value;
}
unsigned short EEPROM_AF2::getSpeedMode()
{
    return _state.speedMode;
}
void EEPROM_AF2::setSpeedMode(unsigned short value)
{
    if (value != (unsigned short)SPEED_MODE::SLOW && value != (unsigned short)SPEED_MODE::MEDIUM && value != (unsigned short)SPEED_MODE::FAST)
    {
        return;
    }

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.speedMode = value;
}
unsigned int EEPROM_AF2::getSettleBufferMs()
{
    return _state.settleBufferMs;
}
void EEPROM_AF2::setSettleBufferMs(unsigned int value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.settleBufferMs = value;
}
bool EEPROM_AF2::getIsManualControl()
{
    return _state.isManualControl;
}
void EEPROM_AF2::setIsManualControl(bool value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.isManualControl = value;
}
unsigned short EEPROM_AF2::getWifiMode() {
    return _state.wifiMode;
}
void EEPROM_AF2::setWifiMode(unsigned short value) {
    if (value != (unsigned short)WIFI_MODE::OFF && value != (unsigned short)WIFI_MODE::AP && value != (unsigned short)WIFI_MODE::STA  && value != (unsigned short)WIFI_MODE::AP_STA)
    {
        return;
    }

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.wifiMode = value;
}
char* EEPROM_AF2::getWifiPassword() {
    return _state.wifiAPPassword;
}
void EEPROM_AF2::setWifiPassword(char* value) {
    _isDirty = true;
    _nextWriteDelayMs = 0;
    strcpy(_state.wifiAPPassword, value);
}
bool EEPROM_AF2::getReverseDirection()
{
    return _state.reverseDirection;
}
void EEPROM_AF2::setReverseDirection(bool value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.reverseDirection = value;
}
unsigned int EEPROM_AF2::getEepromWriteTimeoutMs()
{
    return _state.eepromWriteTimeoutMs;
}
void EEPROM_AF2::setEepromWriteTimeoutMs(unsigned int value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.eepromWriteTimeoutMs = value;
}
unsigned short EEPROM_AF2::getCoilsMode()
{
    return _state.coilsMode;
}
void EEPROM_AF2::setCoilsMode(unsigned short value)
{
    if (value != (unsigned short)COILS_MODE::IDLE_OFF && value != (unsigned short)COILS_MODE::ALWAYS_ON && value != (unsigned short)COILS_MODE::IDLE_TIMEOUT_OFF)
        return;

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.coilsMode = value;
}
unsigned int EEPROM_AF2::getCoilsIdleTimeoutMs()
{
    return _state.coilsIdleTimeoutMs;
}
void EEPROM_AF2::setCoilsIdleTimeoutMs(unsigned int value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.coilsIdleTimeoutMs = value;
}
unsigned short EEPROM_AF2::getCoilsCurrentMove()
{
    return _state.coilsCurrentMove;
}
void EEPROM_AF2::setCoilsCurrentMove(unsigned short value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.coilsCurrentMove = value;
}
unsigned short EEPROM_AF2::getCoilsCurrentHold()
{
    return _state.coilsCurrentHold;
}
void EEPROM_AF2::setCoilsCurrentHold(unsigned short value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.coilsCurrentHold = value;
}
unsigned short EEPROM_AF2::getManualStepMode()
{
    return _state.manualStepMode;
}
void EEPROM_AF2::setManualStepMode(unsigned short value)
{
    if (value != (unsigned short)STEP_MODE::FULL && value != (unsigned short)STEP_MODE::HALF && value != (unsigned short)STEP_MODE::QUARTER && value != (unsigned short)STEP_MODE::EIGHT)
    {
        return;
    }

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualStepMode = value;
}
unsigned short EEPROM_AF2::getManualSpeedMode()
{
    return _state.manualSpeedMode;
}
void EEPROM_AF2::setManualSpeedMode(unsigned short value)
{
    if (value != (unsigned short)SPEED_MODE::SLOW && value != (unsigned short)SPEED_MODE::MEDIUM && value != (unsigned short)SPEED_MODE::FAST)
    {
        return;
    }

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualSpeedMode = value;
}
bool EEPROM_AF2::getManualReverseDirection()
{
    return _state.manualReverseDirection;
}
void EEPROM_AF2::setManualReverseDirection(bool value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualReverseDirection = value;
}
unsigned short EEPROM_AF2::getManualStepSize()
{
    return _state.manualStepSize;
}
void EEPROM_AF2::setManualStepSize(unsigned short value)
{
    if (value != (unsigned short)MANUAL_STEP_SIZE::FINE && value != (unsigned short)MANUAL_STEP_SIZE::COARSE)
    {
        return;
    }

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualStepSize = value;
}
unsigned int EEPROM_AF2::getManualFineMoveSteps()
{
    return _state.manualFineMoveSteps;
}
void EEPROM_AF2::setManualFineMoveSteps(unsigned int value)
{
    if (value == 0)
        value = value;
    else if (value > _state.maxMovement)
        value = _state.maxMovement;

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualFineMoveSteps = value;
}
unsigned int EEPROM_AF2::getManualCoarseMoveSteps()
{
    return _state.manualCoarseMoveSteps;
}
void EEPROM_AF2::setManualCoarseMoveSteps(unsigned int value)
{
    if (value == 0)
        value = value;
    else if (value > _state.maxMovement)
        value = _state.maxMovement;

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualCoarseMoveSteps = value;
}
unsigned short EEPROM_AF2::getManualCoilsMode()
{
    return _state.manualCoilsMode;
}
void EEPROM_AF2::setManualCoilsMode(unsigned short value)
{
    if (value != (unsigned short)COILS_MODE::IDLE_OFF && value != (unsigned short)COILS_MODE::ALWAYS_ON && value != (unsigned short)COILS_MODE::IDLE_TIMEOUT_OFF)
        return;

    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualCoilsMode = value;
}
unsigned int EEPROM_AF2::getManualCoilsIdleTimeoutMs()
{
    return _state.manualCoilsIdleTimeoutMs;
}
void EEPROM_AF2::setManualCoilsIdleTimeoutMs(unsigned int value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualCoilsIdleTimeoutMs = value;
}
unsigned short EEPROM_AF2::getManualCoilsCurrentMove()
{
    return _state.manualCoilsCurrentMove;
}
void EEPROM_AF2::setManualCoilsCurrentMove(unsigned short value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualCoilsCurrentMove = value;
}
unsigned short EEPROM_AF2::getManualCoilsCurrentHold()
{
    return _state.manualCoilsCurrentHold;
}
void EEPROM_AF2::setManualCoilsCurrentHold(unsigned short value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.manualCoilsCurrentHold = value;
}
unsigned long EEPROM_AF2::getChecksum()
{
    return _state.checksum;
}
void EEPROM_AF2::setChecksum(unsigned long value)
{
    _isDirty = true;
    _nextWriteDelayMs = 0;
    _state.checksum = value;
}