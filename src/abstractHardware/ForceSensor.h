#ifndef __FINFORCESW__
#define __FINFORCESW__

#include "Sensor.h"

class ForceSensor : public Sensor 
{
public:
	ForceSensor() = default;

	virtual void read(float dt) = 0;
	virtual float getForceN() = 0;

	virtual void tare(int times=10) = 0;

	bool getIsTared() {
		return isTared;
	}

	void setTared() {
		isTared = true;
	}
	
    public:
    virtual void hardwareSetup() = 0;

protected:
	float getRawOffset() {
		return rawOffset;
	}

	void setTareOffset(float offset) {
		rawOffset = offset;
		setTared();
	}

private:
	float rawOffset = 0;

	bool isTared = false;
};


#endif