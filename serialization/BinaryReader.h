#pragma once

#include "serialization/BinaryShared.h"
#include "control/ObjectHandler.h"
#include <sys/stat.h>

class BinaryReader: public GenericBaseClass
{
    public:
        BinaryReader();

        void ReadBinary(ObjectHandler *objectHandler, std::string fname);
    
    private:
        coord deserializeCoord(std::string binary);
        double deserializeDouble(std::string binary);
        int deserializeInt(std::string binary);
        bodyType deserializeBodyType(std::string binary);

        void shiftCursor(std::string *thisObject, int *cursor, int *itemSize);
        int getSize(std::string *binary, int startPoint = 0);

        int signInt(int *unsignedData, std::string *sign);
        double signDouble(double *unsignedData, std::string *sign);
};