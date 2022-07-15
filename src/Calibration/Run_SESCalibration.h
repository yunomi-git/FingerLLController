#ifndef __SKETCH__
#define __SKETCH__

#include "../ArduinoSketch.h"
#include "hardwareInterface/HardwareParameters.h"

#include "../hardware/PT15SeriesElasticSensor.h"
#include "../hardware/HX711TorqueSensor.h"

#include "../util/Timer.h"

class Run_SESCalibration : public ArduinoSketch
{
    // ..... alter these parameters for tuning ......
    byte readPin = 21;
    float springConstant = 2.7;
    float deadbandSize = 0.018;
    float tareOffset = 0.5265;
    // ..............................................

    PT15SeriesElasticSensor sesSensor;
    HX711TorqueSensor referenceSensor;
    Timer sensorTimer;
    float sensorTime = 0.0001;

    Timer printTimer;
    float printTime = 0.001;

    Timer calibrationTimer;
    float calibrateTime = 1;

public:
    Run_SESCalibration() = default;
    
    void setup()
    {
        HardwareParameters hp = HardwareParameters();
        sesSensor = PT15SeriesElasticSensor(readPin, springConstant, tareOffset, deadbandSize);
        referenceSensor = HX711TorqueSensor(hp.HX_DOUT_PIN, hp.HX_SCK_PIN, hp.HX_MOUNTING_LENGTH);

        sesSensor.hardwareSetup();
        referenceSensor.hardwareSetup();

        sensorTimer.usePrecision();
        sensorTimer.set(sensorTime);

        printTimer.set(printTime);

        calibrationTimer.set(calibrateTime);
    }

    void loop()
    {
        if (calibrationTimer.isRinging())
        {
            calibrationTimer.stopRinging();
            referenceSensor.tare(100);
            sesSensor.tare();
        }

        if (sensorTimer.isRinging())
        {
            float dt = sensorTimer.dt();
            sensorTimer.restart();

            sesSensor.read(dt);
            referenceSensor.read(dt);
        }
        if (printTimer.isRinging())
        {
            printTimer.restart();
            // Serial.println(referenceSensor.getForceN());
            float refTorque = referenceSensor.getTorqueNm();
            float sensTorque = sesSensor.getTorqueNm();
            Serial.print(sesSensor.getRawRead(), 10);Serial.print(",");
            Serial.print(refTorque, 10); Serial.print(",");
            Serial.print(-sensTorque, 10); //Serial.print(" ");
            Serial.println();
            // filter.update(mass);
            // Serial.println(filter.getFilteredData(), 10);
            //print sesSensor.getTorqueNm();
            //print referenceSensor.getTorqueNm();
        }

    }
};

#endif