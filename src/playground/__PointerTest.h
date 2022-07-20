#ifndef __SKETCH__
#define __SKETCH__

#include "../ArduinoSketch.h"
#include "../abstractHardware/AngleSensor.h"
#include "../hardware/PT15AngleSensor.h"

#include "TestSensorPacker.h"

class __PointerTest : public ArduinoSketch
{
public:
    __PointerTest() = default;
    AngleSensor *angleSensor;
    PT15AngleSensor ptSensor;
    TestSensorPacker sensorPacker;

    void setup()
    {
        Serial.begin(115200);

        ptSensor = PT15AngleSensor(20);
        sensorPacker = TestSensorPacker(&ptSensor);
        angleSensor = &ptSensor;

        sensorPacker.hardwareSetup();
        angleSensor->hardwareSetup();
    }

    void loop()
    {

        // if (sensorTimer.isRinging())
        // {
        //     float dt = sensorTimer.dt();
        //     sensorTimer.restart();

        //     // sensorDataPacker->read(dt);

        //     // angle1Sensor.read(dt);
        //     // angle2Sensor.read(dt);
        //     // sensorData.angle1 = angle1Sensor.getAngleDeg();
        //     // sensorData.angle2 = angle2Sensor.getAngleDeg();
        // }
        // if (printTimer.isRinging())
        // {
        //     printTimer.restart();
        //     // sensorData = sensorDataPacker->getReading();
        //     printSensorsDirectly(sensorData);
        // }
    }
};

#endif