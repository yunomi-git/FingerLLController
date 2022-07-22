#ifndef __PT15Encoder__
#define __PT15Encoder__

#include "../abstractHardware/AngleSensor.h"

#include "Potentiometer.h"

#include "../util/Timer.h"
#include "../util/MathUtil.h"
#include "../util/Derivative.h"


class PT15AngleSensor : public AngleSensor 
{
    private:
    Potentiometer potentiometer;
    float MAX_ANGLE_DEG = 135.0;
    float MIN_ANGLE_DEG = -135.0;

    float angle = 0.0;
    float velocity = 0.0;
    float alpha = 1.0;
    float zero = 0.0;

    byte readPin;

    public:
    PT15AngleSensor() = default;
    
    PT15AngleSensor(byte readPin, float zero, float velocityTick, float angleAlpha=1.0, float velocityAlpha=1.0) : AngleSensor(velocityTick, angleAlpha, velocityAlpha)
    {
        this->readPin = readPin;
        setZero(zero);
        // this->alpha = alpha;
        potentiometer = Potentiometer(readPin);
    }

    void hardwareSetup()
    {
        // Serial.println("angle setup");
        potentiometer.hardwareSetup();
        // setAlphaFilterValue(alpha);
    }

    void printName()
    {
        Serial.println("PT15AngleSensor");
    }

    void setZero(float zero)
    {
        this->zero = zero;
    }

    private: 
    void updateHardwareReading(float dt)
    {
        float rawRead = potentiometer.getReadingNormalized();
        angle = fmap(rawRead, 0.0, 1.0, MIN_ANGLE_DEG, MAX_ANGLE_DEG) - zero;
    }

    float getHardwareAngleDeg()
    {
        return angle;
    }

    float convertRawReadToDegrees(float rawRead)
    {
        return fmap(rawRead, 0.0, 1.0, MIN_ANGLE_DEG, MAX_ANGLE_DEG);
    }
};

#endif