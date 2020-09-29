#include "serialization/BinaryCreator.h"

// TODO: clean this the fuck up
// just convert between types
// you've got strings which are strings
// strings which are binary
// ints
// chars
//
// wack af
//
// also a bunch of functions don't actually get used
//
// improve logging
//
// do BinaryReader
//
// comment cause this isn't readable at all
//
// update all the serialize whatever functions
// bc they're pretty wank
//
// also serializeDouble() is very stupid
// don't just stream variables out of memory and into
// a file
//
// redo decimalToBinary & vice versa cause they're shit
// and also might not work for negatives
//
// get rid of unused includes
// 
// thanks x



BinaryCreator::BinaryCreator() {
    logger.setSender("BinaryCreator");

    logger.info("BinaryCreator initialized");
}


void BinaryCreator::CreateBinary(ObjectHandler *objectHandler, std::string fname) {
    logger.info("Creating a binary");

    std::string binData = createBinData(objectHandler);
    std::string chars = binaryToString(binData);
    writeToFile(chars, fname);
}



std::string BinaryCreator::createBinData(ObjectHandler *objectHandler) {
    logger.info("Creating binary data");

    std::string output = "";
    int objectCount = (objectHandler -> objects).size();

    // start ID bits
    output += "01000101";

    // version bits
    output += makeByte(decimalToBinary(VERSION));

    // object count bit
    output += makeByte(decimalToBinary(objectCount));

    // objects
    logger.info("Object count is "+std::to_string(objectCount));
    for (int i=0; i<objectCount; i++) {
        logger.info("Serializing object #"+std::to_string(i));
        output += serializeObject(&(objectHandler->objects[i]));
    }

    // end ID bits
    output += "0000000110100100";
    
    return output;

}


std::string BinaryCreator::serializeObject(Object *object) {
    logger.info("serializing object");

    std::string output = "";

    output += serializeCoord(&(object -> location));
    output += serializeCoord(&(object -> velocity));
    output += serializeCoord(&(object -> acceleration));
    output += serializeDouble(&(object -> size));
    output += serializeDouble(&(object -> mass));
    output += serializeBodyType(&(object -> shape));

    addLengthByte(&output);

    logger.info("object binary: "+output);

    return output;

}

// assumes length is already a multiple of 8
void BinaryCreator::addLengthByte(std::string *binary) {
    logger.info("Adding a length byte to binary "+*binary);
    *binary = makeByte(decimalToBinary((binary->length() / 8))) + *binary;
    logger.info("New binary: "+*binary);
    return;
}

std::string BinaryCreator::serializeCoord(coord *coords) {
    logger.info("Serializing a coord");

    std::string x = serializeDouble(&(coords->x));
    std::string y = serializeDouble(&(coords->y));
    std::string z = serializeDouble(&(coords->z));

    std::string output = x+y+z;

    addLengthByte(&output);

    logger.info("Coord binary: "+output);

    return output;
}

// there is a way to do this but i don't know it
//
// floating point algorithm?? TODO: research floating points
std::string BinaryCreator::serializeDouble(double *someDouble) {
    logger.info("Serializing a double");
    std::string output;

    // ok first sign it
    //
    // everything has to be bytes unfortunately
    if (*someDouble >= 0)
    {
        output += "00000000";
    }
    else
    {
        output += "00000001";
    }

    // ok now convert it into the int bit and the decimal bit
    int intBit = abs((int)floor(*someDouble));
    double decimalBit = abs(*someDouble-intBit);


    // now we can store the int bytes
    output += serializeInt(&intBit);


    // now figure out how many dp it is
    int dpCounter = 0;
    while (!isInt(&decimalBit)) {
        dpCounter ++;
        decimalBit *= 10;
    }

    int decimalAsInt = (int)decimalBit;
    output += serializeInt(&decimalAsInt);

    output += serializeInt(&dpCounter);

    addLengthByte(&output);

    logger.info("Double binary: "+output);

    return output;

}

std::string BinaryCreator::serializeInt(int *someInt) {
    logger.info("Serializing int");
    std::string output;

    // sign
    logger.info("Signing int");
    if (*someInt >= 0) {
        logger.info("Positive");
        output += "00000000";
    } else {
        logger.info("Negative");
        output += "00000001";
    }


    int absInt = abs(*someInt);

    output += makeByte(decimalToBinary(absInt));

    addLengthByte(&output);

    logger.info("Int binary: "+output);

    return output;
}

std::string BinaryCreator::serializeBodyType(bodyType *bType) {
    std::string output = "";
    int id;

    switch(*bType) {
        case cube: {
            id = 0;
            break;
        }
        case sphere: {
            id = 1;
            break;
        }
    }

    output = makeByte(decimalToBinary(id));

    addLengthByte(&output);

    return output;
}


// convert binary string to writable string of chars
std::string BinaryCreator::binaryToString(std::string binary) {
    logger.info("Converting binary "+binary+" to a string");

    // first, convert the binary into bytes
    std::vector<std::string> bytes;

    logger.info("Separating bytes");
    for (int i = 0; i < (binary.length()) / 8; i++) {
        std::string current = binary.substr(i*8, 8);
        logger.info("Byte "+std::to_string(i)+": "+current);

        //std::cout << current << std::endl;

        bytes.push_back(current);
    }

    // now convert those to a string of actual chars
    std::string chars;

    logger.info("Converting to chars");
    
    for (int i=0; i<bytes.size(); i++) {
        logger.info("Converting byte "+std::to_string(i));
        unsigned char thisChar = binaryToDecimal(bytes[i]);

        //logger.info("Char is "+thisChar);
        chars += thisChar;
    }

    return chars;

}

std::string BinaryCreator::charToString(unsigned char chars[]) {
    // again, there's an easier way but screw that
    std::string output;
    for (int i=0; i<(sizeof(chars)/sizeof(unsigned char)); i++) {
        output += i;
    }

    return output;
}

void BinaryCreator::writeToFile(std::string input, std::string fname) {
    logger.info("Writing string "+input+" to file "+fname);

    std::ofstream fh("./data/models/"+fname, std::ios::binary);

    // convert string to char array
    //
    // there's an easier way to do this but i'm on my 7th
    // pepsi of the night and am therefore doing the absolute
    // bare minimum to get this serialization done
    unsigned char chars[input.length()];
    for (int i=0; i<input.length(); i++) {
        chars[i] = input[i];
    }

    fh.write((char*)&chars, sizeof(chars));

    fh.close();


}

void BinaryCreator::inheritedDestroy() {

}