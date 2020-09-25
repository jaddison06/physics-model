#pragma once

#include "control/logging.h"
#include "3d/3DBody.h"
#include "physics/GravField.h"

class Object: public ThreeDBody {
    public:
        Object(coord pos, double bigness, double massGrams, bodyType form);
    
    private:
        double volume, mass, density;
        Logger logger {"Object"};
        GravField gravField;

};