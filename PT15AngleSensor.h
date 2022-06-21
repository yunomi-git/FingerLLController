#ifndef __PT15Encoder__
#define __PT15Encoder__

#include "AngleSensor.h"
#include "Potentiometer.h"
#include "Timer.h"
#include "MathUtil.h"

class PT15AngleSensor : public AngleSensor 
{
    private:
    Potentiometer potentiometer;
    // Timer velocityTimer;
    static const float MAX_ANGLE_DEG = 135.0;
    static const float MIN_ANGLE_DEG = -135.0;

    float angle = 0.0;
    float velocity = 0.0;
    float alpha = 1.0;

    byte readPin;

    public:
    PT15AngleSensor() = default;
    
    PT15AngleSensor(byte readPin, float alpha=1.0)
    {
        this->readPin = readPin;
        this->alpha = alpha;
        // velocityTimer = Timer();
        // velocityTimer.usePrecision();
        // velocityTimer.restart();
    }

    void hardwareSetup()
    {
        potentiometer = Potentiometer(readPin);
        potentiometer.hardwareSetup();
        setAlphaFilterValue(alpha);
    }

    private: 
    void updateHardwareReading(float dt)
    {
        float lastAngle = angle;
        float rawRead = potentiometer.getReadingNormalized();
        angle = fmap(rawRead, 0.0, 1.0, MIN_ANGLE_DEG, MAX_ANGLE_DEG);

        // float dt = this.velocityTimer.dt();
        // this.velocityTimer.restart();
        velocity = (angle - lastAngle) / dt;
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