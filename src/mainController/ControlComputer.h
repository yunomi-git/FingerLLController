#ifndef __CONTROLCOMPUTE__
#define __CONTROLCOMPUTE__

#include "./hardwareInterface/HardwareParameters.h"
#include "ControllerParameters.h"
#include "../packets/JointSpaceCommand.h"
#include "./hardwareInterface/VoltageCommand.h"
#include "PIDController.h"
#include "./packets/SensorData.h"

class ControlComputer
{
    public:
    ControlComputer() = default;

    ControlComputer(HardwareParameters hp, ControllerParameters cp)
    {
        angleController1 = PIDController(cp.angle1Gains);
        angleController2 = PIDController(cp.angle2Gains);
        torqueController1 = PIDController(cp.torque1Gains);
        torqueController2 = PIDController(cp.torque2Gains);
    }

    void submitJointspaceCommand(JointSpaceCommand jointSpaceCommand)
    {
        this->jointSpaceCommand = jointSpaceCommand;
    }

    void compute(SensorData sensorData, float dt)
    {
        ControlMode controlMode = jointSpaceCommand.mode;
        switch (controlMode)
        {
            // if control mode changed, reset integrators
            case POSITION:
                voltageCommand = computePositionControlCommand(sensorData, jointSpaceCommand.input1, jointSpaceCommand.input2, dt);
            case TORQUE:
                voltageCommand = computeTorqueControlCommand(sensorData, jointSpaceCommand.input1, jointSpaceCommand.input2, dt);
            case VOLTAGE:
                voltageCommand = computeVoltageControlCommand(sensorData, jointSpaceCommand.input1, jointSpaceCommand.input2, dt);
            default:
                voltageCommand = VoltageCommand(0, 0);
                break;
        }
    }

    VoltageCommand getVoltageCommand()
    {
        return voltageCommand;
    }

private:
    VoltageCommand computePositionControlCommand(SensorData sensorData, float desiredAngle1, float desiredAngle2, float dt)
    {
        VoltageCommand voltageCommand = VoltageCommand();
        voltageCommand.voltage1 = angleController1.stepAndGet(sensorData.angle1, desiredAngle1, dt);
        voltageCommand.voltage2 = angleController2.stepAndGet(sensorData.angle2, desiredAngle2, dt);
        return voltageCommand; 
    }

    VoltageCommand computeTorqueControlCommand(SensorData sensorData, float desiredTorque1, float desiredTorque2, float dt)
    {
        VoltageCommand voltageCommand = VoltageCommand();
        voltageCommand.voltage1 = torqueController1.stepAndGet(sensorData.torque1, desiredTorque1, dt);
        voltageCommand.voltage2 = torqueController2.stepAndGet(sensorData.torque2, desiredTorque2, dt);
        return voltageCommand; 
    }

    VoltageCommand computeVoltageControlCommand(SensorData sensorData, float desiredVoltage1, float desiredVoltage2, float dt)
    {
        VoltageCommand voltageCommand = VoltageCommand(desiredVoltage1, desiredVoltage2);
        return voltageCommand; 
    }

    JointSpaceCommand jointSpaceCommand;
    VoltageCommand voltageCommand;

    PIDController angleController1;
    PIDController angleController2;
    PIDController torqueController1;
    PIDController torqueController2;
};

#endif