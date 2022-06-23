#ifndef __HX711Force__
#define __HX711Force__

#include "HX711/HX711.h"

class HX711ForceSensor : public ForceSensor {
private:
    HX711 hx711;
    byte dout;
    byte pd_sck;

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
		torque_sensor_HW.begin(dout, pd_sck);
		torque_sensor_HW.set_scale(scale);
	}

	void tare(int times=10) {
		setTareOffset(tareOffset);
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