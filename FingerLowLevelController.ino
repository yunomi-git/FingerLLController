#include "ArduinoSketch.h"
#include "Run_FingerController.h"

ArduinoSketch sketch;

setup() 
{
    sketch = Run_FingerController();
    sketch.setup();
}

loop()
{
    sketch.loop();
}