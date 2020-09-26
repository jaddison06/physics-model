#include "control/GenericBaseClass.h"

void GenericBaseClass::Destroy() {
    logger.info("destroying");
    inheritedDestroy();
    logger.destroy();
}