#ifndef __HX711Force__
#define __HX711Force__

#include "HX711.h"
#include "../abstractHardware/ForceSensor.h"

class HX711ForceSensor : public ForceSensor 
{
private:
    HX711 hx711;
    byte dout;
    byte pd_sck;
    float scale;

    float KG_SCALE = 399000.f;
	float GRAVITY = 9.81;

    float force;

public:
	HX711ForceSensor() = default;

	HX711ForceSensor(byte dout, byte pd_sck, float scale) 
	{
		this->dout = dout;
		this->pd_sck = pd_sck;
        this->scale = scale;
	}

	void hardwareSetup() {
		hx711.begin(dout, pd_sck);
		hx711.set_scale(scale);
	}

	void tare(int times=10) {
		setTareOffset(0);  //todo
	}

	void read(float dt)
	{
		if (hx711.is_ready()) {
			float kg_reading = hx711.get_units();
            force = kg_reading * GRAVITY;
		} 
	}

	float getForceN() {
		return force;
	}
};

#endif