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

	void setTared() {
		isTared = true;
	}    

    bool getIsTared() {
		return isTared;
	}

    public:
    virtual void hardwareSetup() = 0;

private:
	bool isTared = false;
};


#endif