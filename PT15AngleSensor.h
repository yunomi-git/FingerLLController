#ifndef __PT15Encoder__
#define __PT15Encoder__

#include "AngleSensor.h"
#include "Potentiometer.h"
#include "Timer.h"
#include "MathUtil.h"

class PT15AngleSensor : protected AngleSensor 
{
    private:
    Potentiometer potentiometer;
    // Timer velocityTimer;
    const MAX_ANGLE_DEG = 135.0;
    const MIN_ANGLE_DEG = -135.0;

    float angle = 0.0;
    float velocity = 0.0;
    float alpha = 1.0;

    public:
    PT15AngleSensor(byte readPin, float alpha=1.0)
    {
        self.readPin = readPin;
        self.alpha = alpha;
        // velocityTimer = Timer();
        // velocityTimer.usePrecision();
        // velocityTimer.restart();
    }

    void hardwareSetup()
    {
        potentiometer.hardwareSetup(self.readPin);
        setAlphaFilterValue(alpha);
    }

    private: 
    void updateHardwareReading(float dt)
    {
        float lastAngle = this.angle;
        float rawRead = potentiometer.getReadingNormalized();
        this.angle = ;

        // float dt = this.velocityTimer.dt();
        // this.velocityTimer.restart();
        this.velocity = (this.angle - lastAngle) / dt;
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