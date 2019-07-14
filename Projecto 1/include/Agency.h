#ifndef AGENCY_H
#define AGENCY_H

#include <string>
#include <vector>
#include "Address.h"
#include "TravelPack.h"
#include "Client.h"

struct Agency
{
	std::string name;
	int nif;
	std::string websiteURL;
	Address address;
	std::vector<TravelPack> travelPacks;
	unsigned lastTravelPackID;
	std::vector<Client> clientList;
	std::string agencyFilePath;
	std::string travelPackFilePath;
	std::string clientFilePath;

	Agency(std::string agencyFilePath);

	int readTravelPacksFile(std::string travelPacksFileName);
	int readClientsFile(std::string clientsFileName);
	int writeClientsToFile();
	int writeTravelPacksToFile();
};

#endif