#pragma once

#ifdef ARDUINO_TESTS
#include "ArduinoFake.h"
#else
#include "Arduino.h"
#endif

#ifndef CarMotor_h
#define CarMotor_h

class CarMotor
{
private:
    int directionPin1;
    int directionPin2;

public:
    CarMotor(int directionPin1, int directionPin2) {}

    void Drive(int speed);
    int isRun();
};

#endif