#ifndef __SKETCH__
#define __SKETCH__

// calibrate a pid controller for a simulated system

#include "ArduinoSketch.h"

#include "mainController/PIDController.h"
#include "../util/Timer.h"


class __PidOfflineTest : public ArduinoSketch
{
    float desired;

    float x;
    float v;
    float a;

    float noiseMagnitude;
    float noise;

    float bias;
    Timer biasTimer;

    float u;

    PIDController controller;
    PIDGains gains;

    Timer dtTimer;
    Timer continuousTimer;

    Timer printTimer;

    public:
    __PidOfflineTest() = default;

    void setup()
    {
        gains.kp = 1.0;
        gains.ki = 0.5;
        gains.kd = 1.0;

        gains.maxIntegrator = 1.0;
        gains.maxControl = 0.6;

        gains.alphaDerivative = 0.1;
        gains.derivativeTime = 0.01;

        bias = -0.5;
        biasTimer.set(5.0);
        noiseMagnitude = 0.1;

        controller = PIDController(gains);

        dtTimer.set(0.001);

        printTimer.set(0.01);
    }

    void loop()
    {
        if (dtTimer.isRinging())
        {
            float dt = dtTimer.dt();
            dtTimer.restart();
            // float t = continuousTimer.dt();

            desired = 1.0;
            // desired = sin(2 * pi * t)
            // Serial.println(dt, 5);

            simulateDynamics(dt);
            doControl(dt);
        }

        if (printTimer.isRinging())
        {
            printTimer.restart();
            Serial.print(x + noise); Serial.print(",");
            Serial.print(desired); Serial.print(",");
            Serial.print(u); Serial.print(",");
            Serial.print(bias);
            Serial.println();
        }

    }

    void simulateDynamics(float dt)
    {
        if (biasTimer.isRinging())
        {
            bias = 0;
            biasTimer.stopRinging();
        }
        noise = noiseMagnitude * random(-1.0, 1.0);
        a = u + bias;
        v += a * dt;
        x += v * dt;
    }

    void doControl(float dt)
    {
        u = controller.stepAndGet(x + noise, desired, dt);
    }

};


#endif