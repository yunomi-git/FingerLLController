#ifndef __CONTROLPARAM__
#define __CONTROLPARAM__

#include "PIDController.h"

struct ControllerParameters
{
    PIDGains angle1Gains;
    PIDGains angle2Gains;
    PIDGains torque1Gains;
    PIDGains torque2Gains;

    ControllerParameters()
    {
        angle1Gains.kp = 1.0;
        angle1Gains.kd = 0.0;
        angle1Gains.ki = 0.0;
        angle1Gains.maxIntegrator = 0.0;

        angle2Gains.kp = 1.0;
        angle2Gains.kd = 0.0;
        angle2Gains.ki = 0.0;
        angle2Gains.maxIntegrator = 0.0;

        torque1Gains.kp = 1.0;
        torque1Gains.kd = 0.0;
        torque1Gains.maxIntegrator = 0.0;

        torque2Gains.kp = 1.0;
        torque2Gains.kd = 0.0;
        torque2Gains.ki = 0.0;
        torque2Gains.maxIntegrator = 0.0;
    }
};

#endif