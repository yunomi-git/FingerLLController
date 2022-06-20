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
        this.filteredVelocity.setAlpha(alpha);
    }

    void updateReading(float dt)
    {
        updateHardwareReading(dt);

        this.angle = getHardwareAngleDeg();
        this.velocity = getHardwareVelocityDegSec();

        this.filteredVelocity.update(this.velocity);
    }

    protected: 
    virtual float getHardwareAngleDeg() = 0;
    virtual float getHardwareVelocityDegSec()=0;
    virtual float updateHardwareReading(float dt) = 0;

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