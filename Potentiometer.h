#ifndef __FIN_POTENT__
#define __FIN_POTENT__

#include "Constants.h"

class Potentiometer {
public:
	Potentiometer(byte readPin) {
        this.readPin = readPin;
	}

    void hardwareSetup() {
        pinMode(readPin, INPUT);
    }

    float getReadingNormalized() {
        int read = analogRead(readPin);
        float normalized_read = read / ANALOG_READ_SCALE;
        return normalized_read;
    }

private:
	byte readPin;
};

#endif

