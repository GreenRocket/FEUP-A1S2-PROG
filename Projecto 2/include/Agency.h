#ifndef AGENCY_H
#define AGENCY_H

#include <string>
#include <vector>
#include <map>
#include "Address.h"
#include "TravelPack.h"
#include "Client.h"

class Agency
{
private:
	std::string name;
	std::string websiteURL;
	unsigned nif;
	Address address;

	unsigned maxTravelPackID;
	std::vector<TravelPack> travelPacks;
	std::string travelPackFilePath;

	unsigned maxClientID;
	std::vector<Client> clients;
	std::string clientFilePath;

	std::pair<std::map<std::string, location>::iterator,bool> locRet;

public:
	std::map<std::string, location> locations;
	Agency(std::string agencyFilePath);

	std::string getName() const;
	std::string getWebsiteURL() const;
	unsigned getNif() const;
	Address getAddress() const;

	std::string getClientFilePath() const;
	std::vector<Client> getClients() const;
	unsigned getMaxClientID() const;
	int readClientsFile();
	int writeClientsToFile();
	void addClient(Client client);
	bool tryGetClient(unsigned nif, Client **client);
	bool tryRemoveClient(unsigned nif);

	std::string getTravelPackFilePath() const;
	std::vector<TravelPack> getTravelPacks() const;
	unsigned getMaxTravelPackID() const;
	int readTravelPacksFile();
	int writeTravelPacksToFile();
	void addTravelPack(TravelPack pack);
	bool tryGetTravelPack(unsigned travelPackID, TravelPack **pack);

	void tryAddLocation(const TravelPack& pack);
	void tryRemoveLocation(const TravelPack& pack);
	void visitLocation(const TravelPack& pack);

	const std::map<std::string, location>& getLocations() const;
};

#endif