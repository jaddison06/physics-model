#include "physics/Field.h"

Field::Field()
{
    logger->setSender("Field");
    addTag("field");

    auto temp = sphere;
    shape = &temp;

    logger->info("Field initialized");
}