#pragma once

#include "control/logging.h"
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

// it's slightly sexier this way imo
struct coord {
    double x, y, z;
};

// add more later
enum bodyType {sphere, cube};


// random stuff from 3DBody.cpp that i might want to reuse at some point
double getDist(coord *a, coord *b);
std::string coordToString(coord *coords);


// class names can't start with a number apparently
//
// it's chill cause we don't really use this, it's
// basically just gonna get extended by other stuff
class ThreeDBody {
    public:

        bool containsPoint(coord *coords);

        void addTag(std::string tag);
        void removeTag(std::string tag);
        bool hasTag(std::string tag);

        coord location;
        bodyType shape;
        double size;

    protected:
        std::vector<std::string> tags;

        // bc this class only gets inherited, it's the responsibility of
        // whoever owns this at runtime to actually init the logger
        //
        // make sure you do though cause some of the public methods use it :/
        Logger logger;

};