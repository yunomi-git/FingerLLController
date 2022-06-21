#ifndef __ANGLESENSOR__
#define __ANGLESENSOR__

#include "Timer.h"
#include "AlphaFilter.h"

class AngleSensor
{
    private:
    float angle;
    float velocity;
    AlphaFilter<float> filteredVelocity;

    public:
    AngleSensor() 
    {

    }

    void setAlphaFilterValue(float alpha)
    {
        filteredVelocity.setAlpha(alpha);
    }

    void read(float dt)
    {
        updateHardwareReading(dt);

        angle = getHardwareAngleDeg();
        velocity = getHardwareVelocityDegSec();

        filteredVelocity.update(velocity);
    }

    public:
    virtual void hardwareSetup() = 0;

    protected: 
    virtual float getHardwareAngleDeg() = 0;
    virtual float getHardwareVelocityDegSec()=0;
    virtual void updateHardwareReading(float dt) = 0;

    public:
    float getAngleDeg()
    {
        return angle;
    }

    float getVelocityDegSec()
    {
        return filteredVelocity.getFilteredData();
    }
};

#endif