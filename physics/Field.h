#pragma once

#include "control/logging.h"
#include "3d/3DBody.h"

class Field: public ThreeDBody {
    public:
        Field();

        // we don't define this, the inheriter does as it's different for different
        // types of field
        virtual float calcFieldStrength(coord *point);
};