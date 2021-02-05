#pragma once

#include "Arduino.h"

#ifndef CarMotor_h
#define CarMotor_h

class CarMotor
{
private:
    int directionPin1;
    int directionPin2;

public:
    CarMotor(int directionPin1, int directionPin2)
    {
        directionPin1 = directionPin1;
        directionPin2 = directionPin2;
    }

    void Drive(int speed);
    int isRun();
};

#endif