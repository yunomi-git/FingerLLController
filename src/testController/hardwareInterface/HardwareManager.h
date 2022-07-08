#ifndef __HARDWAREMANAGER__
#define __HARDWAREMANAGER__

#include "../../hardware/PT15AngleSensor.h"
#include "../../hardware/PT15SeriesElasticSensor.h"
#include "../../hardware/L298NMotorDriver.h"

#include "HardwareParameters.h"
#include "SensorDataPacker.h"
#include "ActuatorWriter.h"

class HardwareManager
{
    private:
    SensorDataPacker sensorDataPacker;
    PT15AngleSensor angle1Sensor;
    PT15AngleSensor angle2Sensor;
    PT15SeriesElasticSensor torque1Sensor;
    PT15SeriesElasticSensor torque2Sensor;

    L298NMotorDriver motorDriver1;
    L298NMotorDriver motorDriver2;

    public:
    HardwareManager() = default;

    HardwareManager(HardwareParameters hp)
    {
        // and set the direcrions
        HardwareParameters::SensorParameters sp = hp.sensorParameters;
        angle1Sensor = PT15AngleSensor(sp.angle1.READ_PIN, sp.angle1.ALPHA);
        sensorDataPacker = SensorDataPacker(&angle1Sensor);

        Serial.println("HardwareManager: Printing here prevents serial bug"); // unknown bug
    }

    void hardwareSetup()
    {
        sensorDataPacker.hardwareSetup();
    }

    SensorDataPacker * createSensorDataPacker()
    {
        return &sensorDataPacker;
    }

};

#endif