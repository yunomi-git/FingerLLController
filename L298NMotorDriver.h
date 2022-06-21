#ifndef __FIN_L298NDRIVERSW__
#define __FIN_L298NDRIVERSW__

#include "MotorDriver.h"
#include "MathUtil.h"
#include "Constants.h"
#include <Arduino.h>

class L298NMotorDriver : public MotorDriver {
public:
	L298NMotorDriver() = default;

    L298NMotorDriver(float supplyVoltage, byte nENA, byte nDIR1, byte nDIR2) : MotorDriver(supplyVoltage) {
        this->ENA = ENA;
        this->DIR1 = DIR1;
        this->DIR2 = DIR2;
    }

    void hardwareSetup() 
    {
        pinMode(ENA, OUTPUT);
        pinMode(DIR1, OUTPUT);
        pinMode(DIR2, OUTPUT);

        stop();
        switchToDirection1();
    }

    void stop() {
        analogWrite(ENA, 0);
    }

private:
    int ENA;
    int DIR1;
    int DIR2;

    void switchToDirection1() {
        digitalWrite(DIR1, LOW);
        digitalWrite(DIR2, HIGH);
    }

    void switchToDirection2() {
        digitalWrite(DIR1, HIGH);
        digitalWrite(DIR2, LOW);
    }

    void writeVoltageToHardware(float voltage) {
        analogWrite(ENA, (int)(fabs(voltage)/getMaxVoltage() * ANALOG_WRITE_SCALE));
    }
};

#endif