#ifndef __FIN_MOTORDRIVERSW__
#define __FIN_MOTORDRIVERSW__

#include "../util/MathUtil.h"

class MotorDriver {
public:
	MotorDriver() = default;

	MotorDriver(float supplyVoltage) {
		this->supplyVoltage = supplyVoltage;
	}

	virtual void hardwareSetup() = 0;

    virtual void stop() = 0;

    void sendVoltageCommand(float voltage) {
    	voltage = fbound(voltage, -supplyVoltage, supplyVoltage);

      	if (!directionIsConsistentWithVoltage(voltage)) {
    		switchDirection();
      	}

        writeVoltageToHardware(voltage);
    }

    float getMaxVoltage() {
    	return supplyVoltage;
    }

protected:
	virtual void writeVoltageToHardware(float voltage)  = 0;
	virtual void switchToDirection1() = 0;
	virtual void switchToDirection2() = 0;

	void switchDirection() {
      	stop();
    	if (direction == direction1) {
    		switchToDirection2();
    		direction = direction2;
    	} else {
    		switchToDirection1();
    		direction = direction1;
    	}
    }

	float supplyVoltage;

private:
	static const int direction1 = 1;
	static const int direction2 = -1;

	int direction = direction1;

    bool directionIsConsistentWithVoltage(float voltage) {
        return voltage * direction > 0;
    }
};

#endif

