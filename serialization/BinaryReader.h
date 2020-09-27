#pragma once

#include "serialization/BinaryShared.h"
#include "control/ObjectHandler.h"
#include <sys/stat.h>

class BinaryReader: public GenericBaseClass {
    public:
        BinaryReader();

        void ReadBinary(ObjectHandler *objectHandler, std::string fname);
    
    private:


        void inheritedDestroy();
};