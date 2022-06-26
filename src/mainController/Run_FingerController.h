#ifndef __SKETCH__
#define __SKETCH__


#include "FingerLowLevelController.h"

#include "externalInterface/JointSpaceCommandInterface.h"
#include "externalInterface/ArduinoCommandInterface.h"
#include "externalInterface/JavaCommandInterface.h"

#include "../ArduinoSketch.h"
#include "hardwareInterface/HardwareParameters.h"

class Run_FingerController : public ArduinoSketch
{
    FingerLowLevelController fingerLowLevelController;
    JointSpaceCommandInterface *jointSpaceCommandInterface;
    bool useArduinoInput = true;

public:
    Run_FingerController() = default;
    void setup()
    {
        HardwareParameters hp = HardwareParameters();
        ControllerParameters cp = ControllerParameters();
        fingerLowLevelController = FingerLowLevelController(hp, cp);

        if (useArduinoInput)
        {
            jointSpaceCommandInterface = new ArduinoInputCommand(hp.POT_1_READ_PIN, hp.POT_2_READ_PIN);
        }
        else
        {
            jointSpaceCommandInterface = new JavaCommandInterface();
        }
    }

    void loop()
    {
        JointSpaceCommand jointSpaceCommand = jointSpaceCommandInterface->recieve();

        fingerLowLevelController.submitCommand(jointSpaceCommand);
        fingerLowLevelController.doControl();
        SensorData sensorData = fingerLowLevelController.getMeasurements();

        jointSpaceCommandInterface->send(sensorData);
    }
};

#endif