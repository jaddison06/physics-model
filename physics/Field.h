#pragma once

#include "3d/3DBody.h"
#include <vector>

class Field: public ThreeDBody {
    public:
        Field();

        // returns the force on that point
        virtual double calcFieldStrength(coord *point, std::vector<double> *extraData)=0;
};
