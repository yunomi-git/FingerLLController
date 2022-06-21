#ifndef __AICR__
#define __AICR__

#include "InputCommand.h"
#include "AngleSensor.h"
#include "ControlMode.h"
#include "InputCommandReader.h"
#include "PT15AngleSensor.h"

class ArduinoInputCommand : public InputCommandReader
{
    PT15AngleSensor angleSensor1;
    PT15AngleSensor angleSensor2;
    ControlMode controlMode = ControlMode::POSITION;

    InputCommand inputControlCommand;
 public:   
    ArduinoInputCommand()
    {

    }

    void read()
    {
        inputControlCommand.mode = controlMode;
        inputControlCommand.angle1 = angleSensor1.getAngleDeg();
        inputControlCommand.angle2 = angleSensor2.getAngleDeg();
        inputControlCommand.torque1 = 0.0;
        inputControlCommand.torque2 = 0.0;
    }

    InputCommand getInputCommand() 
    {
        return inputControlCommand;
    }
};

#endif