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

    float KG_SCALE = 401000.f;
	float GRAVITY = 9.81;

    float force;
	float mass;

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
		float avgReading = 0.0;
		float delayTime = 0.01;
		for (int i = 0; i < times; i++)
		{
			delay((int) (delayTime * 1000));
			read(delayTime);
			avgReading += force / times;
		}
		setTareOffset(avgReading);

	}

	void read(float dt)
	{
		if (hx711.is_ready()) {
			float kg_reading = hx711.get_units();
            force = kg_reading * GRAVITY;
		} 
	}

	float getForceN() {
		return force - getRawOffset();
	}
};

#endif