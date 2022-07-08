#ifndef __SENSORDATAPACKER__
#define __SENSORDATAPACKER__

#include "../../abstractHardware/AngleSensor.h"
#include "../../abstractHardware/TorqueSensor.h"

#include "SensorData.h"

class SensorDataPacker
{
    public:
    SensorDataPacker() = default;

    SensorDataPacker(AngleSensor *ang1)
    {
        this->ang1 = ang1;
    }

    void hardwareSetup()
    {
        ang1->hardwareSetup();
    }

    void read(float dt)
    {
        ang1->read(dt);
    }

    SensorData getReading()
    {
        SensorData sensorData = SensorData();

        sensorData.angle1 = ang1->getAngleDeg();

        return sensorData;
    }

private:
    AngleSensor *ang1;
};

#endif