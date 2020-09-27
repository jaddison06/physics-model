#pragma once

#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "control/GenericBaseClass.h"
#include "control/ObjectHandler.h"
#include "serialization/BinaryShared.h"

#define VERSION 1

class BinaryCreator: public GenericBaseClass {
    public:
        BinaryCreator();

        void CreateBinary(ObjectHandler *objectHandler, std::string fname);
    
    private:

        std::string makeByte(std::string input);
        std::string setLength(std::string input, int targetLength);

        std::string charToString(char chars[]);

        std::string createBinData(ObjectHandler *objectHandler);
        
        std::string serializeObject(Object *object);
        std::string serializeCoord(coord *coords);
        std::string serializeDouble(double *someDouble);
        std::string serializeBodyType(bodyType *bType);

        std::string binaryToString(std::string binary);
        void writeToFile(std::string chars, std::string fname);

        void inheritedDestroy();


};
