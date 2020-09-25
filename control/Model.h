#pragma once

#include "control/logging.h"
#include "control/ObjectHandler.h"

void initLogging();

class Model {
    public:
        Model();

        void Start( bool (exitFunc)(Logger *logger) );
    private:
        bool isRunning;
        void Tick();
        void Shutdown();

        Logger logger {"Model"};
        ObjectHandler objectHandler;

};