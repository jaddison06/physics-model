#pragma once

#include "logging.h"
#include "Field.h"
#include <vector>

// will add more later
enum fieldType {gravitational};

class FieldHandler {
    public:
        Field *addField(fieldType thisType, coord *coords);
        void removeField(Field* field);
    
    private:
        std::vector<Field> fields;
};