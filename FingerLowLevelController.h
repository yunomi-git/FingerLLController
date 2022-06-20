#ifndef __FLLC__
#define __FLLC__

#include "SensorDataPacker.h"
#include "SensorData.h"
#include "VoltageCommand.h"
#include "PIDController.h"
#include "ControlMode.h"
#include "InputCommand.h"
#include "MotorDriver.h"
#include "L298NMotorDriver.h"
#include "Parameters.h"

class FingerLowLevelController
{
public:
    FingerLowLevelController() = default;

    FingerLowLevelController(HardwareParameters hp, ControllerParameters cp)
    {
        motorDriver1 = L298NMotorDriver(hp.motorDriver1.SUPPLY_VOLTAGE, hp.motorDriver1.ENA_PIN, hp.motorDriver1.DIR1, hp.motorDriver1.DIR2);  
        motorDriver2 = L298NMotorDriver(hp.motorDriver2.SUPPLY_VOLTAGE, hp.motorDriver2.ENA_PIN, hp.motorDriver2.DIR1, hp.motorDriver2.DIR2);      
        sensorDataPacker = SensorDataPacker(hp.sensorParameters);

        angleController1 = PIDController(cp.angle1Gains);
        angleController2 = PIDController(cp.angle2Gains);
        torqueController1 = PIDController(cp.torque1Gains);
        torqueController2 = PIDController(cp.torque2Gains);
    }

    void hardwareSetup()
    {
        motorDriver1.hardwareSetup();
        motorDriver2.hardwareSetup();
        sensorDataPacker.hardwareSetup();
    }

    void submitCommand(InputCommand inputCommand) 
    {
        self.inputCommand = inputCommand;
    }

    void doControl(float dt)
    {
        sensorDataPacker.updateReading(dt);
        sensorData = sensorDataPacker.getReading();

        VoltageCommand voltageCommand = computeVoltage(dt);
        motorDriver1.sendVoltage(voltageCommand.voltage1);
        motorDriver2.sendVoltage(voltageCommand.voltage2);
    }

    VoltageCommand computeVoltage(float dt)
    {
        ControlMode controlMode = inputCommand.controlMode;
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

        VoltageCommand voltageCommand = new VoltageCommand();
        voltageCommand.voltage1 = angleController1.stepAndGet(angle1Error, dt);
        voltageCommand.voltage2 = angleController2.stepAndGet(angle2Error, dt);
        return voltageCommand; 
    }

    VoltageCommand computeTorqueControlCommand(float desiredTorque1, float desiredTorque2, float dt)
    {
        float torque1Error = sensorData.torque1 - desiredTorque1;
        float torque2Error = sensorData.torque2 - desiredTorque2;

        VoltageCommand voltageCommand = new VoltageCommand();
        voltageCommand.voltage1 = torqueController1.stepAndGet(torque1Error, dt);
        voltageCommand.voltage2 = torqueController2.stepAndGet(torque2Error, dt);
        return voltageCommand; 
    }

    SensorData getMeasurements(float dt)
    {
        return sensorData;
    }

    private:
    InputCommand inputCommand;
    
    SensorDataPacker sensorDataPacker;
    SensorData sensorData;

    PIDController angleController1;
    PIDController angleController2;
    PIDController torqueController1;
    PIDController torqueController2;

    MotorDriver motorDriver1;
    MotorDriver motorDriver2;
};



#endif