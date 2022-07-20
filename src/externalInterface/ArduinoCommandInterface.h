#ifndef __AICR__
#define __AICR__

#include "Arduino.h"
#include "../packets/JointSpaceCommand.h"
#include "../packets/ControlMode.h"
#include "../hardware/Potentiometer.h"
#include "JointSpaceCommandInterface.h"

class ArduinoInputCommand : public JointSpaceCommandInterface
{
    Potentiometer pot1;
    Potentiometer pot2;
    ControlMode controlMode;

    float maxVoltage;
    float maxTorque;
    float maxAngle1;
    float maxAngle2;

    JointSpaceCommand jointSpaceCommand;
 public:   
    ArduinoInputCommand() = default;
    
    ArduinoInputCommand(ControlMode controlMode, byte POT1_READ_PIN, byte POT2_READ_PIN, HardwareParameters hp)
    {
        pot1 = Potentiometer(POT1_READ_PIN);
        pot2 = Potentiometer(POT2_READ_PIN);
        this->controlMode = controlMode;
        this->maxVoltage = hp.MOTOR_VOLTAGE;
        this->maxAngle1 = hp.MAX_ANGLE_1;
        this->maxAngle2 = hp.MAX_ANGLE_2;
        this->maxTorque = hp.MAX_READ_TORQUE;
    }

    void hardwareSetup()
    {
        pot1.hardwareSetup();
        pot2.hardwareSetup();
    }

    JointSpaceCommand recieve()
    {
        jointSpaceCommand.mode = controlMode;
        float read1 = pot1.getReadingNormalized();
        float read2 = pot2.getReadingNormalized();
        switch (controlMode)
        {
            case TORQUE:
                jointSpaceCommand.input1 = (read1 - 0.5) * maxTorque * 2;
                jointSpaceCommand.input2 = (read2 - 0.5) * maxTorque * 2;
            case POSITION:
                jointSpaceCommand.input1 = read1 * maxAngle1;
                jointSpaceCommand.input2 = read2 * maxAngle2;
            case VOLTAGE:
                // jointSpaceCommand.input1 = (read1) ;
                // jointSpaceCommand.input2 = (read2) ;
                jointSpaceCommand.input1 = (read1 - 0.5) * 2.0 * maxVoltage;
                jointSpaceCommand.input2 = (read2 - 0.5) * 2.0 * maxVoltage;
        }

        return jointSpaceCommand;
    }

    void send(SensorData sensorData)
    {
        Serial.print(jointSpaceCommand.input1); Serial.print(",");
        Serial.print(jointSpaceCommand.input2); 
        Serial.println();
    }
};

#endif