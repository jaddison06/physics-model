#pragma once

#include <fstream>
#include <string>
#include <bitset>
#include "control/GenericBaseClass.h"
#include "control/ObjectHandler.h"
#include "serialization/BinaryShared.h"

#define VERSION 1

class BinaryCreator: public GenericBaseClass {
    public:
        BinaryCreator();

        void CreateBinary(ObjectHandler *objectHandler);
    
    private:

        std::string makeByte(std::string input);
        std::string setLength(std::string input, int targetLength);

        std::string createBinData(ObjectHandler *objectHandler);
        std::string binaryToString(std::string binary);
        void writeToFile(std::string chars);

        void inheritedDestroy();


};
