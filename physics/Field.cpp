#include "physics/Field.h"

Field::Field() {
    logger.setSender("Field");
    addTag("field");
    shape = sphere;
}