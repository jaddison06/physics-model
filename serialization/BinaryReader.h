#pragma once

#include "serialization/BinaryShared.h"
#include "control/ObjectHandler.h"
#include <sys/stat.h>

class BinaryReader: public GenericBaseClass {
    public:
        BinaryReader();

        void ReadBinary(ObjectHandler *objectHandler, std::string fname);
    
    private:
        void deserializeCoord(std::string binary, coord *output);
        void deserializeDouble(std::string binary, double *output);
        void deserializeInt(std::string binary, int *output);
        void deserializeBodyType(std::string binary, bodyType *output);

        void inheritedDestroy();
};