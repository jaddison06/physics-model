#pragma once

#include "control/ObjectHandler.h"
#include "control/GenericBaseClass.h"
#include "serialization/BinaryCreator.h"

// something here is causing a phat segfault

class Model: public GenericBaseClass {
    public:
        Model();

        void Start( bool (*exitFunc)(Logger *) );
    private:
        bool isRunning;
        void Tick();
        void inheritedDestroy();

        // this might have to be public so we 
        // can pass it to the binaryCreator
        ObjectHandler objectHandler;

        BinaryCreator binaryCreator;

};