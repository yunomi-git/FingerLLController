#ifndef __SKETCH__
#define __SKETCH__


#include "FingerLowLevelController.h"

#include "../externalInterface/JointSpaceCommandInterface.h"
#include "../externalInterface/ArduinoCommandInterface.h"
#include "../externalInterface/JavaCommandInterface.h"
#include "../packets/ControlMode.h"

#include "../ArduinoSketch.h"
#include "hardwareInterface/HardwareParameters.h"

class Run_FingerController : public ArduinoSketch
{
    FingerLowLevelController fingerLowLevelController;
    // JointSpaceCommandInterface *jointSpaceCommandInterface;
    bool useArduinoInput = true;
    Timer sendTimer;
    float sendTime = 0.01;


public:
    Run_FingerController() = default;
    void setup()
    {
        HardwareParameters hp = HardwareParameters();
        ControllerParameters cp = ControllerParameters();
        fingerLowLevelController = FingerLowLevelController(hp, cp);
        fingerLowLevelController.hardwareSetup();

        // if (useArduinoInput)
        // {
        //     jointSpaceCommandInterface = new ArduinoInputCommand(ControlMode::VOLTAGE, hp.POT_1_READ_PIN, hp.POT_2_READ_PIN, hp);
        // }
        // else
        // {
        //     jointSpaceCommandInterface = new JavaCommandInterface();
        // }
        sendTimer.set(sendTime);
    }

    void loop()
    {
        // JointSpaceCommand jointSpaceCommand = jointSpaceCommandInterface->recieve();

        // fingerLowLevelController.submitCommand(jointSpaceCommand);
        fingerLowLevelController.doControl();

        SensorData sensorData = fingerLowLevelController.getMeasurements();
        if (sendTimer.isRinging())
        {
            sendTimer.restart();
            Serial.print(sensorData.torque1); Serial.print(",");
            Serial.print(sensorData.torque2); //Serial.print(",");
            // Serial.print(sensorData.velocity1); //Serial.print(",");
            // Serial.print(sensorData.velocity2); 
            Serial.println();

            // jointSpaceCommandInterface->send(sensorData);
        }
    }
};

#endif