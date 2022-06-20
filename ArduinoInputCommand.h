#ifndef __AICR__
#define __AICR__

#include "InputCommand.h"
#include "AngleSensor.h"
#include "ControlMode.h"

class ArduinoInputCommand
{
    AngleSensor angleSensor1;
    AngleSensor angleSensor2;
    ControlMode controlMode = ControlMode.POSITION;

    InputCommand inputControlCommand;
    
    ArduinoInputCommand()
    {

    }

    void update()
    {
        inputControlCommand.mode = controlMode;
        inputControlCommand.angle1 = angleSensor1.getAngleDegrees();
        inputControlCommand.angle2 = angleSensor2.getAngleDegrees();
        inputControlCommand.torque1 = 0.0;
        inputControlCommand.torque2 = 0.0;
    }

    InputControlCommand getInputCommand() 
    {
        return inputControlCommand;
    }
}

#endif