#ifndef __SENSORDATAPACKER__
#define __SENSORDATAPACKER__

#include "../../abstractHardware/AngleSensor.h"
#include "../../abstractHardware/TorqueSensor.h"

#include "../../packets/SensorData.h"

class SensorDataPacker
{
    public:
    SensorDataPacker() = default;

    SensorDataPacker(AngleSensor *ang1, AngleSensor *ang2, TorqueSensor *ses1, TorqueSensor *ses2)
    {
        this->ang1 = ang1;
        this->ang2 = ang2;
        this->ses1 = ses1;
        this->ses2 = ses2;
        ang1->printName();

    }

    void hardwareSetup()
    {
        Serial.println("sensor setup");
        if (!ang1)
        {
            Serial.println("angle is null");
        }
        else
        {
            Serial.println("angle not null");
        }
        ang1->printName();
        ang1->hardwareSetup();
        ang2->hardwareSetup();
        ses1->hardwareSetup();
        ses2->hardwareSetup();
    }

    void read(float dt)
    {
        // ses1->read(dt);
        // ses2->read(dt);
        ang1->read(dt);
        // ang2->read(dt);
    }

    SensorData getReading()
    {
        SensorData sensorData = SensorData();
        
        // sensorData.torque1 = ses1->getTorqueNm();
        // sensorData.torque2 = ses2->getTorqueNm();
        // sensorData.velocity1 = ang1->getVelocityDegSec();
        // sensorData.velocity2 = ang2->getVelocityDegSec();
        // sensorData.angle1 = ang1->getAngleDeg();
        // sensorData.angle2 = ang2->getAngleDeg();

        return sensorData;
    }

private:
    TorqueSensor *ses1;
    TorqueSensor *ses2;
    AngleSensor *ang1;
    AngleSensor *ang2;
};

#endif