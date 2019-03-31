#include <Arduino.h>
#include "Motor_AF2.h"

void Motor_AF2::_writeCoilsMode()
{
    //Serial.println(_eeprom->getIsManualControl());
    if (isMoving())
        return;

    unsigned short coilsMode = _eeprom->getIsManualControl() ? _eeprom->getManualCoilsMode() : _eeprom->getCoilsMode();
    unsigned int holdCurrent = _eeprom->getIsManualControl() ? _eeprom->getManualCoilsCurrentHold() : _eeprom->getCoilsCurrentHold();
    unsigned int timeoutMs = _eeprom->getIsManualControl() ? _eeprom->getManualCoilsIdleTimeoutMs() : _eeprom->getCoilsIdleTimeoutMs();

    if (coilsMode == (unsigned short)COILS_MODE::IDLE_OFF)
    {
        //Serial.println("off");
        digitalWrite(MP6500_PIN_SLP, LOW);
        _coilsOn = false;
    }
    //Always on
    else if (coilsMode == (unsigned short)COILS_MODE::ALWAYS_ON)
    {
        //Serial.println("Always on");
        digitalWrite(MP6500_PIN_SLP, HIGH);
        ledcWrite(MP6500_PIN_I1_CHANNEL, holdCurrent);
        _coilsOn = true;
    }
    //Idle - coils timeout (ms)
    else if (coilsMode == (unsigned short)COILS_MODE::IDLE_TIMEOUT_OFF)
    {
        //Serial.println("Timeout");
        if ((millis() - _lastStopMs) <= timeoutMs)
        {
            digitalWrite(MP6500_PIN_SLP, HIGH);
            ledcWrite(MP6500_PIN_I1_CHANNEL, holdCurrent);
            _coilsOn = true;
        }
        else
        {
            digitalWrite(MP6500_PIN_SLP, LOW);
            _coilsOn = false;
        }
    }
}

void Motor_AF2::_writeStepMode(unsigned short stepMode)
{
    switch (stepMode)
    {
        case (unsigned short)STEP_MODE::FULL:
            digitalWrite(MP6500_PIN_MS1, 0);
            digitalWrite(MP6500_PIN_MS2, 0);
            break;
        case (unsigned short)STEP_MODE::HALF:
            digitalWrite(MP6500_PIN_MS1, 1);
            digitalWrite(MP6500_PIN_MS2, 0);
            break;
        case (unsigned short)STEP_MODE::QUARTER:
            digitalWrite(MP6500_PIN_MS1, 0);
            digitalWrite(MP6500_PIN_MS2, 1);
            break;
        case (unsigned short)STEP_MODE::EIGHT:
            digitalWrite(MP6500_PIN_MS1, 1);
            digitalWrite(MP6500_PIN_MS2, 1);
            break;
        default: // half step by default
            digitalWrite(MP6500_PIN_MS1, 1);
            digitalWrite(MP6500_PIN_MS2, 0);
            break;
    }
}

void Motor_AF2::init(EEPROM_AF2 &eeprom)
{
    pinMode(MP6500_PIN_DIR, OUTPUT);
    pinMode(MP6500_PIN_STEP, OUTPUT);
    pinMode(MP6500_PIN_MS1, OUTPUT);
    pinMode(MP6500_PIN_MS2, OUTPUT);
    pinMode(MP6500_PIN_SLP, OUTPUT);
    pinMode(MP6500_PIN_EN, OUTPUT);

    digitalWrite(MP6500_PIN_EN, LOW);
    ledcAttachPin(MP6500_PIN_I1, 1);
    // Initialize channels
    // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
    // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
    ledcSetup(1, 64000, 12); // 12 kHz PWM, 12-bit resolution
                             // set direction and step to low
    digitalWrite(MP6500_PIN_DIR, LOW);
    digitalWrite(MP6500_PIN_STEP, LOW);
    digitalWrite(MP6500_PIN_SLP, LOW);

    _eeprom = &eeprom;
    _writeStepMode(_eeprom->getStepMode());
    _writeCoilsMode();
}

//GENERAL
void Motor_AF2::handleMove()
{
    if (_movementStatus != MOVEMENT_STATUS::STOP)
    {
        digitalWrite(MP6500_PIN_SLP, HIGH);
        ledcWrite(MP6500_PIN_I1_CHANNEL, _eeprom->getIsManualControl() ? _eeprom->getManualCoilsCurrentMove() : _eeprom->getCoilsCurrentMove());
        unsigned short sm = _eeprom->getIsManualControl() ? _eeprom->getManualStepMode() : _eeprom->getStepMode();
        bool reverseDirection = _eeprom->getIsManualControl() ? _eeprom->getManualReverseDirection() : _eeprom->getReverseDirection();
        unsigned int speedFactor = 1;
        switch (_eeprom->getIsManualControl() ? _eeprom->getManualSpeedMode() : _eeprom->getSpeedMode())
        {
        case (unsigned short)SPEED_MODE::SLOW:
            speedFactor = 30;
            break;
        case (unsigned short)SPEED_MODE::MEDIUM:
            speedFactor = 12;
            break;
        case (unsigned short)SPEED_MODE::FAST:
            speedFactor = 1;
            break;
        }

        if (_eeprom->getTargetPosition() < _eeprom->getPosition())
        {
            digitalWrite(MP6500_PIN_DIR, reverseDirection ? LOW : HIGH);
            while (_eeprom->getPosition() != _eeprom->getTargetPosition())
            {
                digitalWrite(MP6500_PIN_STEP, 1);
                delayMicroseconds(1);
                digitalWrite(MP6500_PIN_STEP, 0);
                _eeprom->setPosition(_eeprom->getPosition() - 1);
                delayMicroseconds(speedFactor * (1600 / sm));

                if (_movementStatus == MOVEMENT_STATUS::MOVING_MANUAL_CONTINUOUS)
                    _eeprom->setTargetPosition(_eeprom->getTargetPosition() - 2);
            }
        }
        else if (_eeprom->getTargetPosition() > _eeprom->getPosition())
        {
            digitalWrite(MP6500_PIN_DIR, reverseDirection ? HIGH : LOW);
            while (_eeprom->getPosition() != _eeprom->getTargetPosition())
            {
                digitalWrite(MP6500_PIN_STEP, 1);
                delayMicroseconds(1);
                digitalWrite(MP6500_PIN_STEP, 0);
                _eeprom->setPosition(_eeprom->getPosition() + 1);
                delayMicroseconds(speedFactor * (1600 / sm));

                if (_movementStatus == MOVEMENT_STATUS::MOVING_MANUAL_CONTINUOUS)
                    _eeprom->setTargetPosition(_eeprom->getTargetPosition() + 2);
            }
        }

        stop();
    }
    else
    {
        unsigned short coilsMode = _eeprom->getIsManualControl() ? _eeprom->getManualCoilsMode() : _eeprom->getCoilsMode();
        if (_coilsOn && coilsMode == (unsigned short)COILS_MODE::IDLE_TIMEOUT_OFF)
        {
            //auto-off coils after timeout
            unsigned int timeoutMs = _eeprom->getIsManualControl() ? _eeprom->getManualCoilsIdleTimeoutMs() : _eeprom->getCoilsIdleTimeoutMs();
            if ((millis() - _lastStopMs) > timeoutMs)
            {
                _writeCoilsMode();
            }
        }
    }
}

void Motor_AF2::stop()
{
    if (_movementStatus != MOVEMENT_STATUS::STOP)
    {
        _movementStatus = MOVEMENT_STATUS::STOP;
        _eeprom->setTargetPosition(_eeprom->getPosition());
        _lastStopMs = millis();
        _settled = _eeprom->getSettleBufferMs() == 0;
        _writeCoilsMode();
    }
}

bool Motor_AF2::isMoving()
{
    if (_movementStatus != MOVEMENT_STATUS::STOP)
    {
        return true;
    }
    else
    {
        /*
            if your focuser has any play, this can affect the autofocuser performance. SGP for example goes aways from current position and
            than starts traversing back. When it changes focus direction (traverse back), focuser play can cause FOV to wiggle just a bit,
            which causes enlongated stars on the next exposure. Settle buffer option returns IsMoving as TRUE after focuser reaches target position,
            letting it to settle a bit. Advices by Jared Wellman of SGP.
        */
        if (!_settled)
        {
            if ((millis() - _lastStopMs) > _eeprom->getSettleBufferMs())
            {
                _settled = true;
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
}

MOVEMENT_STATUS Motor_AF2::getMovementStatus()
{
    return _movementStatus;
}

void Motor_AF2::resetToDefaults() {
    _writeStepMode(_eeprom->getStepMode());
    _writeCoilsMode();
}

//EXTERNAL (ASCOM or INDI via Serial/Wifi)

void Motor_AF2::move()
{
    if (_eeprom->getTargetPosition() == _eeprom->getPosition())
        return;

    _writeStepMode(_eeprom->getStepMode());
    digitalWrite(MP6500_PIN_SLP, HIGH);
    ledcWrite(MP6500_PIN_I1_CHANNEL, _eeprom->getCoilsCurrentMove());

    /*
      When waking up from sleep mode,
      approximately 1ms of time must pass before a
      STEP command can be issued to allow the
      internal circuitry to stabilize.
    */
    delayMicroseconds(1000);

    _movementStatus = MOVEMENT_STATUS::MOVING;
    _eeprom->setIsManualControl(false);

    _eeprom->delayEepromWrite();
}

void Motor_AF2::setCoilsMode(unsigned short mode)
{
    _eeprom->setIsManualControl(false);
    _eeprom->setCoilsMode(mode);
    _writeCoilsMode();
}

int Motor_AF2::getMoveCurrentPercent()
{
    return (int)((float)MP6500_PIN_I1_MOVE_MAX - (float)_eeprom->getCoilsCurrentMove()) / (float)MP6500_PIN_I1_MOVE_RANGE * 100;
}

void Motor_AF2::setMoveCurrentPercent(float percent)
{
    percent = percent / 100.0;
    _eeprom->setCoilsCurrentMove((unsigned short)MP6500_PIN_I1_MOVE_MAX - MP6500_PIN_I1_MOVE_RANGE * percent);
}

void Motor_AF2::setMoveCurrent(unsigned int value)
{
    _eeprom->setIsManualControl(false);
    if (value > MP6500_PIN_I1_MOVE_MAX)
        value = MP6500_PIN_I1_MOVE_MAX;
    else if (value < MP6500_PIN_I1_MOVE_MIN)
        value = MP6500_PIN_I1_MOVE_MIN;

    _eeprom->setCoilsCurrentMove(value);
    _writeCoilsMode();
}

int Motor_AF2::getHoldCurrentPercent()
{
    return (int)((float)MP6500_PIN_I1_HOLD_MAX - (float)_eeprom->getCoilsCurrentHold()) / (float)MP6500_PIN_I1_HOLD_RANGE * 100;
}

void Motor_AF2::setHoldCurrentPercent(float percent)
{
    percent = percent / 100.0;
    _eeprom->setCoilsCurrentHold((unsigned short)(MP6500_PIN_I1_HOLD_MAX - MP6500_PIN_I1_HOLD_RANGE * percent));
    _writeCoilsMode();
}

void Motor_AF2::setHoldCurrent(unsigned int value)
{
    _eeprom->setIsManualControl(false);
    if (value > MP6500_PIN_I1_HOLD_MAX)
        value = MP6500_PIN_I1_HOLD_MAX;
    else if (value < MP6500_PIN_I1_HOLD_MIN)
        value = MP6500_PIN_I1_HOLD_MIN;

    _eeprom->setCoilsCurrentHold(value);
    _writeCoilsMode();
}

//MANUAL MOVEMENT

void Motor_AF2::moveManual()
{
    if (_eeprom->getTargetPosition() == _eeprom->getPosition())
        return;

    _writeStepMode(_eeprom->getManualStepMode());
    digitalWrite(MP6500_PIN_SLP, HIGH);
    ledcWrite(MP6500_PIN_I1_CHANNEL, _eeprom->getManualCoilsCurrentMove());

    /*
      When waking up from sleep mode,
      approximately 1ms of time must pass before a
      STEP command can be issued to allow the
      internal circuitry to stabilize.
    */
    delayMicroseconds(1000);

    _movementStatus = MOVEMENT_STATUS::MOVING_MANUAL;
    _eeprom->setIsManualControl(true);

    _eeprom->delayEepromWrite();
}

void Motor_AF2::moveManual(MOVEMENT_MANUAL_DIR dir)
{
    _eeprom->setIsManualControl(true);
    int diff = _eeprom->getManualFineMoveSteps();
    if (_eeprom->getManualStepSize() == (unsigned short)MANUAL_STEP_SIZE::COARSE)
    {
        diff = _eeprom->getManualCoarseMoveSteps();
    }

    if (dir == MOVEMENT_MANUAL_DIR::CW)
        _eeprom->setTargetPosition(_eeprom->getPosition() + diff);
    else
    {
        if (diff > _eeprom->getPosition())
            _eeprom->setTargetPosition(0);
        else
            _eeprom->setTargetPosition(_eeprom->getPosition() - diff);
    }

    if (_eeprom->getTargetPosition() == _eeprom->getPosition())
        return;

    //Serial.println(_eeprom->getPosition());
    //Serial.println(_eeprom->getTargetPosition());

    _writeStepMode(_eeprom->getManualStepMode());
    digitalWrite(MP6500_PIN_SLP, HIGH);
    ledcWrite(MP6500_PIN_I1_CHANNEL, _eeprom->getManualCoilsCurrentMove());

    /*
      When waking up from sleep mode,
      approximately 1ms of time must pass before a
      STEP command can be issued to allow the
      internal circuitry to stabilize.
    */
    delayMicroseconds(1000);

    _movementStatus = MOVEMENT_STATUS::MOVING_MANUAL;

    _eeprom->delayEepromWrite();
}

void Motor_AF2::moveManualContinuous(MOVEMENT_MANUAL_DIR dir)
{
    _eeprom->setIsManualControl(true);

    _writeStepMode(_eeprom->getManualStepMode());
    digitalWrite(MP6500_PIN_SLP, HIGH);
    ledcWrite(MP6500_PIN_I1_CHANNEL, _eeprom->getManualCoilsCurrentMove());

    /*
      When waking up from sleep mode,
      approximately 1ms of time must pass before a
      STEP command can be issued to allow the
      internal circuitry to stabilize.
    */
    delayMicroseconds(1000);

    if (dir == MOVEMENT_MANUAL_DIR::CW)
    {
        _eeprom->setTargetPosition(_eeprom->getTargetPosition() + 1);
        _movementStatus = MOVEMENT_STATUS::MOVING_MANUAL_CONTINUOUS;
    }
    else
    {
        _eeprom->setTargetPosition(_eeprom->getTargetPosition() - 1);
        _movementStatus = MOVEMENT_STATUS::MOVING_MANUAL_CONTINUOUS;
    }
    _eeprom->delayEepromWrite();
}

void Motor_AF2::setManualCoilsMode(unsigned short mode)
{
    _eeprom->setIsManualControl(true);
    _eeprom->setManualCoilsMode(mode);
    _writeCoilsMode();
}

int Motor_AF2::getManualMoveCurrentPercent()
{
    return (int)((float)MP6500_PIN_I1_MOVE_MAX - (float)_eeprom->getManualCoilsCurrentMove()) / (float)MP6500_PIN_I1_MOVE_RANGE * 100;
}

void Motor_AF2::setManualMoveCurrentPercent(float percent)
{
    percent = percent / 100.0;
    _eeprom->setManualCoilsCurrentMove((unsigned short)MP6500_PIN_I1_MOVE_MAX - MP6500_PIN_I1_MOVE_RANGE * percent);
}

void Motor_AF2::setManualMoveCurrent(unsigned int value)
{
    _eeprom->setIsManualControl(true);
    if (value > MP6500_PIN_I1_MOVE_MAX)
        value = MP6500_PIN_I1_MOVE_MAX;
    else if (value < MP6500_PIN_I1_MOVE_MIN)
        value = MP6500_PIN_I1_MOVE_MIN;

    _eeprom->setManualCoilsCurrentMove(value);
    _writeCoilsMode();
}

int Motor_AF2::getManualHoldCurrentPercent()
{
    return (int)((float)MP6500_PIN_I1_HOLD_MAX - (float)_eeprom->getManualCoilsCurrentHold()) / (float)MP6500_PIN_I1_HOLD_RANGE * 100;
}

void Motor_AF2::setManualHoldCurrentPercent(float percent)
{
    percent = percent / 100.0;
    _eeprom->setManualCoilsCurrentHold((unsigned short)MP6500_PIN_I1_HOLD_MAX - MP6500_PIN_I1_HOLD_RANGE * percent);
    _writeCoilsMode();
}

void Motor_AF2::setManualHoldCurrent(unsigned int value)
{
    _eeprom->setIsManualControl(true);
    if (value > MP6500_PIN_I1_HOLD_MAX)
        value = MP6500_PIN_I1_HOLD_MAX;
    else if (value < MP6500_PIN_I1_HOLD_MIN)
        value = MP6500_PIN_I1_HOLD_MIN;

    _eeprom->setManualCoilsCurrentHold(value);
    _writeCoilsMode();
}