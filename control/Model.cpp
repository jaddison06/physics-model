#include "control/Model.h"

Model::Model() {
    logger.setSender("Model");

    logger.info("Model initialized");
}

// start the Model
void Model::Start( bool (*exitFunc)(Logger *) ) {
    logger.info("Model starting");

    objectHandler.Add({10, 0, 0}, {-3, 1, 2}, {0, 1, 0}, 20, 69, cube);

    // are we already running?
    if (!isRunning) {
        
        // tick until we're told to stop
        while ( !exitFunc(&logger) ){
            Tick();
        }
        logger.info("model complete, exiting");

        // testing only
        binaryCreator.CreateBinary(&objectHandler, "test.model");

        // now shut down
        Destroy();
    
    } else {
        logger.warning("Start was called but the model was already running");
    }
}


// 1 tick, will eventually be equivalent to a real-world time unit but this is very early
// probably variable as we can then calculate stuff
void Model::Tick(){
    logger.info("ticking");
    objectHandler.Tick(1);
}

// any cleanup code goes here
void Model::inheritedDestroy() {
    isRunning = false;
    objectHandler.Destroy();
}