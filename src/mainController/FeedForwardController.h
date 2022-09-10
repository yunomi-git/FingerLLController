#ifndef __FFCONTROL__
#define __FFCONTROL__

#include "PIDController.h"

class FeedForwardController
{
private:
    PIDController pidController;
    float feedForward;
    PIDGains pidGains;
    bool doResetIntegrator;

    float lastControl = 1.0;

public:
    FeedForwardController() = default;

    FeedForwardController(float feedForward, PIDGains pidGains, bool doResetIntegrator)
    {
        this->feedForward = feedForward;
        this->doResetIntegrator = doResetIntegrator;
        this->pidGains = pidGains;
        pidController = PIDController(pidGains);
    }

    void resetIntegrator()
    {
        pidController.resetIntegrator();
    }

    float stepAndGet(float measured, float desired, float dt)
    {
        float control = pidController.stepAndGet(measured, desired, dt);
        if (control > 0)
        {
            if (lastControl < 0 && doResetIntegrator)
            {
                pidController.resetIntegrator();
            }
            lastControl = 1.0;
            control += feedForward;
        }
        else
        {
            if (lastControl > 0 && doResetIntegrator)
            {
                pidController.resetIntegrator();
            }
            lastControl = -1.0;
            control -= feedForward;
        }
        control = fbound(control, -pidGains.maxControl, pidGains.maxControl);
        return control;
    }
};

#endif