#include "control/ObjectHandler.h"

// ObjectHandler is responsible for all the Objects in space. Its 
// Tick function -is- will be spicy and handles all the logic for interactions
// _between_ objects. At some point it needs to be able to deal with
// model data as well

ObjectHandler::ObjectHandler()
{
    objects = *(new std::vector<Object>);

    logger.setSender("ObjectHandler");

    logger.info("ObjectHandler initialized");
}

ObjectHandler::~ObjectHandler()
{
    //delete objects;
}

void ObjectHandler::Tick(double tickTime)
{
    logger.info("ticking");
    for (int i=0; i<objects.size(); i++)
    {
        objects[i].Tick(tickTime);
    }
}

void ObjectHandler::Add(coord *pos, coord *vel, coord *accel, double *size, double *mass, bodyType *shape)
{
    auto temp = std::to_string(objects.size());
    std::string *ID = &temp;
    
    Object object(pos, size, mass, shape, ID);

    object.velocity = *vel;
    object.acceleration = *accel;

    objects.push_back(object);
}