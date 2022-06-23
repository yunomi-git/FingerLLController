#ifndef __AICR__
#define __AICR__

#include "JointSpaceCommand.h"
#include "ControlMode.h"
#include "JointSpaceCommandInterface.h"

#include "../../hardware/PT15AngleSensor.h"

class ArduinoInputCommand : public JointSpaceCommandInterface
{
    PT15AngleSensor angleSensor1;
    PT15AngleSensor angleSensor2;
    ControlMode controlMode = ControlMode::POSITION;

    JointSpaceCommand jointSpaceCommand;
 public:   
    ArduinoInputCommand()
    {

    }

    JointSpaceCommand recieve()
    {
        jointSpaceCommand.mode = controlMode;
        jointSpaceCommand.angle1 = angleSensor1.getAngleDeg();
        jointSpaceCommand.angle2 = angleSensor2.getAngleDeg();
        jointSpaceCommand.torque1 = 0.0;
        jointSpaceCommand.torque2 = 0.0;
    }

    void send(SensorData sensorData)
    {

    }
};

#endif