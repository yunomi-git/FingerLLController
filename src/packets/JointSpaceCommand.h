#ifndef __INPUTCOMMAND__
#define __INPUTCOMMAND__

#include "ControlMode.h"

struct JointSpaceCommand
{
    ControlMode mode;
    float input1;
    float input2;
};

#endif