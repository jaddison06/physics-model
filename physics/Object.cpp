#include "physics/Object.h"

Object::Object(coord pos, double bigness, double massGrams, bodyType form, std::string ID) {
    logger.setSender("Object");
    logger.setID(ID);
    addTag("object");

    logger.info("Object initialized");

    location = pos;
    size = bigness;
    mass = massGrams;
    shape = form;

    switch(shape) {
        case cube: {
            logger.info("Object is a cube");
            volume = pow(size, 3);
            break;
        }
        case sphere: {
            logger.info("Object is a sphere");
            volume = (4/3)*PI*pow(size, 3);
            break;
        }
    }

    density = mass/volume;

    gravField.init(mass);
}

// Move the object a certain interval forwards in time
// tickTime currently does nothing
void Object::Tick(double tickTime) {
    logger.info("Current location: "+coordToString(&location));
    logger.info("Current velocity: "+coordToString(&velocity));
    logger.info("Current acceleration: "+coordToString(&acceleration));

    logger.info("ticking");

    addCoords(&location, &velocity);
    addCoords(&velocity, &acceleration);

    logger.info("New location: " + coordToString(&location));
    logger.info("New velocity: " + coordToString(&velocity));
    logger.info("New acceleration: " + coordToString(&acceleration));

    gravField.location = location;
}

void Object::inheritedDestroy() {
    gravField.Destroy();
}