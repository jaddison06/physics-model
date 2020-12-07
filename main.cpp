#include "control/Model.h"
#include "control/logging.h"
#include <iostream>

// entrypoint for the model

// exitFunc is called repeatedly to determine
// whether or not the model should continue to the next tick
//
// it's given a pointer to the Model's logger and once model data happens
// it'll also get that

// this exitFunc for testing only
int count = 0;
bool exitFunc(Logger *logger) {
    logger->info("exitFunc called");
    count++;
    return !(count<5);
}

int main() {

    // we have to call this _before_
    // instantiating the Model as it has its own Logger object
    // that won't work without it
    initLogging();
    Model *model = new Model;
    model->Start(&exitFunc);

    printf("done\n");

    delete model;

    printf("hhhh\n");

    return 0;
}