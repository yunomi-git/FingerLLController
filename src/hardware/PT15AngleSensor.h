#ifndef __PT15Encoder__
#define __PT15Encoder__

#include "../abstractHardware/AngleSensor.h"

#include "Potentiometer.h"

#include "../util/Timer.h"
#include "../util/MathUtil.h"

class PT15AngleSensor : public AngleSensor 
{
    private:
    Potentiometer potentiometer;
    // Timer velocityTimer;
    float MAX_ANGLE_DEG = 135.0;
    float MIN_ANGLE_DEG = -135.0;

    float angle = 0.0;
    float velocity = 0.0;
    float lastAngle = 0.0;
    float alpha = 1.0;

    byte readPin;

    public:
    PT15AngleSensor() = default;
    
    PT15AngleSensor(byte readPin, float alpha=1.0)
    {
        this->readPin = readPin;
        this->alpha = alpha;
        potentiometer = Potentiometer(readPin);
    }

    void hardwareSetup()
    {
        potentiometer.hardwareSetup();
        setAlphaFilterValue(alpha);
    }

    private: 
    void updateHardwareReading(float dt)
    {
        float rawRead = potentiometer.getReadingNormalized();
        angle = fmap(rawRead, 0.0, 1.0, MIN_ANGLE_DEG, MAX_ANGLE_DEG);
        velocity = (angle - lastAngle) / dt; // TODO this reading is buggy
        lastAngle = angle;
    }

    float getHardwareAngleDeg()
    {
        return angle;
    }

    float getHardwareVelocityDegSec()
    {
        return velocity;
    }

    float convertRawReadToDegrees(float rawRead)
    {
        return fmap(rawRead, 0.0, 1.0, MIN_ANGLE_DEG, MAX_ANGLE_DEG);
    }
};

#endif