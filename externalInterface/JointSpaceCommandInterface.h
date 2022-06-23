#ifndef __ICR__
#define __ICR__

#include "JointSpaceCommand.h"
#include "../abstractHardware/SensorData.h"

class JointSpaceCommandInterface
{
    public:
    JointSpaceCommandInterface()
    {

    }

    virtual JointSpaceCommand recieve() = 0;

    virtual void send(SensorData SensorData) = 0;
};

#endif