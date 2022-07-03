#ifndef __VOLTAGECOMMAND__
#define __VOLTAGECOMMAND__

struct VoltageCommand
{
    VoltageCommand() = default;
    
    VoltageCommand(float voltage1, float voltage2)
    {
        this->voltage1 = voltage1;
        this->voltage2 = voltage2;
    }
    float voltage1;
    float voltage2;
};

#endif