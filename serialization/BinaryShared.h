#pragma once

#include <string>
#include <fstream>
#include <cstring>
#include "control/GenericBaseClass.h"

// version of the file only, not the whole piece of software
#define VERSION 1

//#include <iostream>

std::string decimalToBinary(int decimal);
int binaryToDecimal(std::string binary);

std::string makeByte(std::string input);
std::string setLength(std::string input, int targetLength);