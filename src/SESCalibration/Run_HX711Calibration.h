#ifndef __SKETCH__
#define __SKETCH__

#include "../ArduinoSketch.h"
#include "./hardwareInterface/HardwareParameters.h"

#include "../hardware/HX711TorqueSensor.h"

#include "../util/Timer.h"

class Run_HX711Calibration : public ArduinoSketch
{
    HX711ForceSensor referenceSensor;

    Timer sensorTimer;
    float sensorTime = 0.0001;

    Timer printTimer;
    float printTime = 0.01;

public:
    Run_HX711Calibration() = default;
    
    void setup()
    {
        HardwareParameters hp = HardwareParameters();
        referenceSensor = HX711ForceSensor(hp.HX_DOUT_PIN, hp.HX_SCK_PIN); // get these from hardware parameters
        referenceSensor.hardwareSetup();
        referenceSensor.tare();

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
            printTimer.restart();
            Serial.println(referenceSensor.getForceN());
        }

    }
};

#endif