#pragma once

#include "control/logging.h"
#include "control/ObjectHandler.h"


// something here is causing a phat segfault

class Model {
    public:
        Model();

        void Start( bool (*exitFunc)(Logger *) );
    private:
        bool isRunning;
        void Tick();
        void Shutdown();

        Logger logger {"Model"};
        ObjectHandler objectHandler;

};