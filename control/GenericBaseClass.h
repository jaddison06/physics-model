#pragma once
#include "logging.h"

// not much in here but it's cool to be able to expand
//
// important stuff:
//  - inheriters must do logger.setSender() in their constructor
//
//  - If a class has members which inherit GenericBaseClass, it is that class's
//    responsibility to call Destroy() on them.

class GenericBaseClass
{
    public:
        GenericBaseClass();
        ~GenericBaseClass();
        
        Logger *logger;
};