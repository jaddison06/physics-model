#include "physics/Object.h"

Object::Object(coord *location, double *size, double *mass, bodyType *shape, std::string *ID)
{
    gravField = new GravField();

    logger->setSender("Object");
    logger->setID(*ID);

    std::string tag = "object";
    addTag(tag);

    gravField->logger->setID("- Object "+*ID);

    this->location = *location;
    this->size = *size;
    this->mass = *mass;
    this->shape = *shape;

    switch(*shape)
    {
        case cube:
        {
            logger->info("Object is a cube");
            volume = pow(*size, 3);
            break;
        }
        case sphere:
        {
            logger->info("Object is a sphere");
            volume = (4/3)*PI*pow(*size, 3);
            break;
        }
    }

    density = *mass/volume;

    gravField->init(mass);

    logger->info("Object initialized");

    logger->info("Location: "+coordToString(location));
    logger->info("Size: "+std::to_string(*size));
    logger->info("Mass: "+std::to_string(*mass));
    logger->info("Volume: "+std::to_string(volume));
    logger->info("Density: "+std::to_string(density));
}

Object::~Object()
{
    delete gravField;
}

// Move the object a certain interval forwards in time
// tickTime currently does nothing
void Object::Tick(double tickTime)
{
    printf("o tick\n");
    logger->info("test");
    printf("t\n");
    logger->info("Current location: "+coordToString(&location));
    printf("l\n");
    logger->info("Current velocity: "+coordToString(&velocity));
    logger->info("Current acceleration: "+coordToString(&acceleration));

    printf("hh\n");

    logger->info("ticking");

    printf("logga\n");

    //TODO: _average_ velocity over the time interval
    addCoords(&location, &velocity);
    addCoords(&velocity, &acceleration);

    printf("add done\n");

    logger->info("New location: " + coordToString(&location));
    logger->info("New velocity: " + coordToString(&velocity));
    logger->info("New acceleration: " + coordToString(&acceleration));

    gravField->location = location;
}