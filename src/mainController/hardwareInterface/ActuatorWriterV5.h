#ifndef __ACTUATORWRITER__
#define __ACTUATORWRITER__

#include "../../hardware/L298NMotorDriver.h"
#include "HardwareParameters.h"
#include "VoltageCommand.h"

class ActuatorWriterV5
{
    private:
    L298NMotorDriver motorDriver1;
    L298NMotorDriver motorDriver2;  

    VoltageCommand voltageCommand;

    public:
    ActuatorWriterV5() = default;

    ActuatorWriterV5(HardwareParameters hp)
    {
        motorDriver1 = L298NMotorDriver(hp.motorDriver1.SUPPLY_VOLTAGE, hp.motorDriver1.ENA_PIN, hp.motorDriver1.DIR1_PIN, hp.motorDriver1.DIR2_PIN);  
        motorDriver2 = L298NMotorDriver(hp.motorDriver2.SUPPLY_VOLTAGE, hp.motorDriver2.ENA_PIN, hp.motorDriver2.DIR1_PIN, hp.motorDriver2.DIR2_PIN);    
    }

    void hardwareSetup()
    {
        motorDriver1.hardwareSetup();
        motorDriver2.hardwareSetup();
    }

    void setCommand(VoltageCommand voltageCommand)
    {
        this->voltageCommand = voltageCommand;
        motorDriver1.submitVoltage(voltageCommand.voltage1);
        motorDriver2.submitVoltage(voltageCommand.voltage2);
    }

    void write()
    {
        motorDriver1.write();
        motorDriver2.write();
    }
};

#endif