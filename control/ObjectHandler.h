#pragma once

#include "physics/Object.h"
#include "control/GenericBaseClass.h"
#include <vector>

class ObjectHandler: public GenericBaseClass
{
    public:
        ObjectHandler();
        ~ObjectHandler();

        // i hate that this has to be public
        //
        // later, when we have some kind of model data,
        // we can accept that instead and make this private
        std::vector<Object> objects;

        void Tick(double tickTime);
        void Add(coord *pos, coord *vel, coord *accel, double *size, double *mass, bodyType *shape);

        
};