#ifndef __POSITIONTENSIONCONTROL__
#define __POSITIONTENSIONCONTROL__

#include "mainController/PIDController.h"
#include "mainController/FeedForwardController.h"
#include "util/Direction.h"

class PositionTensionController
{
private:
    FeedForwardController positionController;
    FeedForwardController torqueController;
    float minimumTorque;
    float hysteresisSize;
    Direction lastDirection = POSITIVE_DIRECTION;

    bool inPullingMode = true;

public:
    PositionTensionController() = default;

    PositionTensionController(float feedForward, float hysteresisSize, float minimumTorque, PIDGains pidGains, FeedForwardController &torqueController, bool doResetIntegrator)
    {
        positionController = FeedForwardController(feedForward, pidGains, doResetIntegrator);
        this->torqueController = torqueController;
        this->hysteresisSize = hysteresisSize;
        this->minimumTorque = minimumTorque;
    }

    float stepAndGet(float measuredTorque, float measuredPosition, float desiredPosition, float dt)
    {
        // if in pulling mode and time to switch to relax mode, switch
        // if in relax mode and time to switch to pulling mode, switch
        // if in pulling mode, pull
        // if in relax mode, relax
        switchModeIfApplicable(measuredPosition, desiredPosition);
        
        // Need to pull cable to get to correct position
        if (inPullingMode)
        {
            return positionController.stepAndGet(measuredPosition, desiredPosition, dt);
        }
        // Need to relax cable to get to correct position
        else
        {
            return torqueController.stepAndGet(measuredTorque, minimumTorque, dt);
        }
    }

private:

    void switchModeIfApplicable(float measuredPosition, float desiredPosition)
    {
        if (inPullingMode)
        {
            // measured too high -> need to relax
            if (measuredPosition > (desiredPosition + hysteresisSize))
                switchMode();
        }
        else
        {
            // measured too low -> need to pull
            if (measuredPosition < (desiredPosition +- hysteresisSize))
                switchMode();
        }
    }

    void switchMode()
    {
        inPullingMode = !inPullingMode;
        positionController.resetIntegrator();
        torqueController.resetIntegrator();
    }



};

#endif