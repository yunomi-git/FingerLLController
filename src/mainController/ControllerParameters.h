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

        torque1Gains.kp = 40.0;
        torque1Gains.kd = 0.1;
        torque1Gains.ki = 30.0;
        torque1Gains.maxIntegrator = 5.5;
        torque1Gains.maxControl = 12.0;
        torque1Gains.alphaDerivative = 0.01;
        torque1Gains.derivativeTime = 0.01;

        torque2Gains.kp = 40.0;
        torque2Gains.kd = 0.1;
        torque2Gains.ki = 30.0;
        torque2Gains.maxIntegrator = 5.5;
        torque2Gains.maxControl = 12.0;
        torque2Gains.alphaDerivative = 0.01;
        torque2Gains.derivativeTime = 0.01;
    }
};
/* Greartisan Parameters
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

        torque1Gains.kp = 40.0;
        torque1Gains.kd = 0.1;
        torque1Gains.ki = 30.0;
        torque1Gains.maxIntegrator = 5.5;
        torque1Gains.maxControl = 12.0;
        torque1Gains.alphaDerivative = 0.01;
        torque1Gains.derivativeTime = 0.01;

        torque2Gains.kp = 40.0;
        torque2Gains.kd = 0.1;
        torque2Gains.ki = 30.0;
        torque2Gains.maxIntegrator = 5.5;
        torque2Gains.maxControl = 12.0;
        torque2Gains.alphaDerivative = 0.01;
        torque2Gains.derivativeTime = 0.01;
    }
*/
#endif

