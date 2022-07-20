#ifndef __DERIVATIVE__
#define __DERIVATIVE__

#include "Timer.h"
#include "AlphaFilter.h"

class Derivative
{
    private:
    Timer timer;
    float lastMeasurement;
    float rawDerivative;
    AlphaFilter<float> derivativeFilter;

    public:
    Derivative() = default;
    
    Derivative(float maxTime, float alpha)
    {
        timer.usePrecision();
        timer.set(maxTime);
        derivativeFilter = AlphaFilter<float>(alpha);
    }

    void update(float measurement, float globalDt)
    {
        // if timer is ringing, dt = this timer
        // if timer is not ringing
        //      if measurement changed, use globalDt
        //      if no change, no update
        if (timer.isRinging())
        {
            float dt = timer.dt();
            timer.restart();
            rawDerivative = (measurement - lastMeasurement) / dt;
        }
        else if (measurement != lastMeasurement)
        {
            rawDerivative = (measurement - lastMeasurement) / globalDt;
        }
        derivativeFilter.update(rawDerivative);
    }

    float getDerivative()
    {
        return derivativeFilter.getFilteredData();
    }

    void setAlpha(float alpha)
    {
        derivativeFilter.setAlpha(alpha);
    }
};

#endif