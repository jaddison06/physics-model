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

            // startPoint is the start of the object
            int startPoint = 8;

            // fun fun fun
            for (int i=0; i<objectCount; i++) {
                logger.info("Deserializing object #"+std::to_string(i));

                int objectSize = getSize(&binData, startPoint);
                logger.info("Object size: "+std::to_string(objectSize));
                
                // get the binary data for just this object
                // starts after size byte
                std::string thisObject = binData.substr(startPoint + 8, objectSize);

                logger.info("Object binary: "+thisObject);

                startPoint += objectSize;

                coord pos, vel, accel;
                double size, mass;
                bodyType shape;

                // cursor tells us where to read from in the object
                int cursor = 0;
                int itemSize = getSize(&thisObject, cursor);
                
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

// get item size in BITS
int BinaryReader::getSize(std::string *binary, int startPoint) {
    logger.info("Getting size from item "+*binary+",\nstarting at bit #"+std::to_string(startPoint));

    std::string binSize = binary->substr(startPoint, 8);
    logger.info("Size bits: "+binSize);

    int size = binaryToDecimal(binSize);
    logger.info("Size in bytes: "+std::to_string(size));

    size *= 8;
    logger.info("Size in bits: "+std::to_string(size));
    
    size += 8;
    logger.info("Size in bits (inc size byte): "+std::to_string(size));

    return size;
}


void BinaryReader::shiftCursor(std::string *thisObject, int *cursor, int *itemSize) {
    *cursor += *itemSize;
    *itemSize = getSize(thisObject, *cursor);

}
//  all deserialize...() functions take input _WITH_ LENGTH BYTE
// ATTACHED
coord BinaryReader::deserializeCoord(std::string binary) {
    logger.info("Deserializing a coord: "+binary);

    coord output;
    
    // remove length byte
    binary = binary.substr(8, binary.length()-8);

    for (int i=0; i<3; i++) {
        logger.info("Getting coord item #"+std::to_string(i+1));
        int nextLength = getSize(&binary);
        logger.info("Item length is "+std::to_string(nextLength));
        std::string nextValBin = binary.substr(0, nextLength);
        logger.info("Item binary: "+nextValBin);

        int nextVal = deserializeDouble(nextValBin);
        switch(i) {
            case 0: {output.x = nextVal; break;}
            case 1: {output.y = nextVal; break;}
            case 2: {output.z = nextVal; break;}
        }

        binary = binary.substr(nextLength, binary.length() - nextLength);
    }

    return output;
}


double BinaryReader::deserializeDouble(std::string binary) {
    double output;

    logger.info("Deserializing a double: " + binary);

    // ditch the length byte
    binary = binary.substr(8, binary.length()-8);

    std::string sign = binary.substr(0, 8);

    int int1, int2, int3;

    // we read the string starting at the cursor point
    // cursor starts after the double's sign bit
    int cursor = 8;

    // get the length of the first int
    // includes sign bit
    int int1Length = getSize(&binary, cursor);

    int1 = deserializeInt(binary.substr(cursor, int1Length));

    // increment cursor
    cursor += int1Length;

    // repeat
    int int2Length = getSize(&binary, cursor);
    int2 = deserializeInt(binary.substr(cursor, int2Length));
    cursor += int2Length;


    // and again
    int int3Length = getSize(&binary, cursor);
    int3 = deserializeInt(binary.substr(cursor, int3Length));

    double decimalPart = int2;
    for (int i=0; i < int3; i++) {
        decimalPart *= 0.1;
    }

    output = int1 + decimalPart;

    output = signDouble(&output, &sign);

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

    output = signInt(&unsignedData, &sign);

    logger.info("Int is "+std::to_string(output));
    return output;


}

int BinaryReader::signInt(int *unsignedData, std::string *sign) {
    int output;

    if (*sign == "00000000") {
        // positive
        logger.info("Int was positive");
        output = *unsignedData;
    } else if (*sign == "00000001") {
        // negative
        logger.info("Int was negative");
        output = 0 - *unsignedData;
    } else {
        // errors are entirely possible
        logger.warning("Tried to deserialize int, signing was " + *sign);
        output = 69;
    }

    return output;
}

double BinaryReader::signDouble(double *unsignedData, std::string *sign) {
    logger.info("Signing double");
    double output;

    if (*sign == "00000000") {
        // positive
        logger.info("Double was positive");
        output = *unsignedData;
    } else if (*sign == "00000001") {
        // negative
        logger.info("Double was negative");
        output = 0 - *unsignedData;
    } else {
        // errors are entirely possible
        logger.warning("Tried to deserialize double, signing was " + *sign);
        output = 69;
    }

    return output;
}

bodyType BinaryReader::deserializeBodyType(std::string binary) {
    logger.info("Deserializing bodyType");

    // remove length byte
    binary = binary.substr(8, binary.length() - 8);

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
