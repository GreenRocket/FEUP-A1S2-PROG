#ifndef MENUCLIENT_H
#define MENUCLIENT_H

#include <string>
#include "Agency.h"

void showClients(Agency *agency);

bool searchForClient(Agency *agency, Client **client, const std::string headerMessage);

#endif