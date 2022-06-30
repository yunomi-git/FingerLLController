#ifndef __FINSEASW__
#define __FINSEASW__

#include "../abstractHardware/TorqueSensor.h"
#include "Potentiometer.h"

class PT15SeriesElasticSensor : public TorqueSensor {
public:
	PT15SeriesElasticSensor() = default;

	PT15SeriesElasticSensor(byte readPin, float springConstant, float tareOffset, float deadbandSize) 
	{
		this->readPin = readPin;
		this->springConstant = springConstant;
		this->tareOffset = tareOffset;
		this->deadbandSize = deadbandSize;
	}

	void hardwareSetup() {
		potentiometer = Potentiometer(readPin);
		potentiometer.hardwareSetup();
		setTareOffset(tareOffset);
	}

	void tare(int times=10) {
		setTareOffset(tareOffset);
	}

	void read(float dt)
	{
		float read = potentiometer.getReadingNormalized() - getRawOffset();
		read = applyDeadband(read);
		torque = convertReadToTorqueNm(read);
	}

	float getTorqueNm() {
		return torque;
	}

public:
	float getRawRead() {
		return potentiometer.getReadingNormalized();
	}

private:
	float convertReadToTorqueNm(float read_value) {
		return springConstant * read_value;
	}

	float applyDeadband(float read) {
		if (fabs(read) < deadbandSize) {
			 return 0;
		} else {
			return read;
		}
	}

private:
	byte read_pin;
	Potentiometer potentiometer;

	float torque = 0.0;

	// const float SPRING_CONSTANT = 1.2; for 0.625", original spring
	byte readPin;
	float springConstant = 3.2; // for 17mm, stronger spring
	float tareOffset = 0.513;
	float deadbandSize = 0.02;

	//const float lower_deadband = 0.507;
	//const float upper_deadband = 0.56;
	//const float tare_offset = (lower_deadband+upper_deadband)/2;
	//const float deadband_size = tare_offset - lower_deadband;

};


#endif