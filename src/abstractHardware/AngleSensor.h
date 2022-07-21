#ifndef __ANGLESENSOR__
#define __ANGLESENSOR__

#include "../util/AlphaFilter.h"
#include "Sensor.h"
#include "../util/Derivative.h"

class AngleSensor : public Sensor
{
    private:
    float angle;
    float velocity;
    Derivative angleDerivative;
    AlphaFilter<float> angleFilter;

    public:
    AngleSensor() 
    {
        
    }

    AngleSensor(float velocityTick, float angleAlpha=1.0, float velocityAlpha=1.0)
    {
        angleDerivative = Derivative(velocityTick, velocityAlpha);
        angleFilter = AlphaFilter<float>(angleAlpha);
    }

    void setAlphaFilterValue(float alpha)
    {
        
        angleDerivative.setAlpha(alpha);
    }

    void read(float dt)
    {
        updateHardwareReading(dt);

        angleFilter.update(getHardwareAngleDeg());
        angle = angleFilter.getFilteredData();
        angleDerivative.update(angle, dt);

        velocity = angleDerivative.getDerivative();
    }

    virtual void setZero(float zero); //TODO should this be virtual?

    public:
    virtual void hardwareSetup() = 0;
    virtual void printName()
    {
        Serial.println("Abstract Angle Sensor");
    }

    protected: 
    virtual float getHardwareAngleDeg() = 0;
    virtual void updateHardwareReading(float dt) = 0;

    public:
    float getAngleDeg()
    {
        return angle;
    }

    float getVelocityDegSec()
    {
        return velocity;
    }
};

#endif