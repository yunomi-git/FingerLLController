#ifndef __HARDWAREMANAGER__
#define __HARDWAREMANAGER__

#include "PT15AngleSensor.h"
#include "PT15SeriesElasticSensor.h"
#include "SensorDataPacker.h"
#include "L298NMotorDriver.h"
#include "Parameters.h"
#include "ActuatorWriter.h"

class HardwareManager
{
    private:
    SensorDataPacker sensorDataPacker;
    PT15AngleSensor angle1Sensor;
    PT15AngleSensor angle2Sensor;
    PT15SeriesElasticSensor torque1Sensor;
    PT15SeriesElasticSensor torque2Sensor;

    ActuatorWriter actuatorWriter;
    L298NMotorDriver motorDriver1;
    L298NMotorDriver motorDriver2;

    public:
    HardwareManager() = default;

    HardwareManager(HardwareParameters hp)
    {
        HardwareParameters::SensorParameters sp = hp.sensorParameters;
        torque1Sensor = PT15SeriesElasticSensor(sp.torque1.READ_PIN, sp.torque2.SCALE, sp.torque2.RAW_OFFSET);
        torque2Sensor = PT15SeriesElasticSensor(sp.torque2.READ_PIN, sp.torque2.SCALE, sp.torque2.RAW_OFFSET);
        angle1Sensor = PT15AngleSensor(sp.angle1.READ_PIN, sp.angle1.ALPHA);
        angle2Sensor = PT15AngleSensor(sp.angle2.READ_PIN, sp.angle2.ALPHA);
        sensorDataPacker = SensorDataPacker(&angle1Sensor, &angle2Sensor, &torque1Sensor, &torque2Sensor);

        motorDriver1 = L298NMotorDriver(hp.motorDriver1.SUPPLY_VOLTAGE, hp.motorDriver1.ENA_PIN, hp.motorDriver1.DIR1_PIN, hp.motorDriver1.DIR2_PIN);  
        motorDriver2 = L298NMotorDriver(hp.motorDriver2.SUPPLY_VOLTAGE, hp.motorDriver2.ENA_PIN, hp.motorDriver2.DIR1_PIN, hp.motorDriver2.DIR2_PIN);    
        actuatorWriter = ActuatorWriter(&motorDriver1, &motorDriver2);
    }

    void hardwareSetup()
    {
        sensorDataPacker.hardwareSetup();
        actuatorWriter.hardwareSetup();
    }

    SensorDataPacker * createSensorDataPacker()
    {
        return &sensorDataPacker;
    }

    ActuatorWriter * createActuatorWriter()
    {
        return &actuatorWriter;
    }

};

#endif