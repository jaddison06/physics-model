#pragma once

#include "control/logging.h"
#include "3d/3DBody.h"
#include <vector>

class Field: public ThreeDBody {
    public:
        Field();

        // sometimes stuff adds extra parameters to this,
        // but apparently that doesn't break stuff so fingers crossed
        // this can stay
        virtual double calcFieldStrength(coord *point, std::vector<double> *extraData)=0;
};