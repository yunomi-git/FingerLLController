#ifndef __PARAMETERS__
#define __PARAMETERS__

#include <Arduino.h>

struct HardwareParameters
{
    HardwareParameters()
    {        
        motorDriver1.ENA_PIN = 2;
        motorDriver1.DIR1_PIN = 3; // in1
        motorDriver1.DIR2_PIN = 4; // in2

        motorDriver2.DIR2_PIN = 5; // in3
        motorDriver2.DIR1_PIN = 6; // in4
        motorDriver2.ENA_PIN = 7;

        sensorParameters.angle1.READ_PIN = 23;
        sensorParameters.angle1.ALPHA = 0.8;

        sensorParameters.angle2.READ_PIN = 22;
        sensorParameters.angle2.ALPHA = 0.8;
        
        sensorParameters.torque1.READ_PIN = 20;
        sensorParameters.torque1.SCALE = 2.7;
        sensorParameters.torque1.RAW_OFFSET = 0.4941;
        sensorParameters.torque1.DEADBAND = 0.02;

        sensorParameters.torque2.READ_PIN = 21;
        sensorParameters.torque2.SCALE = 2.7;
        sensorParameters.torque2.RAW_OFFSET = 0.4916;
        sensorParameters.torque1.DEADBAND = 0.02;


        
        // sensorParameters.angle1.READ_PIN = 19;
        // sensorParameters.angle2.READ_PIN = 18;
        // sensorParameters.angle1.ALPHA = 0.8;
        // sensorParameters.angle2.ALPHA = 0.8;
        
        // sensorParameters.torque1.READ_PIN = 17;
        // sensorParameters.torque1.SCALE = 3.2;
        // sensorParameters.torque1.RAW_OFFSET = 0.513;

        // sensorParameters.torque2.READ_PIN = 16;
        // sensorParameters.torque2.SCALE = 3.2;
        // sensorParameters.torque2.RAW_OFFSET = 0.513;
    }

    float MOTOR_VOLTAGE = 12.0;
    byte POT_1_READ_PIN = 15;
    byte POT_2_READ_PIN = 14;

    float MAX_ANGLE_1 = 90;
    float MAX_ANGLE_2 = 90;
    float MAX_TORQUE = 0.1;

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
            float DEADBAND;
        };

        AngleSensorParam angle1;
        AngleSensorParam angle2;
        TorqueSensorParam torque1;
        TorqueSensorParam torque2;
    };

    MotorDriverParam motorDriver1;
    MotorDriverParam motorDriver2;
    SensorParameters sensorParameters;


};

#endif