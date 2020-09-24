#include "3DBody.h"

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


// getter n setter
coord ThreeDBody::getLocation() {
    return location;
}

void ThreeDBody::setLocation(coord *newLoc) {
    location = *newLoc;
}