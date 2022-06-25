#ifndef __AICR__
#define __AICR__

#include "JointSpaceCommand.h"
#include "ControlMode.h"
#include "JointSpaceCommandInterface.h"

class ArduinoInputCommand : public JointSpaceCommandInterface
{
    Potentiometer pot1;
    Potentiometer pot2;
    ControlMode controlMode = ControlMode::POSITION;

    JointSpaceCommand jointSpaceCommand;
 public:   
    ArduinoInputCommand(byte POT1_READ_PIN, byte POT2_READ_PIN)
    {
        pot1 = Potentiometer(POT1_READ_PIN);
        pot2 = Potentiometer(POT2_READ_PIN);
    }

    void hardwareSetup()
    {
        pot1.hardwareSetup();
        pot2.hardwareSetup();
    }

    JointSpaceCommand recieve()
    {
        jointSpaceCommand.mode = controlMode;
        jointSpaceCommand.input1 = pot1.getReadingNormalized();
        jointSpaceCommand.input2 = pot2.getReadingNormalized();
    }

    void send(SensorData sensorData)
    {

    }
};

#endif