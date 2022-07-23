#ifndef __SKETCH__
#define __SKETCH__



#include "ArduinoSketch.h"
#include <Arduino.h>
#include "../externalInterface/JavaCommandInterface.h"
#include "../packets/SensorData.h"
#include "../mainController/hardwareInterface/HardwareParameters.h"
#include "../Constants.h"
#include "../util/Timer.h"
#include "../mainController/hardwareInterface/HardwareParameters.h"
#include "../hardware/PT15AngleSensor.h"

// streams sensor data to java side 

class Run_SerialWriter : public ArduinoSketch
{
public:
    Run_SerialWriter() = default;
    HardwareParameters hp;
    byte writeBuffer[12];
    SensorData sensorData;

    Timer printTimer;

    Timer sensorTimer;
    float sensorTime = 0.0001;

    PT15AngleSensor angle1Sensor;
    PT15AngleSensor angle2Sensor;

    bool sendToJava = true;


    void setup()
    {
        HardwareParameters::SensorParameters sp = hp.sensorParameters;
        angle1Sensor = PT15AngleSensor(sp.angle1.READ_PIN, sp.angle1.ALPHA);
        angle2Sensor = PT15AngleSensor(sp.angle2.READ_PIN, sp.angle2.ALPHA);
        angle1Sensor.setZero(sp.angle1.ZERO);
        angle2Sensor.setZero(sp.angle2.ZERO);
        angle1Sensor.hardwareSetup();
        angle2Sensor.hardwareSetup();

        Serial.begin(115200);
        hp = HardwareParameters();

        sensorData = SensorData();
        sensorData.angle1 = 3.8;
        sensorData.velocity1 = 0;
        sensorData.torque1 =0;
        sensorData.angle2 = 0;
        sensorData.velocity2 = 0;
        sensorData.torque2 = 0;

        printTimer.set(0.01);
        sensorTimer.usePrecision();
        sensorTimer.set(sensorTime);

        convertSensorDataToBytes(sensorData, writeBuffer);
        // writeBufferToSerial(writeBuffer, sizeof(writeBuffer));
    }

    void loop()
    {

        if (sensorTimer.isRinging())
        {
            float dt = sensorTimer.dt();
            sensorTimer.restart();

            angle1Sensor.read(dt);
            angle2Sensor.read(dt);
            sensorData.angle1 = angle1Sensor.getAngleDeg();
            sensorData.angle2 = angle2Sensor.getAngleDeg();
        }
        if (printTimer.isRinging())
        {
            printTimer.restart();
            if (sendToJava)
            {
                
                convertSensorDataToBytes(sensorData, writeBuffer);
                Serial.write(writeBuffer, sizeof(writeBuffer));
                // writeBufferToSerial(writeBuffer, sizeof(writeBuffer));
            }
            else
            {
                // printSensorsDirectly(sensorData);
                printBytesDirectly(sensorData, true);
            }
        }
        

        
    }

    void writeBufferToSerial(byte *buffer, int length)
    {
        for (int i = 0; i < length; i++)
        {
            Serial.write(buffer[i]);
        }
    }

    int convertFloatToInt(float f, float min, float max)
    {
        if (f < min) f = min;
        if (f > max) f = max;
        float ratio = (f - min) / (max - min);
        // Serial.println((int) (ratio * SERIAL_WRITE_SCALE));
        return (int) (ratio * SERIAL_WRITE_SCALE);
    }

    void writeFloatToBufferAtIndex(float f, float min, float max, byte *buffer, int i)
    {
        int intData = convertFloatToInt(f, min, max);
        // Serial.print(intData, BIN); Serial.print(", ");
        // Serial.print((byte) (intData >> 8), BIN); Serial.print(", ");
        // Serial.print((byte) (intData), BIN); Serial.println();
        buffer[i] = (byte) (intData >> 8);
        buffer[i+1] = (byte) (intData);
    }

    void convertSensorDataToBytes(SensorData sensorData, byte *buffer)
    {
        writeFloatToBufferAtIndex(sensorData.angle1, hp.MIN_READ_ANGLE, hp.MAX_READ_ANGLE, buffer, 0);
        writeFloatToBufferAtIndex(sensorData.velocity1, hp.MIN_READ_VELOCITY, hp.MAX_READ_VELOCITY, buffer, 2);
        writeFloatToBufferAtIndex(sensorData.torque1, hp.MIN_READ_TORQUE, hp.MAX_READ_TORQUE, buffer, 4);
        writeFloatToBufferAtIndex(sensorData.angle2, hp.MIN_READ_ANGLE, hp.MAX_READ_ANGLE, buffer, 6);
        writeFloatToBufferAtIndex(sensorData.velocity2, hp.MIN_READ_VELOCITY, hp.MAX_READ_VELOCITY, buffer, 8);
        writeFloatToBufferAtIndex(sensorData.torque2, hp.MIN_READ_TORQUE, hp.MAX_READ_TORQUE, buffer, 10);
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

    void printBytesDirectly(SensorData sensorData, bool inBinary)
    {
        printByteForData(sensorData.angle1, hp.MIN_READ_ANGLE, hp.MAX_READ_ANGLE, inBinary);
        printByteForData(sensorData.velocity1, hp.MIN_READ_VELOCITY, hp.MAX_READ_VELOCITY, inBinary);
        printByteForData(sensorData.torque1, hp.MIN_READ_TORQUE, hp.MAX_READ_TORQUE, inBinary);
        printByteForData(sensorData.angle2, hp.MIN_READ_ANGLE, hp.MAX_READ_ANGLE, inBinary);
        printByteForData(sensorData.velocity2, hp.MIN_READ_VELOCITY, hp.MAX_READ_VELOCITY, inBinary);
        printByteForData(sensorData.torque2, hp.MIN_READ_TORQUE, hp.MAX_READ_TORQUE, inBinary);
        Serial.println();
    }

    void printByteForData(float f, float min, float max, bool inBinary)
    {
        int intData = convertFloatToInt(f, min, max);
        if (inBinary)
        {
            Serial.print(intData, BIN); Serial.print(", ");
        }
        else
        {
            Serial.print(intData); Serial.print(", ");
        }
    }
};

#endif