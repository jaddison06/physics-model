#pragma once

#include "3d/3DBody.h"
#include "physics/GravField.h"
#include "physics/constants.h"

// an Object represents a mass in space. it is
// responsible for ticking all its components, and
// modifying their attributes eg location with its own
class Object: public ThreeDBody
{
    public:
        Object(coord *location, double *size, double *mass, bodyType *shape, std::string *ID);
        ~Object();

        // obviously not actual coords but it's an x, y, z struct
        coord *velocity, *acceleration;

        double volume, mass, density;
        
        void Tick(double tickTime);
    
    private:
        GravField *gravField;

};