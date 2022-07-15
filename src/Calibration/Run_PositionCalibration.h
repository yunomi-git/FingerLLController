#ifndef __SKETCH__
#define __SKETCH__

#include "../ArduinoSketch.h"
#include "hardwareInterface/HardwareParameters.h"

#include "../hardware/PT15AngleSensor.h"

#include "../util/Timer.h"

class Run_PositionCalibration : public ArduinoSketch
{
    // ..... alter these parameters for tuning ......
    byte readPin = 22;
    float alpha = 0.0;
    float zero = 5.9326;
    // ..............................................

    PT15AngleSensor angleSensor;
    Timer sensorTimer;
    float sensorTime = 0.0001;

    Timer printTimer;
    float printTime = 0.001;


public:
    Run_PositionCalibration() = default;
    
    void setup()
    {
        HardwareParameters hp = HardwareParameters();
        angleSensor = PT15AngleSensor(readPin, alpha);
        angleSensor.setZero(zero);

        angleSensor.hardwareSetup();

        sensorTimer.usePrecision();
        sensorTimer.set(sensorTime);

        printTimer.set(printTime);

    }

    void loop()
    {
        if (sensorTimer.isRinging())
        {
            float dt = sensorTimer.dt();
            sensorTimer.restart();

            angleSensor.read(dt);
        }
        if (printTimer.isRinging())
        {
            printTimer.restart();
            // Serial.println(referenceSensor.getForceN());
            float angle = angleSensor.getAngleDeg();
            // Serial.print(sesSensor.getRawRead(), 10);Serial.print(",");
            Serial.print(angle, 10); //Serial.print(" ");
            Serial.println();
            // filter.update(mass);
            // Serial.println(filter.getFilteredData(), 10);
            //print sesSensor.getTorqueNm();
            //print referenceSensor.getTorqueNm();
        }

    }
};

#endif