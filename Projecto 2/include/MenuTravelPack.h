#ifndef MENUTRAVELPACK_H
#define MENUTRAVELPACK_H

#include <string>
#include "Agency.h"

void showTravelPacks(Agency *agency);

bool searchForTravelPack(Agency *agency, TravelPack **pack, const std::string headerMessage);

#endif