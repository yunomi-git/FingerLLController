#ifndef __ACTUATORWRITER__
#define __ACTUATORWRITER__

#include "MotorDriver.h"
#include "VoltageCommand.h"

class ActuatorWriter
{
    private:
    MotorDriver *motorDriver1;
    MotorDriver *motorDriver2;  

    VoltageCommand voltageCommand;

    public:
    ActuatorWriter() = default;

    ActuatorWriter(MotorDriver *motorDriver1, MotorDriver *motorDriver2)
    {
        this->motorDriver1 = motorDriver1;
        this->motorDriver2 = motorDriver2;
    }

    void hardwareSetup()
    {
        motorDriver1->hardwareSetup();
        motorDriver2->hardwareSetup();
    }

    void setCommand(VoltageCommand voltageCommand)
    {
        this->voltageCommand = voltageCommand;
    }

    void write()
    {
        motorDriver1->sendVoltageCommand(voltageCommand.voltage1);
        motorDriver2->sendVoltageCommand(voltageCommand.voltage2);
    }
};

#endif