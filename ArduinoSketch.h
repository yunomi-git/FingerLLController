#ifndef __ARDUINOSKETCH__
#define __ARDUINOSKETCH__

class ArduinoSketch
{
    public:
    ArduinoSketch() {}

    virtual void setup() = 0;
    virtual void loop() = 0;
}

#endif