#ifndef __FLLC__
#define __FLLC__

#include "hardwareInterface/SensorDataPacker.h"
#include "hardwareInterface/SensorData.h"
#include "hardwareInterface/VoltageCommand.h"
#include "hardwareInterface/ActuatorWriter.h"

#include "hardwareInterface/HardwareParameters.h"
#include "hardwareInterface/HardwareManager.h"

#include "ControllerParameters.h"
#include "ControlComputer.h"

#include "externalInterface/ControlMode.h"
#include "externalInterface/JointSpaceCommand.h"

class FingerLowLevelController
{
public:
    FingerLowLevelController() = default;

    FingerLowLevelController(HardwareParameters hp, ControllerParameters cp)
    {
        hardwareManager = HardwareManager(hp);
        sensorDataPacker = hardwareManager.createSensorDataPacker();
        actuatorWriter = hardwareManager.createActuatorWriter();
        maxVoltage = hp.MOTOR_VOLTAGE;

        controlComputer = ControlComputer(hp, cp);
    }

    void hardwareSetup()
    {
        hardwareManager.hardwareSetup();
        timer.usePrecision();
        timer.set(MIN_TIME_BETWEEN_CONTROL);
    }

    void submitCommand(JointSpaceCommand jointSpaceCommand) 
    {
        this->jointSpaceCommand = jointSpaceCommand;
    }

    void doControl()
    {
        if (timer.isRinging())
        {
        Serial.print(jointSpaceCommand.input1); Serial.print(",");
        Serial.print(jointSpaceCommand.input2); 
        Serial.println();
            float dt = timer.dt();
            timer.restart();

            // sensorDataPacker->read(dt);
            // sensorData = sensorDataPacker->getReading();

            // controlComputer.submitJointspaceCommand(jointSpaceCommand);
            // controlComputer.compute(sensorData, dt);
            // VoltageCommand voltageCommand = controlComputer.getVoltageCommand();

            // actuatorWriter->setCommand(voltageCommand);
            // actuatorWriter->write();
        }

    }

public:
    SensorData getMeasurements()
    {
        return sensorData;
    }

    private:
    float maxVoltage;
    JointSpaceCommand jointSpaceCommand;

    HardwareManager hardwareManager;
    
    SensorDataPacker *sensorDataPacker;
    SensorData sensorData;

    ControlComputer controlComputer;

    ActuatorWriter *actuatorWriter;

    Timer timer;

    float MIN_TIME_BETWEEN_CONTROL = 0.0001; //sec
};



#endif