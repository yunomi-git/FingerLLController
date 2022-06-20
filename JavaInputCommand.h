#ifndef __JICR__
#define __JICR__

#include "InputCommand.h"
#include "ControlMode.h"

class JavaInputCommand
{    
    ControlMode controlMode = ControlMode.POSITION;

    InputCommand inputControlCommand;

public:
    JavaInputCommand()
    {

    }

    void update()
    {
        String string = getInputString();
        parseInputString(string);
    }

private:
    void parseInputString(String string)
    {
        inputControlCommand.mode = controlMode;
        inputControlCommand.angle1 = angleSensor1.getAngleDegrees();
        inputControlCommand.angle2 = angleSensor2.getAngleDegrees();
        inputControlCommand.torque1 = 0.0;
        inputControlCommand.torque2 = 0.0;
    }

public:
    InputControlCommand getInputCommand() 
    {
        return inputControlCommand;
    }
}

#endif