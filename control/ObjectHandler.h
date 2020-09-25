#pragma once

#include "physics/Object.h"
#include <vector>

class ObjectHandler {
    public:

        // i hate that this has to be public
        //
        // later, when we have some kind of model data,
        // we can accept that instead and make this private
        std::vector<Object> objects;

        void Tick(double tickTime);
    
    private:
        Logger logger{"ObjectHandler"};
};