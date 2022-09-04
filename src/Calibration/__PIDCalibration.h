#ifndef __SKETCH__
#define __SKETCH__

#include "ArduinoSketch.h"

#include "mainController/PIDController.h"
#include "mainController/FeedForwardController.h"
#include "mainController/PositionTensionController.h"

#include "hardware/PT15AngleSensor.h"
#include "hardware/PT15SeriesElasticSensor.h"
#include "hardware/L298NMotorDriver.h"

#include "mainController/hardwareInterface/HardwareParameters.h"

#include "packets/SensorData.h"
#include "packets/ControlMode.h"
#include "mainController/hardwareInterface/VoltageCommand.h"


#include "../externalInterface/ArduinoCommandInterface.h"

#include "../util/Timer.h"


class __PidCalibration : public ArduinoSketch
{
    bool calibratingProximalJoint = false;
    ControlMode controlMode = ControlMode::POSITION;

    ArduinoInputCommand inputReader;

    HardwareParameters hp;

    PT15AngleSensor angleSensor;
    PT15SeriesElasticSensor torqueSensor;
    L298NMotorDriver motorDriver;

    FeedForwardController torqueController;
    PositionTensionController positionController;

    PIDGains torqueGains;
    PIDGains positionGains;

    float desired;
    float measuredPosition;   
    float measuredTorque;
    float control;

    Timer dtTimer;

    Timer printTimer;

    float feedforward = 8.0;

    public:
    __PidCalibration() = default;

    void setup()
    {
        torqueGains.kp = 40.0;
        torqueGains.ki = 30.0;
        torqueGains.kd = 0.1;
        torqueGains.maxIntegrator = 5.5;
        torqueGains.maxControl = 12.0;
        torqueGains.alphaDerivative = 0.001;
        torqueGains.derivativeTime = 0.01;
        float torqueFeedForward = 8.0;

        positionGains.kp = 0.2;
        positionGains.ki = 0.05;
        positionGains.kd = 0.0;
        positionGains.maxIntegrator = 5.5;
        positionGains.maxControl = 12.0;
        positionGains.alphaDerivative = 0.01;
        positionGains.derivativeTime = 0.01;
        float positionFeedForward = 8.0;
        float hysteresisSize = 0.0;
        float minimumTorque = 0.03; // actual min is 0.05

        float torqueSensorAlpha = 0.001;

        inputReader = ArduinoInputCommand(controlMode, hp.POT_1_READ_PIN, hp.POT_2_READ_PIN, hp);

        hp = HardwareParameters();
        HardwareParameters::SensorParameters sp = hp.sensorParameters;

        torqueController = FeedForwardController(torqueFeedForward, torqueGains);
        positionController = PositionTensionController(positionFeedForward, hysteresisSize, minimumTorque, positionGains, torqueController);

        dtTimer.set(0.001);

        printTimer.set(0.01);

        if (calibratingProximalJoint)
        {
            motorDriver = L298NMotorDriver(hp.MOTOR_VOLTAGE, hp.motorDriver1.ENA_PIN, hp.motorDriver1.DIR1_PIN, hp.motorDriver1.DIR2_PIN, hp.motorDriver1.flipDirection);
            angleSensor = PT15AngleSensor(sp.angle1.READ_PIN, sp.angle1.ZERO, sp.velocityReadTick, sp.angleAlphaFilter, sp.velocityAlphaFilter);
            torqueSensor = PT15SeriesElasticSensor(sp.torque1.READ_PIN, sp.torque1.SCALE, sp.torque1.RAW_OFFSET, sp.torque1.DEADBAND, torqueSensorAlpha, sp.torque1.flipDirection);
        }
        else
        {
            motorDriver = L298NMotorDriver(hp.MOTOR_VOLTAGE, hp.motorDriver2.ENA_PIN, hp.motorDriver2.DIR1_PIN, hp.motorDriver2.DIR2_PIN, hp.motorDriver2.flipDirection);
            angleSensor = PT15AngleSensor(sp.angle2.READ_PIN, sp.angle2.ZERO, sp.velocityReadTick, sp.angleAlphaFilter, sp.velocityAlphaFilter);
            torqueSensor = PT15SeriesElasticSensor(sp.torque2.READ_PIN, sp.torque2.SCALE, sp.torque2.RAW_OFFSET, sp.torque2.DEADBAND, torqueSensorAlpha, sp.torque2.flipDirection);
        }
        inputReader.hardwareSetup();
        motorDriver.hardwareSetup();
        angleSensor.hardwareSetup();
        torqueSensor.hardwareSetup();
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
            angleSensor.read(dt);
            torqueSensor.read(dt);
            measuredPosition = angleSensor.getAngleDeg();   
            measuredTorque = torqueSensor.getTorqueNm();


            // get control
            if (controlMode == ControlMode::TORQUE)
            {
                control = torqueController.stepAndGet(measuredTorque, desired, dt);         
            }
            else
            {
                control = positionController.stepAndGet(measuredTorque, measuredPosition, desired, dt);
            }
            

            // send to motor
            motorDriver.submitVoltage(control);
            motorDriver.write();
        }

        if (printTimer.isRinging())
        {
            printTimer.restart();
            Serial.print(desired); Serial.print(",");
            Serial.print(measuredPosition); Serial.print(",");
            Serial.print(measuredTorque); Serial.print(",");
            Serial.print(control);
            Serial.println();
        }

    }



};


#endif