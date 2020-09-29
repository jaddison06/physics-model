#include "serialization/BinaryReader.h"

BinaryReader::BinaryReader() {
    logger.setSender("BinaryReader");

    logger.info("BinaryReader initialized");
}


void BinaryReader::ReadBinary(ObjectHandler *objectHandler, std::string fname) {
    logger.info("Reading binary");

    std::string fpath = "./data/models/" + fname;

    char cfpath[fpath.size() + 1];
    strcpy(cfpath, fpath.c_str());

    struct stat results;
    stat(cfpath, &results);
    
    int fileSize = results.st_size;

    unsigned char bytes[fileSize];

    std::ifstream fh(fpath, std::ios::binary);

    fh.read(bytes, fileSize);

    fh.close();

    logger.info("Loaded data");

    std::string binData;
    for (int i=0; i<(sizeof(bytes)/sizeof(unsigned char)); i++) {
        binData += makeByte(decimalToBinary(((int)bytes[i])));
    }

    logger.info("Entire binary is "+binData);

    // check ID bits
    std::string startBits = binData.substr(0, 8);
    std::string endBits = binData.substr(binData.length()-16, 16);

    logger.info("First 8 bits: "+startBits);
    logger.info("Last 16 bits: "+endBits);

    /*
    if (!(startBits == "01000101" && endBits == "0000000110100100")) {
        logger.warning("ID bits are incorrect, file corrupt");
        return;
    }*/
    

    std::string versionBits = binData.substr(8, 8);
    
    logger.info("Version bits: "+versionBits);
    int version = binaryToDecimal(versionBits);

    if (version != VERSION) {
        logger.warning("Outdated file: file version is "+std::to_string(version)+", current version is "+std::to_string(VERSION));
    }

    // actual parsing happens here
    //
    // for new versions, add extra code while trying to
    // maintain compatibility
    switch (version) {
        case 0: {
            int objectCount;
            std::string objCountBits = binData.substr(16, 8);

            logger.info("Object count bits: "+objCountBits);
            objectCount = binaryToDecimal(objCountBits);
            logger.info("Object count: "+std::to_string(objectCount));

            int objectLength = ((sizeof(double) * 11) + 8);
            int coordLength = sizeof(double) * 3;
            int bodyTypeLength = 8;
            // this is the good bit
            for (int i=0; i<objectCount; i++) {
                logger.info("Deserializing object "+std::to_string(i));

                int startPos = ((i + 1) *  objectLength) + 24;
                
                std::string thisObject = binData.substr(startPos, objectLength);

                coord pos, vel, accel;

                deserializeCoord(thisObject.substr(coordLength * 0, coordLength), &pos);
                deserializeCoord(thisObject.substr(coordLength * 1, coordLength), &vel);
                deserializeCoord(thisObject.substr(coordLength * 2, coordLength), &accel);

                double size, mass;

                deserializeDouble(thisObject.substr((coordLength * 3) + (sizeof(double) * 0), sizeof(double)), &size);
                deserializeDouble(thisObject.substr((coordLength * 3) + (sizeof(double) * 1), sizeof(double)), &mass);

                bodyType shape;

                deserializeBodyType(thisObject.substr((coordLength * 3) + (sizeof(double) * 2), bodyTypeLength), &shape);

                objectHandler->Add(pos, vel, accel, size, mass, shape);
            }


            break;
        }
    }
}

void BinaryReader::deserializeCoord(std::string binary, coord *output) {
    deserializeDouble((binary.substr(sizeof(double) * 0, sizeof(double))), &(output->x));
    deserializeDouble((binary.substr(sizeof(double) * 1, sizeof(double))), &(output->y));
    deserializeDouble((binary.substr(sizeof(double) * 2, sizeof(double))), &(output->z));

}

void BinaryReader::deserializeDouble(std::string binary, double *output) {
    std::string sign = binary.substr(0, 8);

    // get the length of the first int
    std::string int1LengthBinary = binary.substr(8, 8);

    // length stored in BYTES
    int int1Length = binaryToDecimal(int1LengthBinary) * 8;
    

    // repeat
    std::string int2LengthBinary = binary.substr(int1Length+16, 8);
    int int2Length = binaryToDecimal(int2LengthBinary) * 8;

    // and again
    std::string int3LengthBinary = binary.substr(int1Length+24+int2Length, 8);
    int int3Length = binaryToDecimal(int3LengthBinary) * 8;
    
    int int1, int2, int3;
    deserializeInt(binary.substr(8, int1Length), &int1);
    deserializeInt(binary.substr(int1Length+8, int2Length), &int2);
    deserializeInt(binary.substr(int1Length+8+int2Length, int3Length), &int3);

    double decimalPart = int2;
    for (int i=0; i < int3; i++) {
        decimalPart *= 0.1;
    }

    *output = int1 + decimalPart;

    return;

}

void BinaryReader::deserializeInt(std::string binary, int* output) {
    // get rid of size byte, we don't care
    binary = binary.substr(8, binary.length()-8);

    int unsignedData;

    std::string sign = binary.substr(0, 8);
    std::string data = binary.substr(8, binary.length()-8);

    unsignedData = binaryToDecimal(data);

    if (sign == "00000000") {
        // positive
        *output = unsignedData;
    } else if (sign == "00000001") { 
        // negative
        *output = 0 - unsignedData;
    } else {
        // errors are entirely possible
        logger.warning("Tried to deserialize int, signing was "+sign);
        *output = 69;
    }

    return;


}

void BinaryReader::deserializeBodyType(std::string binary, bodyType *output) {
    switch(binaryToDecimal(binary)) {
        case 0: {
            *output = cube;
            break;
        }
        case 1: {
            *output = sphere;
            break;
        }
    }
}

void BinaryReader::inheritedDestroy() {

}
