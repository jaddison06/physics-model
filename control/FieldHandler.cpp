#include "FieldHandler.h"

Field* FieldHandler::addField(fieldType thisType, coord *coords) {
    logger.info("adding field");
    Field thisField;
    thisField.location = *coords;
    fields.push_back(thisField);
    return &thisField;
}

void FieldHandler::removeField(Field *field) {
    logger.info("removing field");
    fields.erase(std::remove(fields.begin(), fields.end(), *field), fields.end());
}

std::vector<Field*> FieldHandler::fieldsContainingPoint(coord *coords) {
    logger.info("checking all fields for point ");
    std::vector<Field*> output;
    for (int i=0; i<fields.size(); i++) {
        if (fields[i].containsPoint(coords)) {
            output.push_back(&fields[i]);
        }
    }
    return output;
}

