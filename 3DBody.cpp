#include "3DBody.h"

// shape is an enum
//
// location is a struct coords
//
// i called it bigness cause i've already used the name
// size, this relates to:
//  - side length of a cube
//  - radius of a sphere
ThreeDBody::ThreeDBody(bodyType thisShape, coord coords, float bigness) {
    shape = thisShape;
    location = coords;
    size = bigness;
}


// tags stuff
void ThreeDBody::addTag(std::string *tag) {
    if (hasTag(tag)) {
        logger.warning("tried to add tag "+*tag+" but we already have it");
    } else {
        logger.info("adding tag "+*tag);
        tags.push_back(*tag);
    }
}

void ThreeDBody::removeTag(std::string *tag) {
    if (!hasTag(tag)) {
        logger.warning("tried to remove tag "+*tag+" but we don't have it");
    } else {
        logger.info("removing tag "+*tag);
        tags.erase(std::remove(tags.begin(), tags.end(), *tag), tags.end());
    }
}

bool ThreeDBody::hasTag(std::string *tag) {
    bool tagFound = false;
    for (int i=0; i<tags.size(); i++) {
        if (tags[i] == *tag) {
            tagFound = true;
            break;
        }
    }
    return tagFound;
}


// check if a given x, y, z is inside the body
bool ThreeDBody::containsPoint(coord *coords) {
    switch (shape) {
        case cube:
            float halfSideLength = size/2;
            coord minimums { location.x - halfSideLength, location.y - halfSideLength, location.z - halfSideLength };
            coord maximums {location.x + halfSideLength, location.y + halfSideLength, location.z + halfSideLength};
            return ( (coords->x > minimums.x && coords->y > minimums.y && coords->z > minimums.z) && (coords->x < maximums.x && coords->y < maximums.y && coords->z < maximums.z) );
    }
}