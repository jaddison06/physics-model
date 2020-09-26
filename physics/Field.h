#pragma once

#include "3d/3DBody.h"
#include <vector>

class Field: public ThreeDBody {
    public:
        Field();

        virtual double calcFieldStrength(coord *point, std::vector<double> *extraData)=0;
};