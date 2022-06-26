#ifndef __HX711Force__
#define __HX711Force__

#include <HX711.h>
#include "../abstractHardware/ForceSensor.h"

class HX711ForceSensor : public ForceSensor 
{
private:
    HX711 hx711;
    byte dout; // mosi or dout
    byte pd_sck; // sck aka spi serial clock
    float scale;

    float KG_SCALE = 399000.f;
	float GRAVITY = 9.81;

    float force;

public:
	HX711ForceSensor() = default;

	HX711ForceSensor(byte dout, byte pd_sck) 
	{
		this->dout = dout;
		this->pd_sck = pd_sck;
	}

	void hardwareSetup() {
		hx711.begin(dout, pd_sck);
		hx711.set_scale(KG_SCALE);
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