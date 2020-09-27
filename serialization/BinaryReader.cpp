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

    char bytes[fileSize];

    std::ifstream fh(fpath, std::ios::binary);

    fh.read(bytes, fileSize);

    fh.close();

    logger.info("Loaded data");

    std::string binData;
    for (int i=0; i<(sizeof(bytes)/sizeof(char)); i++) {
        binData += makeByte(decimalToBinary(((int)bytes[i])));
    }

    // check ID bits

    std::string startBits = binData.substr(0, 8);
    std::string endBits = binData.substr(binData.length()-16, 16);

    logger.info("First 8 bits: "+startBits);
    logger.info("Last 16 bits: "+endBits);

    /*
    if (!(startBits == "01000101" && endBits == "0000000110100100")) {
        logger.warning("ID bits are incorrect, file corrupt");
        return;
    }
    */

    std::string versionBits = binData.substr(8, 8);
    
    logger.info("Version bits: "+versionBits);
    int version = binaryToDecimal(versionBits);

    if (version != VERSION) {
        logger.warning("Outdated file: file version is "+std::to_string(version)+", current version is VERSION");
    }

    // actual parsing happens here
    //
    // for new versions, add extra code while trying to
    // maintain compatibility
    switch (version) {
        case 1: {
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
    memcpy(output, &binary, sizeof(binary));
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
