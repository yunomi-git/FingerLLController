#ifndef __FLLC__
#define __FLLC__

#include "SensorDataPacker.h"
#include "SensorData.h"
#include "VoltageCommand.h"
#include "PIDController.h"
#include "ControlMode.h"
#include "InputCommand.h"
#include "Parameters.h"
#include "ActuatorWriter.h"
#include "HardwareManager.h"

class FingerLowLevelController
{
public:
    FingerLowLevelController() = default;

    FingerLowLevelController(HardwareParameters hp, ControllerParameters cp)
    {
        hardwareManager = HardwareManager(hp);
        sensorDataPacker = hardwareManager.createSensorDataPacker();
        actuatorWriter = hardwareManager.createActuatorWriter();

        angleController1 = PIDController(cp.angle1Gains);
        angleController2 = PIDController(cp.angle2Gains);
        torqueController1 = PIDController(cp.torque1Gains);
        torqueController2 = PIDController(cp.torque2Gains);
    }

    void hardwareSetup()
    {
        hardwareManager.hardwareSetup();
        timer.usePrecision();
        timer.set(MIN_TIME_BETWEEN_CONTROL);
    }

    void submitCommand(InputCommand inputCommand) 
    {
        this->inputCommand = inputCommand;
    }

    void doControl()
    {
        if (timer.isRinging())
        {
            float dt = timer.dt();
            timer.restart();
            sensorDataPacker->read(dt);
            sensorData = sensorDataPacker->getReading();

            VoltageCommand voltageCommand = computeVoltage(dt);
            actuatorWriter->setCommand(voltageCommand);
            actuatorWriter->write();
        }

    }

private:
    VoltageCommand computeVoltage(float dt)
    {
        ControlMode controlMode = inputCommand.mode;
        switch (controlMode)
        {
            // if control mode changed, reset integrators
            case POSITION:
                return computePositionControlCommand(inputCommand.angle1, inputCommand.angle2, dt);
            case TORQUE:
                return computeTorqueControlCommand(inputCommand.torque1, inputCommand.torque2, dt);
            default:
                break;
        }
    }

    VoltageCommand computePositionControlCommand(float desiredAngle1, float desiredAngle2, float dt)
    {
        float angle1Error = sensorData.angle1 - desiredAngle1;
        float angle2Error = sensorData.angle2 - desiredAngle2;

        VoltageCommand voltageCommand = VoltageCommand();
        voltageCommand.voltage1 = angleController1.stepAndGet(angle1Error, dt);
        voltageCommand.voltage2 = angleController2.stepAndGet(angle2Error, dt);
        return voltageCommand; 
    }

    VoltageCommand computeTorqueControlCommand(float desiredTorque1, float desiredTorque2, float dt)
    {
        float torque1Error = sensorData.torque1 - desiredTorque1;
        float torque2Error = sensorData.torque2 - desiredTorque2;

        VoltageCommand voltageCommand = VoltageCommand();
        voltageCommand.voltage1 = torqueController1.stepAndGet(torque1Error, dt);
        voltageCommand.voltage2 = torqueController2.stepAndGet(torque2Error, dt);
        return voltageCommand; 
    }
public:
    SensorData getMeasurements()
    {
        return sensorData;
    }

    private:
    InputCommand inputCommand;

    HardwareManager hardwareManager;
    
    SensorDataPacker *sensorDataPacker;
    SensorData sensorData;

    PIDController angleController1;
    PIDController angleController2;
    PIDController torqueController1;
    PIDController torqueController2;

    ActuatorWriter *actuatorWriter;

    Timer timer;

    float MIN_TIME_BETWEEN_CONTROL = 0.0001; //sec
};



#endif