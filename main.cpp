#include "control/Model.h"
#include "control/logging.h"
#include <iostream>

// entrypoint for the model

// exitFunc is called repeatedly to determine
// whether or not the model should continue to the next tick
//
// it's given a pointer to the Model's logger and once model data happens
// it'll also get that

//TESTING ONLY
int count = 0;

bool exitFunc(Logger *logger) {
    logger->info("exitFunc called");
    count++;
    return (count<5);
}

int main() {
    
    // for posterity, this doesn't even print
    //
    // somehow it's segfaulting before code even
    // starts to execute
    std::cout << "main called";


    Model model;
    model.Start(&exitFunc);

    return 0;
}