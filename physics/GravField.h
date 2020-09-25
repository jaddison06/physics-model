#pragma once

#include "physics/Field.h"
#include "physics/constants.h"
#include <math.h>

class GravField: public Field {
    public:
        GravField();
        void init(double ownerMass);
        
        
        double calcFieldStrength(coord *point, std::vector<double> *extraData);

    private:
        double bodyMass;

        
};