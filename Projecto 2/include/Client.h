#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "Address.h"

class Client
{
private:
	std::string name;
	unsigned nif;
	unsigned householdSize;
	Address address;
	std::vector<unsigned> travelPacksBought;
	std::string travelPacksBoughtStr;
	unsigned  totalPurchased;

public:
	Client();
	Client(std::vector<std::string> clientContent);
	Client(std::string name, unsigned nif, unsigned householdSize, Address address);
	Client(std::string, unsigned nif, unsigned householdSize, Address address, std::vector<unsigned> travelPacksBought, unsigned totalPurchased);
	void addTravelPack(int id, unsigned value);
	std::string toString() const;

	std::string getName() const;
	unsigned getNIF() const;
	unsigned getHouseholdSize() const;
	Address getAddress() const;
	std::vector<unsigned> getTravelPacksBought() const;
	std::string getTravelPacksBoughtStr() const;
	unsigned getTotalPurchased() const;

	void setName(std::string name);
	void setAddress(Address addr);
	void setNIF(unsigned newNIF);
	void setHouseholdSize(unsigned newHouseholdSize);
};

#endif