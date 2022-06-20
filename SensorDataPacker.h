#ifndef __SENSORDATAPACKER__
#define __SENSORDATAPACKER__

#include "AngleSensor.h"
#include "PT15AngleSensor.h"
#include "TorqueSensor.h"
#include "PT15SeriesElasticSensor.h"
#include "SensorData.h"
#include "Parameters.h"

class SensorDataPacker
{
    public:
    SensorDataPacker(HardwareParameters::SensorParameters parameters)
    {
        ses1 = PT15SeriesElasticSensor(parameters.torque1.READ_PIN, parameters.torque2.SCALE, parameters.torque2.TARE_OFFSET);
        ses2 = PT15SeriesElasticSensor(parameters.torque2.READ_PIN, parameters.torque2.SCALE, parameters.torque2.TARE_OFFSET);
        ang1 = PT15AngleSensor(parameters.angle1.READ_PIN, parameters.angle1.ALPHA);
        ang2 = PT15AngleSensor(parameters.angle2.READ_PIN, parameters.angle2.ALPHA);
    }

    void hardwareSetup()
    {
        ang1.hardwareSetup();
        ang2.hardwareSetup();
        ses1.hardwareSetup();
        ses2.hardwareSetup();
    }

    void updateReading(float dt)
    {
        ses1.updateReading(dt);
        ses2.updateReading(dt);
        ang1.updateReading(dt);
        ang2.updateReading(dt);
    }

    SensorData getReading()
    {
        SensorData sensorData = SensorData();
        
        sensorData.torque1 = ses1.getTorqueNm();
        sensorData.torque2 = ses1.getTorqueNm();
        sensorData.velocity1 = ang1.getVelocityDegSec();
        sensorData.velocity2 = ang2.getVelocityDegSec();
        sensorData.angle1 = ang1.getAngleDeg();
        sensorData.angle2 = ang2.getAngleDeg();

        return sensorData;
    }

private:
    TorqueSensor ses1;
    TorqueSensor ses2;
    AngleSensor ang1;
    AngleSensor ang2;
};

#endif