#ifndef __RUN_SESCalibration__
#define __RUN_SESCalibration__

#include "../ArduinoSketch.h"
#include "../hardware/HardwareParameters.h"

#include "../hardware/PT15SeriesElasticSensor.h"
#include "../hardware/HX711TorqueSensor.h"

#include "../util/Timer.h"

class Run_SESCalibration : public ArduinoSketch
{
    // alter these parameters for tuning
    byte readPin = 16;
    float springConstant = 3.2;
    float tareOffset = 0.2;

    PT15SeriesElasticSensor sesSensor;
    HX711ForceSensor referenceSensor;
    Timer sensorTimer;
    float sensorTime = 0.0001;

    Timer printTimer;
    float printTime = 0.001;

public:
    Run_SESCalibration() = default;
    
    void setup()
    {
        sesSensor = PT15SeriesElasticSensor(readPin, springConstant, tareOffset);
        referenceSensor = HX711TorqueSensor(dout, pd_sck, scale, mountingLength); // get these from hardware parameters

        sesSensor.hardwareSetup();
        referenceSensor.hardwareSetup();

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

            sesSensor.read(dt);
            referenceSensor.read(dt);
        }
        if (printTimer.isRinging())
        {
            //print sesSensor.getTorqueNm();
            //print referenceSensor.getTorqueNm();
        }

    }
};

#endif