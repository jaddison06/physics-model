#include "physics/Object.h"

Object::Object(coord pos, double bigness, double massGrams, bodyType form) {
    addTag("object");

    location = pos;
    size = bigness;
    mass = massGrams;
    shape = form;

    switch(shape) {
        case cube: {
            volume = pow(size, 3);
        }
        case sphere: {
            volume = (4/3)*PI*pow(size, 3);
        }
    }

    density = mass/volume;

    gravField.init(mass);
}