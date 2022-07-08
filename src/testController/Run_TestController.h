#ifndef __SKETCH__
#define __SKETCH__


#include "FingerLowLevelController.h"

#include "externalInterface/JointSpaceCommandInterface.h"
#include "externalInterface/ArduinoCommandInterface.h"
#include "externalInterface/JavaCommandInterface.h"
#include "externalInterface/ControlMode.h"

#include "../ArduinoSketch.h"
#include "hardwareInterface/HardwareParameters.h"

class Run_TestController : public ArduinoSketch
{
    FingerLowLevelController fingerLowLevelController;
    Timer sendTimer;
    float sendTime = 0.01;


public:
    Run_TestController() = default;
    void setup()
    {
        HardwareParameters hp = HardwareParameters();
        ControllerParameters cp = ControllerParameters();
        fingerLowLevelController = FingerLowLevelController(hp, cp);
        fingerLowLevelController.hardwareSetup();

        sendTimer.set(sendTime);
    }

    void loop()
    {
        JointSpaceCommand jointSpaceCommand = JointSpaceCommand();
        fingerLowLevelController.submitCommand(jointSpaceCommand);
        fingerLowLevelController.doControl();

        SensorData sensorData = fingerLowLevelController.getMeasurements();
        if (sendTimer.isRinging())
        {
            sendTimer.restart();
            Serial.println(sensorData.angle1);
            Serial.println();
        }
    }
};

#endif