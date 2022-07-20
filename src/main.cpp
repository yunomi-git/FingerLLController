#include <Arduino.h>
#include "ArduinoSketch.h"
// #include "mainController/Run_FingerController.h"
// #include "testController/Run_TestController.h"

// ------ Calibration -----------
// #include "Calibration/Run_HX711Calibration.h"
// #include "Calibration/Run_SESCalibration.h"
// #include "Calibration/Run_PositionCalibration.h"
#include "playground/__PrintSensors.h"

// ------- CPP testing ------------
// #include "playground/__PointerTest.h"

// #include "playground/Run__SerialWriter.h"
// #include "playground/__MotorPlayground.h"

ArduinoSketch *sketch;

void setup() 
{
    Serial.begin(115200);
    // sketch = new Run_TestController();
    // sketch = new Run_FingerController();
    // sketch = new Run_HX711Calibration();
    // sketch = new Run_SESCalibration();
    // sketch = new Run_SerialWriter();
    sketch = new __PrintSensors();
    // sketch = new Run_PositionCalibration();
    // sketch = new __MotorPlayground();

    // sketch = new __PointerTest();
    sketch->setup();
}

void loop()
{

    sketch->loop();
}