#ifndef __ICR__
#define __ICR__

#include "../packets/JointSpaceCommand.h"
#include "../packets/SensorData.h"

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