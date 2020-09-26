#pragma once

#include "control/ObjectHandler.h"
#include "control/GenericBaseClass.h"


// something here is causing a phat segfault

class Model: public GenericBaseClass {
    public:
        Model();

        void Start( bool (*exitFunc)(Logger *) );
    private:
        bool isRunning;
        void Tick();
        void inheritedDestroy();

        ObjectHandler objectHandler;

};