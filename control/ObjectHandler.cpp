#include "control/ObjectHandler.h"

// ObjectHandler is responsible for all the Objects in space. Its 
// Tick function -is- will be spicy and handles all the logic for interactions
// _between_ objects. At some point it needs to be able to deal with
// model data as well

ObjectHandler::ObjectHandler() {
    logger.setSender("ObjectHandler");
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