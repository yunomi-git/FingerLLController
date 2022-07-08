#include <Arduino.h>
#include "ArduinoSketch.h"
#include "mainController/Run_FingerController.h"
// #include "testController/Run_TestController.h"

// #include "SESCalibration/Run_HX711Calibration.h"
// #include "SESCalibration/Run_SESCalibration.h"

ArduinoSketch *sketch;

void setup() 
{
    Serial.begin(115200);
    // sketch = new Run_TestController();
    sketch = new Run_FingerController();
    // sketch = new Run_HX711Calibration();
    // sketch = new Run_SESCalibration();
    sketch->setup();
}

void loop()
{

    sketch->loop();
}