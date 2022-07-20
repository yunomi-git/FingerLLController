#ifndef __TEST_PACKER__
#define __TEST_PACKER__

#include "../abstractHardware/AngleSensor.h"

class TestSensorPacker
{
    AngleSensor *angleSensor;

    public:
    TestSensorPacker() = default;

    TestSensorPacker(AngleSensor *angleSensor)
    {
        this->angleSensor = angleSensor;
    }

    void hardwareSetup()
    {
        angleSensor->hardwareSetup();
    }
};

#endif