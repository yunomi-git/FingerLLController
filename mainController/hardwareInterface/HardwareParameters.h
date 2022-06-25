#ifndef __PARAMETERS__
#define __PARAMETERS__

struct HardwareParameters
{
    HardwareParameters()
    {        
        motorDriver1.ENA_PIN = 10;
        motorDriver1.DIR1_PIN = 8;
        motorDriver1.DIR2_PIN = 9;

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

    float MOTOR_VOLTAGE = 12.0;
    byte POT_1_READ_PIN = 15;
    byte POT_2_READ_PIN = 16;

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


};

#endif