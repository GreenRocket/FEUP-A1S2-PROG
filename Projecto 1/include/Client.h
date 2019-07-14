#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "Address.h"

struct Client
{
	std::string name;
	unsigned nif;
	unsigned householdSize;
	Address address;
	std::vector<int> travelPacksBought;
	std::string travelPacksBoughtStr;

	Client();
	Client(std::vector<std::string> clientContent);
	Client(std::string name, unsigned nif, unsigned householdSize, Address address);
	Client(std::string, unsigned nif, unsigned householdSize, Address address, std::vector<int> travelPacksBought);
	void AddTravelPack(int id);
	std::string toString() const;
};

#endif