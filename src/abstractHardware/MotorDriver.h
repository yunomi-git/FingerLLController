#ifndef __FIN_MOTORDRIVERSW__
#define __FIN_MOTORDRIVERSW__

#include "../util/MathUtil.h"
#include "../util/Direction.h"

class MotorDriver {
public:
	MotorDriver() = default;

	MotorDriver(float supplyVoltage) {
		this->supplyVoltage = supplyVoltage;
	}

	virtual void hardwareSetup() = 0;

    virtual void stop() = 0;

	virtual void submitVoltage(float voltage) = 0;

    virtual void write() = 0;

    float getMaxVoltage() {
    	return supplyVoltage;
    }

    void setDirection(Direction direction)
    {
        this->direction = direction;
    }

    float getDirection()
    {
        return direction.value;
    }
protected:

	float supplyVoltage;

private:
	Direction direction = POSITIVE_DIRECTION;

    bool directionIsConsistentWithVoltage(float voltage) {
        return voltage * getDirection() > 0;
    }
};

#endif

