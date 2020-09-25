#include "3DBody.h"

// shape is an enum
//
// location is a struct coords
//
// size relates to:
//  - side length of a cube
//  - radius of a sphere


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
    logger.info("checking for tag "+*tag);
    bool tagFound = false;
    for (int i=0; i<tags.size(); i++) {
        if (tags[i] == *tag) {
            tagFound = true;
            break;
        }
    }
    if (tagFound) {
        logger.info("the tag was found");
    } else {
        logger.info("the tag was not found");
    }
    return tagFound;
}

// sexy coord
std::string coordToString(coord *coords) {
    return std::to_string(coords->x) + ", " + std::to_string(coords->y) + ", " + std::to_string(coords->z);
}


// spicy pythagoras to find distance between two 3d points
// this may or may not work with negative coords
float getDist(coord *a, coord *b) {
    // first find the distance on the xz plane
    //
    // i'm pretty sure there's no need to root this as it just
    // gets squared again later but i'm playing it safe
    float baseDist = sqrt(pow((b->x) - (a->x), 2) + pow((b->z) - (a->z), 2));

    // now do that again with the y axis
    return sqrt(pow(baseDist, 2) + pow((b->y) - (a->y), 2));
}

// check if a given x, y, z is inside the body
bool ThreeDBody::containsPoint(coord *coords) {
    switch (shape) {
        case cube:
        {
            float halfSideLength = size/2;
            coord minimums { location.x - halfSideLength, location.y - halfSideLength, location.z - halfSideLength };
            coord maximums {location.x + halfSideLength, location.y + halfSideLength, location.z + halfSideLength};
            return ( (coords->x > minimums.x && coords->y > minimums.y && coords->z > minimums.z) && (coords->x < maximums.x && coords->y < maximums.y && coords->z < maximums.z) );
        }
        
        case sphere:
        {
            // get the distance between the centre of the sphere & our point
            float dist = getDist(&location, coords);

            // now compare that to the radius of our sphere
            return (dist <= size);
        }
    }

    // this doesn't get used but it satisfies the compiler
    return false;

}