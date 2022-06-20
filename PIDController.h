#ifndef __FIN_PID__
#define __FIN_PID__

// #include "Timer.h"
#include "MathUtil.h"

struct PIDGains {
	float kp;
	float ki;
	float kd;
	float maxIntegrator;
};

class PIDController {
public:
	PIDController(PIDGains gains) 
	{
		this.gains = gains;
		prevError = 0.0;
		// dt_timer.reset();
		// dt_timer.usePrecision();
	}

	// void bindErrorReference(float *nerror_ref) {
	// 	error_ref = nerror_ref;
	// }

	void setPIDGains(PIDGains gains) {
		this.gains = gains;
	}

	void resetIntegrator()
	{
		self.errorIntegrator = 0.0;
	}

	float stepAndGet(float error, float dt) {
		// float error = *error_ref;
		// float dt = dt_timer.dtSec();
		// dt_timer.reset();
		float derror = (error - this.prevError) / dt;
		prevError = error;

		errorIntegrator += error * dt;
		errorIntegrator = fbound(errorIntegrator, -gains.maxIntegrator, gains.maxIntegrator);

		float control = gains.kp * error +
						gains.ki * errorIntegrator +
						gains.kd * derror;
		return control;
	}

private:
	// Timer dt_timer;
	PIDGains gains;

	// float *error_ref;
	float prevError;
	float errorIntegrator;
};

#endif