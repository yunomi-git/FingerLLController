#include "ArduinoSketch.h"
#include "Run_FingerController.h"

ArduinoSketch *sketch;

void setup() 
{
    sketch = new Run_FingerController();
    sketch->setup();
}

void loop()
{
    sketch->loop();
}
