#ifndef __SKETCH__
#define __SKETCH__

#include "ArduinoSketch.h"
#include <Arduino.h>
#include "../externalInterface/JavaCommandInterface.h"
#include "../packets/SensorData.h"
#include "../Constants.h"
#include "../util/Timer.h"
#include "../hardware/PT15AngleSensor.h"

#include "../mainController/hardwareInterface/HardwareParameters.h"
#include "../mainController/hardwareInterface/HardwareManager.h"
#include "../mainController/hardwareInterface/SensorDataPacker.h"


class __PrintSensors : public ArduinoSketch
{
public:
    __PrintSensors() = default;
    HardwareParameters hp;
    byte writeBuffer[12];
    SensorData sensorData;

    Timer printTimer;

    Timer sensorTimer;
    float sensorTime = 0.0001;

    PT15AngleSensor angle1Sensor;
    PT15AngleSensor angle2Sensor;

    HardwareManager hardwareManager;
    SensorDataPacker *sensorDataPacker;

    

    bool sendToJava = true;


    void setup()
    {
        // HardwareParameters::SensorParameters sp = hp.sensorParameters;
        // angle1Sensor = PT15AngleSensor(sp.angle1.READ_PIN, sp.angle1.ALPHA);
        // angle2Sensor = PT15AngleSensor(sp.angle2.READ_PIN, sp.angle2.ALPHA);
        // angle1Sensor.setZero(sp.angle1.ZERO);
        // angle2Sensor.setZero(sp.angle2.ZERO);
        // angle1Sensor.hardwareSetup();
        // angle2Sensor.hardwareSetup();

        Serial.begin(115200);
                // Serial.println("aaa done");

        hp = HardwareParameters();
        hardwareManager = HardwareManager(hp);
        hardwareManager.hardwareSetup();
        Serial.println("setup done");

        // sensorDataPacker = hardwareManager.createSensorDataPacker();

        sensorData = SensorData();

        printTimer.set(0.01);
        sensorTimer.usePrecision();
        sensorTimer.set(sensorTime);
    }

    void loop()
    {

        if (sensorTimer.isRinging())
        {
            float dt = sensorTimer.dt();
            sensorTimer.restart();

            // sensorDataPacker->read(dt);

            // angle1Sensor.read(dt);
            // angle2Sensor.read(dt);
            // sensorData.angle1 = angle1Sensor.getAngleDeg();
            // sensorData.angle2 = angle2Sensor.getAngleDeg();
        }
        if (printTimer.isRinging())
        {
            printTimer.restart();
            // sensorData = sensorDataPacker->getReading();
            printSensorsDirectly(sensorData);
        }
    }

    void printSensorsDirectly(SensorData sensorData)
    {
        Serial.print(sensorData.angle1, 5); Serial.print(", ");
        Serial.print(sensorData.velocity1, 5); Serial.print(", ");
        Serial.print(sensorData.torque1, 5); Serial.print(", ");
        Serial.print(sensorData.angle2, 5); Serial.print(", ");
        Serial.print(sensorData.velocity2, 5); Serial.print(", ");
        Serial.print(sensorData.torque2, 5);
        Serial.println();
    }
};

#endif