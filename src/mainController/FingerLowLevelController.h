#ifndef __FLLC__
#define __FLLC__

#include "../packets/ControlMode.h"
#include "../packets/JointSpaceCommand.h"
#include "../packets/SensorData.h"

#include "hardwareInterface/SensorDataPackerV5.h"
#include "hardwareInterface/VoltageCommand.h"
#include "hardwareInterface/ActuatorWriterV5.h"

#include "hardwareInterface/HardwareParameters.h"
#include "hardwareInterface/HardwareManager.h"

#include "ControllerParameters.h"
#include "ControlComputer.h"



class FingerLowLevelController
{
public:
    FingerLowLevelController() = default;

    FingerLowLevelController(HardwareParameters hp, ControllerParameters cp)
    {
        MIN_TIME_BETWEEN_CONTROL = hp.controlDt;
        actuatorWriter = ActuatorWriterV5(hp);
        sensorDataPacker = SensorDataPackerV5(hp);

        controlComputer = ControlComputer(hp, cp);
    }

    void hardwareSetup()
    {
        actuatorWriter.hardwareSetup();
        sensorDataPacker.hardwareSetup();
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
            float dt = timer.dt();
            timer.restart();

            sensorDataPacker.read(dt);
            sensorData = sensorDataPacker.getReading();

            controlComputer.submitJointspaceCommand(jointSpaceCommand);
            controlComputer.compute(sensorData, dt);
            VoltageCommand voltageCommand = controlComputer.getVoltageCommand();

            actuatorWriter.setCommand(voltageCommand);
            actuatorWriter.write();
        }

    }

public:
    SensorData getMeasurements()
    {
        return sensorData;
    }

    private:
    JointSpaceCommand jointSpaceCommand;

    SensorDataPackerV5 sensorDataPacker;
    SensorData sensorData;

    ControlComputer controlComputer;

    ActuatorWriterV5 actuatorWriter;

    Timer timer;

    float MIN_TIME_BETWEEN_CONTROL; //sec
};



#endif