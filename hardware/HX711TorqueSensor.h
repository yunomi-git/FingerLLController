#ifndef __HX711Torque__
#define __HX711Torque__

#include "HX711ForceSensor.h"

class HX711TorqueSensor : public TorqueSensor {
private:
    HX711ForceSensor forceSensor;

    //float mounting_length_mm = 80;
    float mountingLength;

    float torque;
    
public:
	HX711TorqueSensor() = default;

	HX711TorqueSensor(byte dout, byte pd_sck, float scale, float mountingLength) 
	{
		forceSensor = HX711ForceSensor(dout, pd_sck, scale);
        this->mountingLength = mountingLength;
	}

	void hardwareSetup() {
		
        forceSensor.hardwareSetup();
	}

	void tare(int times=10) {
		setTareOffset(tareOffset);
	}

	void read(float dt)
	{
        forceSensor.read();
        float force = forceSensor.getForceN();
        torque = force * mounting_length_mm / 1000.0;
	}

	float getTorqueNm() {
		return torque;
	}
};

#endif