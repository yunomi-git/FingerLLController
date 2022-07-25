#ifndef __FIN_L298NDRIVERSW__
#define __FIN_L298NDRIVERSW__

#include "../abstractHardware/MotorDriver.h"
#include "../util/MathUtil.h"
#include "../Constants.h"
#include <Arduino.h>

class L298NMotorDriver : public MotorDriver {
public:
	L298NMotorDriver() = default;

    L298NMotorDriver(float supplyVoltage, byte ENA, byte DIR1, byte DIR2, bool flipDirection=false) 
        : MotorDriver(supplyVoltage) 
    {
        this->ENA = ENA;
        this->DIR1 = DIR1;
        this->DIR2 = DIR2;
        if (flipDirection)
        {
            setDirection(NEGATIVE_DIRECTION);
        }
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

    void submitVoltage(float voltage)
    {
        this->voltage = fbound(voltage, -supplyVoltage, supplyVoltage) * getDirection();
    }

    void write() {
        if (!directionIsConsistentWithVoltage(voltage)) {
    		switchHardwareDirection();
      	}
        // Serial.println((int)(fabs(voltage)/getMaxVoltage() * ANALOG_WRITE_SCALE));
        analogWrite(ENA, (int)(fabs(voltage)/getMaxVoltage() * ANALOG_WRITE_SCALE));
    }

private:
    byte ENA;
    byte DIR1;
    byte DIR2;
    Direction hardwareDirection = POSITIVE_DIRECTION;
    float voltage;

    void switchToDirection1() {
        digitalWrite(DIR1, LOW);
        digitalWrite(DIR2, HIGH);
    }

    void switchToDirection2() {
        digitalWrite(DIR1, HIGH);
        digitalWrite(DIR2, LOW);
    }

    void switchHardwareDirection() {
      	stop();
    	if (getHardwareDirection() == POSITIVE_DIRECTION.value) {
    		switchToDirection2();
    		hardwareDirection = NEGATIVE_DIRECTION;
    	} else {
    		switchToDirection1();
    		hardwareDirection = POSITIVE_DIRECTION;
    	}
    }

    bool directionIsConsistentWithVoltage(float voltage) {
        return voltage * getHardwareDirection() > 0;
    }

    float getHardwareDirection()
    {
        return hardwareDirection.value;
    }
};

#endif