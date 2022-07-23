#ifndef __SKETCH__
#define __SKETCH__

// hold hx711 on table and add weights

#include "../ArduinoSketch.h"
#include "./hardwareInterface/HardwareParameters.h"

#include "../hardware/HX711TorqueSensor.h"

#include "../util/Timer.h"
#include "../util/AlphaFilter.h"

class Run_HX711Calibration : public ArduinoSketch
{
    HX711ForceSensor referenceSensor;
    AlphaFilter<float> filter;

    Timer sensorTimer;
    float sensorTime = 0.0001;

    Timer printTimer;
    float printTime = 0.001;

    Timer calibrationTimer;
    float calibrateTime = 0.5;

public:
    Run_HX711Calibration() = default;

    
    void setup()
    {
        filter = AlphaFilter<float>(0.005);
        HardwareParameters hp = HardwareParameters();
        referenceSensor = HX711ForceSensor(hp.HX_DOUT_PIN, hp.HX_SCK_PIN); // get these from hardware parameters
        referenceSensor.hardwareSetup();
        // referenceSensor.tare();

        sensorTimer.usePrecision();
        sensorTimer.set(sensorTime);

        printTimer.set(printTime);

        calibrationTimer.set(calibrateTime);
    }

    void loop()
    {
        // reference 
        if (calibrationTimer.isRinging())
        {
            calibrationTimer.stopRinging();
            referenceSensor.tare(100);
        }
        if (sensorTimer.isRinging())
        {
            float dt = sensorTimer.dt();
            sensorTimer.restart();

            referenceSensor.read(dt);
        }
        if (printTimer.isRinging())
        {
            printTimer.restart();
            // Serial.println(referenceSensor.getForceN());
            float mass = referenceSensor.getForceN();
            filter.update(mass);
            Serial.println(filter.getFilteredData(), 10);
        }

    }
};

#endif