#ifndef __SKETCH__
#define __SKETCH__

#include "ArduinoSketch.h"

#include "mainController/PIDController.h"

#include "hardware/PT15AngleSensor.h"
#include "hardware/PT15SeriesElasticSensor.h"
#include "hardware/L298NMotorDriver.h"

#include "mainController/hardwareInterface/HardwareParameters.h"

#include "packets/SensorData.h"
#include "packets/ControlMode.h"
#include "mainController/hardwareInterface/VoltageCommand.h"


#include "../externalInterface/ArduinoCommandInterface.h"

#include "../util/Timer.h"


class __PidOfflineTest : public ArduinoSketch
{
    bool calibratingProximalJoint = true;
    ControlMode controlMode = ControlMode::POSITION;

    ArduinoInputCommand inputReader;

    HardwareParameters hp;

    PT15AngleSensor angleSensor;
    PT15SeriesElasticSensor torqueSensor;
    L298NMotorDriver motorDriver;

    PIDController controller;
    PIDGains gains;

    float desired;
    float measured;
    float control;

    Timer dtTimer;

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

        inputReader = ArduinoInputCommand(controlMode, hp.POT_1_READ_PIN, hp.POT_2_READ_PIN, hp);

        hp = HardwareParameters();
        HardwareParameters::SensorParameters sp = hp.sensorParameters;

        controller = PIDController(gains);

        dtTimer.set(0.001);

        printTimer.set(0.01);

        if (calibratingProximalJoint)
        {
            motorDriver = L298NMotorDriver(hp.MOTOR_VOLTAGE, hp.motorDriver1.ENA_PIN, hp.motorDriver1.DIR1_PIN, hp.motorDriver1.DIR2_PIN, hp.motorDriver1.flipDirection);
            angleSensor = PT15AngleSensor(sp.angle1.READ_PIN, sp.angle1.ZERO, sp.velocityReadTick, sp.angleAlphaFilter, sp.velocityAlphaFilter);
            torqueSensor = PT15SeriesElasticSensor(sp.torque1.READ_PIN, sp.torque1.SCALE, sp.torque1.RAW_OFFSET, sp.torque1.DEADBAND, sp.torque1.flipDirection);
        }
        else
        {
            motorDriver = L298NMotorDriver(hp.MOTOR_VOLTAGE, hp.motorDriver2.ENA_PIN, hp.motorDriver2.DIR1_PIN, hp.motorDriver2.DIR2_PIN, hp.motorDriver2.flipDirection);
            angleSensor = PT15AngleSensor(sp.angle2.READ_PIN, sp.angle2.ZERO, sp.velocityReadTick, sp.angleAlphaFilter, sp.velocityAlphaFilter);
            torqueSensor = PT15SeriesElasticSensor(sp.torque2.READ_PIN, sp.torque2.SCALE, sp.torque2.RAW_OFFSET, sp.torque2.DEADBAND, sp.torque2.flipDirection);
        }

    }

    void loop()
    {
        if (dtTimer.isRinging())
        {
            float dt = dtTimer.dt();
            dtTimer.restart();

            // get desired
            JointSpaceCommand jointSpaceCommand = inputReader.recieve();
            desired = jointSpaceCommand.input1;

            // get measurement
            if (controlMode == ControlMode::POSITION)
            {
                angleSensor.read(dt);
                measured = angleSensor.getAngleDeg();   
            }
            else
            {
                torqueSensor.read(dt);
                measured = torqueSensor.getTorqueNm();
            }

            // get control
            control = controller.stepAndGet(measured, desired, dt);

            // send to motor
            motorDriver.submitVoltage(control);
            motorDriver.write();
        }

        if (printTimer.isRinging())
        {
            printTimer.restart();
            Serial.print(desired); Serial.print(",");
            Serial.print(measured); Serial.print(",");
            Serial.print(control);
            Serial.println();
        }

    }



};


#endif