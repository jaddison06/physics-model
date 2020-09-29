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

    fh.read((char*)&bytes, fileSize);

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

    
    if (!(startBits == "01000101" && endBits == "0000000110100100")) {
        logger.warning("ID bits are incorrect, file corrupt");
        return;
    }
    

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
        case 1: {
            // remove start, version bits
            binData = binData.substr(16, binData.length()-16);

            // get object count
            int objectCount = binaryToDecimal(binData.substr(0, 8));
            logger.info("Object count is "+std::to_string(objectCount));

            int startPoint = 8;
            // fun fun fun
            for (int i=0; i<objectCount; i++) {
                logger.info("Deserializing object #"+std::to_string(i));

                int objectSize = binaryToDecimal(binData.substr(startPoint, 8))*8;
                logger.info("Object size: "+std::to_string(objectSize));
                
                std::string thisObject = binData.substr(startPoint + 8, objectSize);

                logger.info("Object binary: "+thisObject);

                startPoint += objectSize;

                coord pos, vel, accel;
                double size, mass;
                bodyType shape;

                int cursor = 0;
                int itemSize = binaryToDecimal(thisObject.substr(cursor, 8))*8;
                cursor += 8;
                
                pos = deserializeCoord(thisObject.substr(cursor, itemSize));
                shiftCursor(&thisObject, &cursor, &itemSize);

                vel = deserializeCoord(thisObject.substr(cursor, itemSize));
                shiftCursor(&thisObject, &cursor, &itemSize);

                accel = deserializeCoord(thisObject.substr(cursor, itemSize));
                shiftCursor(&thisObject, &cursor, &itemSize);


                size = deserializeDouble(thisObject.substr(cursor, itemSize));
                shiftCursor(&thisObject, &cursor, &itemSize);

                mass = deserializeDouble(thisObject.substr(cursor, itemSize));
                shiftCursor(&thisObject, &cursor, &itemSize);


                shape = deserializeBodyType(thisObject.substr(cursor, itemSize));


                objectHandler->Add(pos, vel, accel, size, mass, shape);

                // this could be wrong, haven't tested with multiple objecte yet so idk
                startPoint = cursor + 8;

            }


            break;
        }
    }
}

void BinaryReader::shiftCursor(std::string *thisObject, int *cursor, int *itemSize) {
    *cursor += *itemSize;
    *itemSize = binaryToDecimal(thisObject->substr(*cursor, 8)) * 8;
    *cursor += 8;
}

//  all deserialize...() functions take input _WITH_ LENGTH BYTE
// ATTACHED
//
// SORT THIS THE FUCK OUT IT'S DISORGANISED
coord BinaryReader::deserializeCoord(std::string binary) {
    logger.info("Deserializing a coord: "+binary);

    coord output;
    
    // remove length byte
    binary = binary.substr(8, binary.length()-8);

    for (int i=0; i<3; i++) {
        logger.info("Getting coord item #"+std::to_string(i+1));
        int nextLength = binaryToDecimal(binary.substr(0, 8))*8;
        logger.info("Item length is "+std::to_string(nextLength));
        std::string nextValBin = binary.substr(8, nextLength*8);
        logger.info("Item binary: "+nextValBin);

        int nextVal = deserializeDouble(nextValBin);
        switch(i) {
            case 0: {output.x = nextVal; break;}
            case 1: {output.y = nextVal; break;}
            case 2: {output.z = nextVal; break;}
        }

        binary = binary.substr(nextLength + 8, binary.length() - nextLength - 8);
    }

    return output;
}


double BinaryReader::deserializeDouble(std::string binary) {
    double output;

    // ditch the length byte
    binary = binary.substr(8, binary.length()-8);

    logger.info("Deserializing a double: "+binary);
    std::string sign = binary.substr(0, 8);

    // get the length of the first int
    std::string int1LengthBinary = binary.substr(8, 8);

    logger.info("Int 1 length (binary): " +int1LengthBinary);

    // length stored in BYTES
    int int1Length = binaryToDecimal(int1LengthBinary) * 8;
    

    // repeat
    std::string int2LengthBinary = binary.substr(int1Length + 16, 8);
    logger.info("Int 2 length (binary): " +int2LengthBinary);
    int int2Length = binaryToDecimal(int2LengthBinary) * 8;

    // and again
    std::string int3LengthBinary = binary.substr(int1Length + 24 + int2Length, 8);
    logger.info("Int 2 length (binary): " +int3LengthBinary);
    int int3Length = binaryToDecimal(int3LengthBinary) * 8;
    
    int int1, int2, int3;
    int1 = deserializeInt(binary.substr(8, int1Length));
    int2 = deserializeInt(binary.substr(int1Length+8, int2Length));
    int3 = deserializeInt(binary.substr(int1Length+8+int2Length, int3Length));

    double decimalPart = int2;
    for (int i=0; i < int3; i++) {
        decimalPart *= 0.1;
    }

    output = int1 + decimalPart;

    logger.info("double was "+std::to_string(output));

    return output;

}

int BinaryReader::deserializeInt(std::string binary) {

    int output;

    logger.info("Deserializing an int: "+binary);
    // get rid of size byte, we don't care
    binary = binary.substr(8, binary.length()-8);

    std::string sign = binary.substr(0, 8);
    std::string data = binary.substr(8, binary.length()-8);

    int unsignedData = binaryToDecimal(data);

    if (sign == "00000000") {
        // positive
        logger.info("Int was positive");
        output = unsignedData;
    } else if (sign == "00000001") { 
        // negative
        logger.info("Int was negative");
        output = 0 - unsignedData;
    } else {
        // errors are entirely possible
        logger.warning("Tried to deserialize int, signing was "+sign);
        output = 69;
    }

    logger.info("Int is "+std::to_string(output));
    return output;


}

bodyType BinaryReader::deserializeBodyType(std::string binary) {
    logger.info("Deserializing bodyType");

    bodyType output;

    switch(binaryToDecimal(binary)) {
        case 0: {
            output = cube;
            logger.info("cube");
            break;
        }
        case 1: {
            output = sphere;
            logger.info("sphere");
            break;
        }
    }

    return output;
}

void BinaryReader::inheritedDestroy() {

}
