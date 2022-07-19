#ifndef __FIN_PID__
#define __FIN_PID__

// #include "Timer.h"
#include "../util/MathUtil.h"
#include "../util/AlphaFilter.h"
#include "../util/Derivative.h"

struct PIDGains {
	float kp;
	float ki;
	float kd;
	float maxIntegrator;
	float maxControl;
	float minControl;
	float alphaDerivative;
	float derivativeTime;

	PIDGains()
	{
		alphaDerivative = 1.0;
		maxIntegrator = __FLT_MAX__;
		maxControl = __FLT_MAX__;
		minControl = __FLT_MIN__;
	}
};

class PIDController {
public:
	PIDController() = default;
	
	PIDController(PIDGains gains) 
	{
		this->gains = gains;
		prevError = 0.0;
		errorIntegrator = 0.0;
		errorDerivative = Derivative(gains.derivativeTime);
	}

	void setPIDGains(PIDGains gains) {
		this->gains = gains;
	}

	void resetIntegrator()
	{
		errorIntegrator = 0.0;
	}

	float stepAndGet(float error, float dt) 
	{
		errorDerivative.update(error, dt);
		float derror = errorDerivative.getDerivative();

		float controlNoIntegrator = gains.kp * error +
									gains.kd * derror;

		errorIntegrator += gains.ki * error * dt;
		float maxErrorIntegrator = fmin(gains.maxIntegrator, 					 // default integrator maximum
										gains.maxControl - controlNoIntegrator); // integrator should not exceed control maximum
		float minErrorIntegrator = fmax(-gains.maxIntegrator, 					 // default integrator minimum
										gains.minControl - controlNoIntegrator); // integrator should not exceed control minimum
		errorIntegrator = fbound(errorIntegrator, minErrorIntegrator, maxErrorIntegrator);

		float control = errorIntegrator + controlNoIntegrator;

		return control;
	}

private:
	PIDGains gains;

	float prevError;
	float errorIntegrator;
	Derivative errorDerivative;
};

#endif