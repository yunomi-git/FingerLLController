#ifndef __FIN_MATH__
#define __FIN_MATH__

float fmap(float x, float inMin, float inMax, float outMin, float outMax)
{
    return (outMax - outMin) / (inMax - inMin) * (x - inMin) + outMin;
}

float fbound(float x, float min, float max) {
	if (x > max) {
		return max;
	}
	if (x < min) {
		return min;
	}
	return x;
};

float fixedAbs(float x) {
	if (x < 0) {
		return -x;
	} else {
		return x;
	}
}

bool within(float x, float low, float high) {
	if (x > low && x < high) {
		return true;
	} 
	return false;
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


#endif