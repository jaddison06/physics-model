#include "serialization/BinaryShared.h"

Logger logger("BinaryShared");

std::string decimalToBinary(int decimal) {
    logger.info("Converting decimal "+std::to_string(decimal)+" to binary");

    int bits[]{};
    int i;

    for (i = 0; decimal > 0; i++)
    {
        bits[i] = decimal % 2;
        decimal = decimal / 2;
    }

    std::string output;
    for (i = i - 1; i >= 0; i--)
    {
        output += std::to_string(bits[i]);
    }

    logger.info("Result was "+output);

    return output;
}

int binaryToDecimal(std::string binary) {
    logger.info("Converting binary "+binary+" to decimal");

    //std::cout << binary << std::endl;
    int num = stoi(binary);
    int cNum = 0, temp, base = 1;

    while (num > 0)
    {
        temp = num % 10;
        num = num / 10;
        cNum = cNum + base * temp;
        base = base * 2;
    }

    logger.info("Result was "+std::to_string(cNum));

    return cNum;
}

// set the length of a string to a multiple of 8
// IF IT'S ALREADY A MULTIPLE IT DOES TO THE NEXT 8 WTF?
// FIX THIS IT'S THE ONLY THING STOPPING THE PROGRAM FROM RUNNING
//
// OR IS IT?
// YES
std::string makeByte(std::string input)
{
    logger.info("Setting " + input + " to a byte");
    int targetLength;
    if (input.length() % 8 == 0) {
        targetLength = input.length();
    } else {
        targetLength = input.length() + 8 - (input.length() % 8);
    }
    return setLength(input, targetLength);
}

// set a binary to a specific length
std::string setLength(std::string input, int targetLength)
{
    logger.info("Setting " + input + " to length " + std::to_string(targetLength));
    std::string prependor;
    for (int i = input.length(); i < targetLength; i++)
    {
        prependor += "0";
    }

    std::string output = prependor + input;

    logger.info("Result was "+output);
    return output;
}


// check if a double is a whole number or not
bool isInt(double *input) {
    return (*input == floor(*input));
}