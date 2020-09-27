#include "serialization/BinaryShared.h"

std::string decimalToBinary(int decimal)
{
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

    return output;
}

int binaryToDecimal(std::string binary) {
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

    return cNum;
}