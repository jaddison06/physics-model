#include "control/ObjectHandler.h"

// ObjectHandler is responsible for all the Objects in space. Its 
// Tick function -is- will be spicy and handles all the logic for interactions
// _between_ objects. At some point it needs to be able to deal with
// model data as well

ObjectHandler::ObjectHandler() {
    logger.setSender("ObjectHandler");

    logger.info("ObjectHandler initialized");
}

void ObjectHandler::Tick(double tickTime) {
    logger.info("ticking");
    for (int i=0; i<objects.size(); i++) {
        objects[i].Tick(tickTime);
    }
}

void ObjectHandler::inheritedDestroy() {
    for (int i=0; i<objects.size(); i++) {
        objects[i].Destroy();
    }
}

void ObjectHandler::Add(coord pos, coord vel, coord accel, double size, double mass, bodyType shape) {
    std::string ID = std::to_string(objects.size());
    
    Object object(pos, size, mass, shape, ID);

    object.velocity = vel;
    object.acceleration = accel;

    objects.push_back(object);
}