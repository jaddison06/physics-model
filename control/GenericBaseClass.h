#pragma once
#include "logging.h"

// not much in here but it's cool to be able to expand
//
// important stuff:
//  - inheriters must do logger.setSender() in their constructor
//
//  - inheriters must define inheritedDestroy()
//    maybe you don't need to do that let's try it and see what the linker says
//
//  - If a class has members which inherit GenericBaseClass, it is that class's
//    responsibility to call Destroy() on them in its inheritedDestroy() .

class GenericBaseClass {
    public:
        // bc this class only gets inherited, it's the responsibility of
        // whoever owns this at runtime to actually init the logger
        Logger logger;

        void Destroy();

    protected:
        // put extra destruction stuff here
        virtual void inheritedDestroy();
}