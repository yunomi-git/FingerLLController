#ifndef __SENSORDATAPACKER__
#define __SENSORDATAPACKER__

#include "../../hardware/PT15AngleSensor.h"
#include "../../hardware/PT15SeriesElasticSensor.h"

#include "HardwareParameters.h"

#include "../../packets/SensorData.h"

class SensorDataPackerV5
{
    public:
    SensorDataPackerV5() = default;

    SensorDataPackerV5(HardwareParameters hp)
    {
        HardwareParameters::SensorParameters sp = hp.sensorParameters;
        torque1Sensor = PT15SeriesElasticSensor(sp.torque1.READ_PIN, sp.torque1.SCALE, sp.torque1.RAW_OFFSET, sp.torque1.DEADBAND);
        torque2Sensor = PT15SeriesElasticSensor(sp.torque2.READ_PIN, sp.torque2.SCALE, sp.torque2.RAW_OFFSET, sp.torque2.DEADBAND);
        angle1Sensor = PT15AngleSensor(sp.angle1.READ_PIN, sp.angle1.ALPHA);
        angle2Sensor = PT15AngleSensor(sp.angle2.READ_PIN, sp.angle2.ALPHA);
    }

    void hardwareSetup()
    {
        angle1Sensor.hardwareSetup();
        angle2Sensor.hardwareSetup();
        torque2Sensor.hardwareSetup();
        torque1Sensor.hardwareSetup();
    }

    void read(float dt)
    {
        torque1Sensor.read(dt);
        torque2Sensor.read(dt);
        angle1Sensor.read(dt);
        angle2Sensor.read(dt);
    }

    SensorData getReading()
    {
        SensorData sensorData = SensorData();
        
        sensorData.torque1 = torque1Sensor.getTorqueNm();
        sensorData.torque2 = torque2Sensor.getTorqueNm();
        sensorData.velocity1 = angle1Sensor.getVelocityDegSec();
        sensorData.velocity2 = angle2Sensor.getVelocityDegSec();
        sensorData.angle1 = angle1Sensor.getAngleDeg();
        sensorData.angle2 = angle2Sensor.getAngleDeg();

        return sensorData;
    }

private:
    PT15SeriesElasticSensor torque1Sensor;
    PT15SeriesElasticSensor torque2Sensor;
    PT15AngleSensor angle1Sensor;
    PT15AngleSensor angle2Sensor;
};

#endif