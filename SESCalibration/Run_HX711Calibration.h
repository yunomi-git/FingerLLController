#ifndef __RUN_HX711Calibration__
#define __RUN_HX711Calibration__

#include "../ArduinoSketch.h"
#include "hardwareInterface/HardwareParameters.h"

#include "../hardware/PT15SeriesElasticSensor.h"
#include "../hardware/HX711TorqueSensor.h"

#include "../util/Timer.h"

class Run_HX711Calibration : public ArduinoSketch
{
    HX711ForceSensor referenceSensor;

    Timer sensorTimer;
    float sensorTime = 0.0001;

    Timer printTimer;
    float printTime = 0.001;

public:
    Run_HX711Calibration() = default;
    
    void setup()
    {
        HardwareParameters hp = HardwareParameters();
        referenceSensor = HX711ForceSensor(dout, pd_sck, scale); // get these from hardware parameters
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

            referenceSensor.read(dt);
        }
        if (printTimer.isRinging())
        {
            //print referenceSensor.getTorqueNm();
        }

    }
};

#endif