#ifndef __ICR__
#define __ICR__

class InputCommandReader
{
    public:
    InputCommandReader()
    {

    }

    virtual void update() = 0;

    virtual InputControlCommand getInputCommand() = 0;
}

#endif