#pragma once

#include "logging.h"
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

// it's slightly sexier this way imo
struct coord {
    float x, y, z;
};

// add more later
enum bodyType {sphere, cube};

// class names can't start with a number apparently
//
// it's chill cause we don't really use this, it's
// basically just gonna get extended by other stuff
class ThreeDBody {
    public:
        ThreeDBody();

        bool containsPoint(coord *coords);

        std::string *addTag(std::string *tag);
        void removeTag(std::string *tag);
        bool hasTag(std::string *tag);

        coord location;
        bodyType shape;
        float size;

    private:
        std::vector<std::string> tags;

        // bc this class only gets inherited, it's the responsibility of
        // whoever owns this at runtime to actually init the logger
        //
        // make sure you do though cause some of the public methods use it :/
        Logger logger;

};