#pragma once

#include "3d/3DBody.h"
#include "physics/GravField.h"
#include "physics/constants.h"

// an Object represents a mass in space. it is
// responsible for ticking all its components, and
// modifying their attributes eg location with its own
class Object: public ThreeDBody {
    public:
        Object(coord pos, double bigness, double massGrams, bodyType form);

        // obviously not actual coords but it's an x, y, z struct
        coord velocity, acceleration;

        void Tick(double tickTime);
    
    private:
        double volume, mass, density;
        GravField gravField;

        void inheritedDestroy();

};