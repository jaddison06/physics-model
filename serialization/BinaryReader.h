#pragma once

#include "serialization/BinaryShared.h"
#include "control/ObjectHandler.h"

class BinaryReader: public GenericBaseClass {
    public:
        BinaryReader();

        void ReadBinary(ObjectHandler *objectHandler, std::string fname);
    
    private:


        void inheritedDestroy();
};