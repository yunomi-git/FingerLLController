#ifndef __JICR__
#define __JICR__

#include "JointSpaceCommand.h"
#include "ControlMode.h"
#include "JointSpaceCommandInterface.h"


class JavaCommandInterface : public JointSpaceCommandInterface
{    
    ControlMode controlMode = ControlMode::POSITION;

    JointSpaceCommand jointSpaceCommand;

public:
    JavaCommandInterface()
    {

    }

    JointSpaceCommand recieve()
    {
        // String string = getInputString();
        // parseInputString(string);
    }

    void send(SensorData sensorData)
    {

    }

private:
    void parseInputString(String string)
    {
        jointSpaceCommand.mode = 0;
        jointSpaceCommand.angle1 = 0;
        jointSpaceCommand.angle2 = 0;
        jointSpaceCommand.torque1 = 0.0;
        jointSpaceCommand.torque2 = 0.0;
    }
};

#endif