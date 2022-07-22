#ifndef __SKETCH__
#define __SKETCH__

#include "ArduinoSketch.h"
#include <Arduino.h>
#include "../externalInterface/JavaCommandInterface.h"
#include "../packets/SensorData.h"
#include "../mainController/hardwareInterface/HardwareParameters.h"
#include "../Constants.h"
#include "../util/Timer.h"
#include "../mainController/hardwareInterface/HardwareParameters.h"
#include "../hardware/PT15AngleSensor.h"
#include "../externalInterface/ArduinoCommandInterface.h"
#include "../hardware/L298NMotorDriver.h"


class __MotorPlayground : public ArduinoSketch
{
    ArduinoInputCommand commandInterface;
    L298NMotorDriver motorDriver;
    HardwareParameters hp;
    bool useMotor1 = true;


public:
    __MotorPlayground()
    {
    }
        
    void setup()
    {
        hp = HardwareParameters();
        commandInterface = ArduinoInputCommand(ControlMode::VOLTAGE, hp.POT_1_READ_PIN, hp.POT_2_READ_PIN, hp);
        commandInterface.hardwareSetup();
        if (useMotor1)
        {
            motorDriver = L298NMotorDriver(hp.MOTOR_VOLTAGE, hp.motorDriver1.ENA_PIN, hp.motorDriver1.DIR1_PIN, hp.motorDriver1.DIR2_PIN);
            motorDriver.setDirection(NEGATIVE_DIRECTION);
        }
        else
        {
            motorDriver = L298NMotorDriver(hp.MOTOR_VOLTAGE, hp.motorDriver2.ENA_PIN, hp.motorDriver2.DIR1_PIN, hp.motorDriver2.DIR2_PIN);
            
        }
        motorDriver.hardwareSetup();
    }

    void loop()
    {
        JointSpaceCommand jointSpaceCommand = commandInterface.recieve();

        motorDriver.submitVoltage(jointSpaceCommand.input1);
        motorDriver.write();

        Serial.print(jointSpaceCommand.input1); Serial.print(",");
        Serial.print(jointSpaceCommand.input2); 
        Serial.println();
    }

};

#endif