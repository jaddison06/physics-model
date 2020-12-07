#include "control/GenericBaseClass.h"


GenericBaseClass::GenericBaseClass()
{
    logger = *(new Logger);
}

GenericBaseClass::~GenericBaseClass()
{
    logger.info("destroying");
    logger.destroy();

    delete &logger;
}