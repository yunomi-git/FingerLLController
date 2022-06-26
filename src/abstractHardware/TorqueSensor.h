#ifndef __FINTORQUESW__
#define __FINTORQUESW__

#include "Sensor.h"

class TorqueSensor : public Sensor
{
public:
	TorqueSensor() = default;

	virtual void hardwareSetup() = 0;
	virtual void read(float dt) = 0;
	virtual float getTorqueNm() = 0;

	virtual void tare(int times=10) = 0;

	bool getIsTared() {
		return isTared;
	}

	void setTared() {
		isTared = true;
	}    

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