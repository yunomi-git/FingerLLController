#ifndef __FINENCODER__
#define __FINENCODER__

#include <arduino.h>
#include "Constants.h"
#include "Timer.h"

class Encoder {

#define DEFAULT_STALL_TIME 0.04 // encoder is considered "not moving" if stall_time passes without a new motion
                                // Higher value => lower velocity detectable, but longer delay to detect stop.
public:
    Encoder() {
        frame_direction = 1;
        timer.restart();
        timer.usePrecision();
    }

    // If constructor cannot be called, use this
    void hardwareSetup(int nsteps_per_rev) {
        steps_per_rev = nsteps_per_rev;
    }

  // parameters
    void setStallTime(float nstall_time) {
        timer.reset(nstall_time);
        stall_time = nstall_time;
    }

    void switchReferenceFrame() {
        frame_direction *= -1;
    }

// Data
    void update() {
        last_angle = absolute_angle;
        absolute_angle = getRawStep() * DEG_PER_REV/steps_per_rev * frame_direction;
        float dangle = absolute_angle - last_angle;

        float dt = timer.dt();

        // update velocity based on: time since last tick, and change in tick
        // if change in tick != 0, take change/time since last tick
        // if change in tick is 0, do not update velocity
        // if change in tick is 0 for too long, update velocity to 0
        if (dangle != 0) {
            velocity = dangle/dt;
            unsetStall();
        } else {
            if (dt > stall_time) {
                velocity = 0;
                unsetStall();
            } else {
                // do nothing
            }
        }
    }

    float getAbsoluteAngleDeg() {
        return absolute_angle;
    }

    // should verify
    float getLimitedAngleDeg() {
        int limited_angle = fmod(absolute_angle, DEG_PER_REV);
        if (limited_angle < 0) 
            limited_angle += DEG_PER_REV;
        return limited_angle;
    }

    long getVelocityDeg() {
        return velocity;
    }


protected:
    virtual int getRawStep()  = 0;

private:
    float absolute_angle = 0;
    float velocity = 0;
    float last_angle = 0;

    int steps_per_rev;
    float stall_time = DEFAULT_STALL_TIME;
    int frame_direction; // User-set frame of reference

    Timer timer;   // Counts time since last step
    void unsetStall() {
        timer.restart();
    }

};

#endif