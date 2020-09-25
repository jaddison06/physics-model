#pragma once

#include "logging.h"
#include "3DBody.h"

class Field: public ThreeDBody {
    public:
        Field();

        // we don't define this, the inheriter does as it's different for different
        // types of field
        float calcFieldStrength(coord *point);
};