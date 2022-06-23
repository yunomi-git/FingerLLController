#ifndef __TIMER__
#define __TIMER__

#include <arduino.h>

#define TIME_INFINITE -1

// TODO: cant do Timer a; a = Timer(xxx); or an error will happen...not sure why
// Used to time the length of functions or create a delay.
// Can be set to check milliseconds or microseconds.
// Interaction is always in seconds
struct Timer {
private:
    long timeStartAbs; // in appropriate unit
    float periodSec;
    long periodUnit;
    unsigned long (*checkTimeAbs)();
    bool using_precision;

    bool isTicking;
public:
    // time finish in seconds
    Timer(float ntime_finish=0) {
        checkTimeAbs = millis;
        timeStartAbs = checkTimeAbs();
        using_precision = false;
        isTicking = false;

        setPeriodInSec(ntime_finish);
    }

    void usePrecision()  {
        checkTimeAbs = micros;
        using_precision = true;
        periodUnit = convertSecToUnit(periodSec);
    }

private: 
    long convertSecToUnit(float t) {
        if (using_precision) {
            return (long) (t * 1000000);
        } else {
            return (long) (t * 1000);
        }
    }

    float convertUnitToSec(long t) {
        if (using_precision) {
            return t / 1000000.0;
        } else {
            return t / 1000.0;
        }
    }

    void setPeriodInSec(float s) {
        periodSec = s;
        periodUnit = convertSecToUnit(periodSec);
    }

public:
    // Starts the timer to run for t ms.
    void set(float t) {
        timeStartAbs = checkTimeAbs();
        setPeriodInSec(t);
        isTicking = true;
    }

    void restart() {
        set(periodSec);
    }

    // Returns whether the time has elapsed
    bool isRinging() {
        if (checkTimeLeftUnit() <= 0.0 && isTickingDown()) {
            return true;
        } else {
            return false;
        }
    }

    void stopRinging() {
        isTicking = false;
    }

    bool isTickingDown() {
        return isTicking;
    }

    float dt() {
        return convertUnitToSec(checkTimeAbs() - timeStartAbs);
    }

private:
    float checkTimeLeftUnit() {
        return (long) (timeStartAbs + periodUnit - checkTimeAbs());
    }

public:
    float checkTimeLeftSec() {
        return convertUnitToSec(checkTimeLeftUnit());
    }
};

#endif