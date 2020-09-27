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

// set the length of a string to a multiple of 8
std::string BinaryCreator::makeByte(std::string input) {
    logger.info("Setting "+input+" to a byte");
    return setLength(input, input.length() + 8 - (input.length() % 8));
}

// set a binary to a specific length
std::string BinaryCreator::setLength(std::string input, int targetLength) {
    logger.info("Setting "+input+" to length "+std::to_string(targetLength));
    std::string prependor;
    for (int i=input.length(); i<targetLength; i++){
        prependor += "0";
    }
    return prependor + input;
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
    for (int i=0; i<objectCount; i++) {
        output += serializeObject(&(objectHandler->objects[i]));
    }

    // end ID bits
    output += "0000000110100100";
    
    return output;

}


std::string BinaryCreator::serializeObject(Object *object) {
    std::string output = "";

    output += serializeCoord(&(object -> location));
    output += serializeCoord(&(object -> velocity));
    output += serializeCoord(&(object -> acceleration));
    output += serializeDouble(&(object -> size));
    output += serializeDouble(&(object -> mass));
    output += serializeBodyType(&(object -> shape));

    return output;

}

std::string BinaryCreator::serializeCoord(coord *coords) {

    std::string x = serializeDouble(&(coords->x));
    std::string y = serializeDouble(&(coords->y));
    std::string z = serializeDouble(&(coords->z));

    return x+y+z;
}

std::string BinaryCreator::serializeDouble(double *someDouble) {
    std::string output;

    char chars[sizeof(double)];

    memcpy(chars, someDouble, sizeof(*someDouble));

    output = charToString(chars);

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
    return output;
}


// convert binary string to writable string of chars
std::string BinaryCreator::binaryToString(std::string binary) {
    logger.info("Converting binary "+binary+" to a string");

    // first, convert the binary into bytes
    std::vector<std::string> bytes;

    for (int i = 0; i < (binary.length()) / 8; i++) {
        std::string current = binary.substr(i, 8);
        std::cout << current << std::endl;

        bytes.push_back(current);
    }

    // now convert those to a string of actual chars
    std::string chars;
    
    for (int i=0; i<bytes.size(); i++) {
        chars += (char)binaryToDecimal(bytes[i]);
    }

    return chars;

}

std::string BinaryCreator::charToString(char chars[]) {
    // again, there's an easier way but screw that
    std::string output;
    for (int i=0; i<(sizeof(chars)/sizeof(char)); i++) {
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
    char chars[input.length()];
    for (int i=0; i<input.length(); i++) {
        chars[i] = input[i];
    }

    fh.write(chars, sizeof(chars));

    fh.close();


}

void BinaryCreator::inheritedDestroy() {

}