#pragma once

#include "control/logging.h"
#include "physics/Field.h"
#include <vector>

// will add more later
enum fieldType {gravitational};

class FieldHandler {
    public:
        Field *addField(fieldType thisType, coord *coords);
        void removeField(Field* field);

        std::vector<Field*> fieldsContainingPoint(coord *coords);
    
    private:
        std::vector<Field> fields;

        Logger logger {"FieldHandler"};
};