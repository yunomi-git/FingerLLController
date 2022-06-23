#include "ArduinoSketch.h"
#include "mainController/Run_FingerController.h"
#include "SESCalibration/Run_HX711Calibration.h"
#include "SESCalibration/Run_SESCalibration.h"

ArduinoSketch *sketch;

void setup() 
{
    sketch = new Run_FingerController();
    // sketch = new Run_HX711Calibration();
    // sketch = new Run_SESCalibration();
    sketch->setup();
}

void loop()
{
    sketch->loop();
}
