#ifndef __JICR__
#define __JICR__

#include "InputCommand.h"
#include "ControlMode.h"
#include "InputCommandReader.h"


class JavaInputCommand : public InputCommandReader
{    
    ControlMode controlMode = ControlMode::POSITION;

    InputCommand inputControlCommand;

public:
    JavaInputCommand()
    {

    }

    void read()
    {
        // String string = getInputString();
        // parseInputString(string);
    }

private:
    void parseInputString(String string)
    {
        inputControlCommand.mode = 0;
        inputControlCommand.angle1 = 0;
        inputControlCommand.angle2 = 0;
        inputControlCommand.torque1 = 0.0;
        inputControlCommand.torque2 = 0.0;
    }

public:
    InputCommand getInputCommand() 
    {
        return inputControlCommand;
    }
};

#endif