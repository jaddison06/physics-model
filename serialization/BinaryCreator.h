#pragma once

#include <vector>
#include "control/ObjectHandler.h"
#include "serialization/BinaryShared.h"

class BinaryCreator: public GenericBaseClass {
    public:
        BinaryCreator();

        void CreateBinary(ObjectHandler *objectHandler, std::string fname);
    
    private:

        std::string charToString(char chars[]);

        std::string createBinData(ObjectHandler *objectHandler);
        
        std::string serializeObject(Object *object);
        std::string serializeCoord(coord *coords);
        std::string serializeDouble(double *someDouble);
        std::string serializeInt(int *someInt);
        std::string serializeBodyType(bodyType *bType);

        std::string binaryToString(std::string binary);
        void writeToFile(std::string chars, std::string fname);

        void inheritedDestroy();


};
