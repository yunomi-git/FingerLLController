#ifndef __SENSOR__
#define __SENSOR__

#include "../util/Direction.h"

class Sensor
{
public:
    // Any hardware related setup needs to be done in setup(), not at declaration.
    // This method holds all such hardware related setup.
    virtual void hardwareSetup() = 0;

    // Does the hardware reading and stores the value
    virtual void read(float dt) = 0;
    // Further classes need to implement a way to access read values

    // Sets the direction
    void setDirection(Direction direction)
    {
        this->direction = direction;
    }

    float getDirection()
    {
        return direction.value;
    }

	void setZeroSI(float offset) {
		zeroSI = offset;
	}

protected:
	float getZeroSI() {
		return zeroSI;
	}



private:
    Direction direction = POSITIVE_DIRECTION;
    float zeroSI = 0;
};

#endif