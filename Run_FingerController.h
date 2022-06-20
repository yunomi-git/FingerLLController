#ifndef __RUN_FING_CONTROL__
#define __RUN_FING_CONTROL__


#include "FingerLowLevelController.h"
#include "InputCommandReader.h"
#include "ArduinoInputCommand.h"
#include "JavaInputCommand.h"
#include "ArduinoSketch.h"
#include "Parameters.h"

class Run_FingerController : public ArduinoSketch
{
    FingerLowLevelController fingerLowLevelController;
    InputCommandReader inputCommandReader;
    OutputWriter outputWriter;
    bool useArduinoInput = true;

    Run_FingerController() = default;

    void setup()
    {
        HardwareParameters hp = HardwareParameters();
        ControllerParameters cp = ControllerParameters();
        fingerLowLevelController = FingerLowLevelController(hp, cp);

        if (useArduinoInput)
        {
            inputCommandReader = ArduinoInputCommand();
        }
        else
        {
            inputCommandReader = JavaInputCommand();
        }
    }

    void loop()
    {
        inputCommandReader.update();
        InputCommand inputCommand = inputCommandReader.getInputCommand();

        float dt = getDT();

        fingerLowLevelController.submitCommand(inputCommand);
        fingerLowLevelController.doControl(dt);
        SensorData sensorData = fingerLowLevelController.getMeasurements(dt);

        outputWriter.write(sensorData);
    }
}

#endif