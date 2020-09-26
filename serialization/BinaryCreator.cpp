#include "serialization/BinaryCreator.h"

BinaryCreator::BinaryCreator() {
    logger.setSender("BinaryCreator");

    logger.info("BinaryCreator initialized");
}

// set the length of a string to a multiple of 8
std::string BinaryCreator::makeByte(std::string input) {
    logger.info("Setting "+input+" to a byte");
    return setLength(input, input.length() % 8);
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








// convert binary string to writable string of chars
std::string BinaryCreator::binaryToString(std::string binary) {
    logger.info("Converting binary "+binary+" to a char");

    // first, convert the binary into bytes
    std::string bytes[] {};

    for (int i = 0; i < (binary.length()) / 8; i++) {
        bytes->append(binary.substr(i, 8));
    }

    // now convert those to a string of actual chars
    std::string chars;
    
    for (int i=0; i<bytes->size(); i++) {
        chars += (char)binaryToDecimal(bytes[i]);
    }

    return chars;

}

void BinaryCreator::writeToFile(std::string input, std::string fname) {
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