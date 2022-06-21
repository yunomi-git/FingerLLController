#ifndef __ICR__
#define __ICR__

#include "InputCommand.h"

class InputCommandReader
{
    public:
    InputCommandReader()
    {

    }

    virtual void read() = 0;

    virtual InputCommand getInputCommand() = 0;
};

#endif