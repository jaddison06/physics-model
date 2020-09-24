#include "Model.h"

Model::Model() {
    logger.setSender("Model");
    logger.info("Model initialised");
}

// start the Model
void Model::Start( bool (*exitFunc)(Logger *logger) ) {
    logger.info("Model starting");
    
    // are we already running?
    if (!isRunning) {
        
        // tick until we're told to stop
        while ( !exitFunc(&logger) ){
            logger.info("ticking");
            Tick();
        }


        // now shut down
        Shutdown();
    
    } else {
        logger.warning("Start was called but the model was already running");
    }
}

// 1 tick, will eventually be equivalent to a real-world time unit but this is very early
void Model::Tick(){

}

// any cleanup code goes here
void Model::Shutdown() {
    logger.destroy();
}