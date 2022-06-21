#ifndef __PARAMETERS__
#define __PARAMETERS__

#include "PIDController.h"

struct HardwareParameters
{
    struct MotorDriverParam
    {
        float SUPPLY_VOLTAGE;
        byte ENA_PIN;
        byte DIR1_PIN;
        byte DIR2_PIN;
    };

    struct SensorParameters
    {
        struct AngleSensorParam
        {
            byte READ_PIN;
            byte ALPHA;
        };

        struct TorqueSensorParam
        {
            byte READ_PIN;
            float SCALE;
            float RAW_OFFSET;
        };

        AngleSensorParam angle1;
        AngleSensorParam angle2;
        TorqueSensorParam torque1;
        TorqueSensorParam torque2;
    };

    MotorDriverParam motorDriver1;
    MotorDriverParam motorDriver2;
    SensorParameters sensorParameters;

    HardwareParameters()
    {
        motorDriver1.SUPPLY_VOLTAGE = 12.0;
        motorDriver1.ENA_PIN = 10;
        motorDriver1.DIR1_PIN = 8;
        motorDriver1.DIR2_PIN = 9;

        motorDriver2.SUPPLY_VOLTAGE = 12.0;
        motorDriver2.ENA_PIN = 10;
        motorDriver2.DIR1_PIN = 8;
        motorDriver2.DIR2_PIN = 9;

        sensorParameters.angle1.READ_PIN = 15;
        sensorParameters.angle2.READ_PIN = 16;
        sensorParameters.angle1.ALPHA = 0.8;
        sensorParameters.angle2.ALPHA = 0.8;
        
        sensorParameters.torque1.READ_PIN = 17;
        sensorParameters.torque1.SCALE = 3.2;
        sensorParameters.torque1.RAW_OFFSET = 0.513;
        sensorParameters.torque2.READ_PIN = 17;
        sensorParameters.torque2.SCALE = 3.2;
        sensorParameters.torque2.RAW_OFFSET = 0.513;
    }


};

struct ControllerParameters
{
    PIDGains angle1Gains;
    PIDGains angle2Gains;
    PIDGains torque1Gains;
    PIDGains torque2Gains;

    ControllerParameters()
    {
        angle1Gains.kp = 1.0;
        angle1Gains.kd = 0.0;
        angle1Gains.ki = 0.0;
        angle1Gains.maxIntegrator = 0.0;

        angle2Gains.kp = 1.0;
        angle2Gains.kd = 0.0;
        angle2Gains.ki = 0.0;
        angle2Gains.maxIntegrator = 0.0;

        torque1Gains.kp = 1.0;
        torque1Gains.kd = 0.0;
        torque1Gains.maxIntegrator = 0.0;

        torque2Gains.kp = 1.0;
        torque2Gains.kd = 0.0;
        torque2Gains.ki = 0.0;
        torque2Gains.maxIntegrator = 0.0;
    }
};

struct CalibrationHardwareParameters
{
    const byte HX_DOUT_PIN = 21;
    const byte HX_SCK_PIN = 22;

    const byte POT_READ_PIN = 15;

    const byte ENC_A_PIN = 3;
    const byte ENC_B_PIN = 4;
    const float ENCODER_STEPS_PER_REV = 2400;
};


#endif