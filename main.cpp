#include "Model.h"

// entrypoint for the model

// exitFunc is called repeatedly to determine
// whether or not the model should continue to the next tick
bool exitFunc() {
    return false;
}

int main() {
    Model model;
    model.setExitFunc(*exitFunc);

    model.Start();

    return 0;
}