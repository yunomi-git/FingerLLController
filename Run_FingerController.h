#ifndef __RUN_FING_CONTROL__
#define __RUN_FING_CONTROL__


#include "FingerLowLevelController.h"
#include "InputCommandReader.h"
#include "ArduinoInputCommand.h"
#include "JavaInputCommand.h"
#include "ArduinoSketch.h"
#include "Parameters.h"
#include "OutputWriter.h"

class Run_FingerController : public ArduinoSketch
{
    FingerLowLevelController fingerLowLevelController;
    InputCommandReader *inputCommandReader;
    OutputWriter *outputWriter;
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
            inputCommandReader = new ArduinoInputCommand();
        }
        else
        {
            inputCommandReader = new JavaInputCommand();
        }
    }

    void loop()
    {
        inputCommandReader->read();
        InputCommand inputCommand = inputCommandReader->getInputCommand();

        fingerLowLevelController.submitCommand(inputCommand);
        fingerLowLevelController.doControl();
        SensorData sensorData = fingerLowLevelController.getMeasurements();

        outputWriter->write(sensorData);
    }
};

#endif