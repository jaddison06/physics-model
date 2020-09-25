#pragma once

#include "physics/Field.h"
#include "physics/constants.h"
#include <math.h>

class GravField: public Field {
    public:
        GravField();
        void init(double ownerMass);
        float calcFieldStrength(coord *point, double m2);

    private:
        double bodyMass;

        
};