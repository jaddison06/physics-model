#include "physics/GravField.h"

GravField::GravField()
{
    logger.setSender("GravField");
    addTag("gravField");

    logger.info("GravField initialized");
}

void GravField::init(double *ownerMass)
{
    // maths for this is on paper somewhere
    auto temp = sqrt(CONST_G*(*ownerMass)*M2_APPROX_KG*1000);
    size = temp;

    bodyMass = ownerMass;
}

// extraData[0] must be the 2nd object's mass
double GravField::calcFieldStrength(coord *point, std::vector<double> *extraData)
{
    logger.info("Calculating field strength");
    double m2 = (*extraData)[0];
    if (containsPoint(point))
    {
        // newton's something of something
        double r = getDist(&location, point);
        return (CONST_G*(*bodyMass)*m2)/pow(r, 2);
    } else
    {
        return 0;
    }
}
