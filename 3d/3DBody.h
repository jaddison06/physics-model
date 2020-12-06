#pragma once

#include "control/GenericBaseClass.h"
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

// it's slightly sexier this way imo
struct coord
{
    double x, y, z;
};

// add more later
enum bodyType
{
    sphere,
    cube
};


// random stuff from 3DBody.cpp that i might want to reuse at some point
double getDist(coord *a, coord *b);
std::string coordToString(coord *coords);
void addCoords(coord *a, coord *b);


// class names can't start with a number apparently
//
// it's chill cause we don't really use this, it's
// basically just gonna get extended by other stuff
class ThreeDBody: public GenericBaseClass
{
    public:
        ThreeDBody();
        ~ThreeDBody();

        bool containsPoint(coord *coords);

        void addTag(std::string tag);
        void removeTag(std::string tag);
        bool hasTag(std::string tag);

        coord *location;
        bodyType *shape;
        double *size;

    protected:
        std::vector<std::string> *tags;


};