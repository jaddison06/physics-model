#pragma once

#include "control/logging.h"
#include "3d/3DBody.h"
#include "physics/GravField.h"

class Object: public ThreeDBody {
    public:
        Object(coord pos, float bigness, float massGrams, bodyType form);
    
    private:
        float volume, mass, density;
        Logger logger {"Object"};
        GravField gravField;

};