#ifndef __HX711Torque__
#define __HX711Torque__

#include "HX711ForceSensor.h"
#include "../abstractHardware/TorqueSensor.h"

class HX711TorqueSensor : public TorqueSensor {
private:
    HX711ForceSensor forceSensor;

    //float mounting_length_mm = 80;
    float mountingLengthMM;

    float torque;
    
public:
	HX711TorqueSensor() = default;

	HX711TorqueSensor(byte dout, byte pd_sck, float mountingLengthMM) 
	{
		forceSensor = HX711ForceSensor(dout, pd_sck);
        this->mountingLengthMM = mountingLengthMM;
	}

	void hardwareSetup() 
    {
        forceSensor.hardwareSetup();
	}

	void tare(int times=10) // how to tare?
    {
		forceSensor.tare(times);
		setZeroSI(0);  // toododo
	}

	void read(float dt)
	{
        forceSensor.read(dt);
        float force = forceSensor.getForceN();
        torque = force * mountingLengthMM / 1000.0;
	}

	float getTorqueNm() {
		return torque;
	}
};

#endif