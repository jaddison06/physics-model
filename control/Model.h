#pragma once

#include "control/ObjectHandler.h"
#include "control/GenericBaseClass.h"
#include "serialization/BinaryCreator.h"
#include "serialization/BinaryReader.h"

#include <SDL/SDL.h>

class Model: public GenericBaseClass {
    public:
        Model();
        ~Model();

        void Start( bool (*exitFunc)(Logger *) );
    private:
        bool isRunning;
        void Tick();

        // this might have to be public so we 
        // can pass it to the binaryCreator
        ObjectHandler *objectHandler;

        BinaryCreator *binaryCreator;
        BinaryReader *binaryReader;

};