#include "control/Model.h"
#include "control/logging.h"

// entrypoint for the model

// exitFunc is called repeatedly to determine
// whether or not the model should continue to the next tick
//
// it's given a pointer to the Model's logger and once model data happens
// it'll also get that
bool exitFunc(Logger *logger) {
    logger->info("exitFunc called");
    return true;
}

int main() {
    Model model;
    model.Start(&exitFunc);

    return 0;
}