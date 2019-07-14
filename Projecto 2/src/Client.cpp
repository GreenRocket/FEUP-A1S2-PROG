#include <sstream>
#include <iostream>
#include <limits>
#include "Client.h"
#include "ParsingHelper.h"

using namespace std;

Client::Client() {}

Client::Client(vector<string> clientContent)
{
	this->name = clientContent[0];
	this->nif = stoul(clientContent[1]);
	this->householdSize = stoul(clientContent[2]);
	Address addr(clientContent[3]);
	this->address = addr;
	size_t start, pos = 0;
	string s;
	int i = 0;
	this->travelPacksBoughtStr = clientContent[4];
	while ((start = clientContent[4].find_first_not_of(";", pos)) != string::npos)
	{
		pos = clientContent[4].find_first_of(";", start + 1);
		s = clientContent[4].substr(start, pos - start);
		i = stoi(s);
		this->travelPacksBought.push_back(i);
	}
	ParsingHelper::safeStoul(this->totalPurchased, clientContent[5], 0, numeric_limits<unsigned>::max());
}

Client::Client(string name, unsigned nif, unsigned householdSize, Address address)
{
	this->name = name;
	this->nif = nif;
	this->householdSize = householdSize;
	this->address = address;

	this->travelPacksBought.clear();
	this->travelPacksBoughtStr = "";
	this->totalPurchased = 0;
}

Client::Client(std::string name, unsigned nif, unsigned householdSize, Address address, std::vector<unsigned> travelPacksBought, unsigned totalPurchased)
{
	this->name = name;
	this->nif = nif;
	this->householdSize = householdSize;
	this->address = address;
	this->travelPacksBought = travelPacksBought;
	this->totalPurchased = totalPurchased;
}

void Client::addTravelPack(int id, unsigned value)
{
	if (!this->travelPacksBought.empty())
		this->travelPacksBoughtStr += " ; ";
	this->travelPacksBought.push_back(id);

	this->travelPacksBoughtStr += to_string(id);

	this->totalPurchased += value;
}

string Client::toString() const
{
	stringstream buffer;

	buffer << this->name << '\n'
		   << this->nif << '\n'
		   << this->householdSize << '\n'
		   << this->address.toString() << '\n';

	for (vector<unsigned>::const_iterator i = this->travelPacksBought.begin(); i != this->travelPacksBought.end(); i++)
	{
		if (i != this->travelPacksBought.begin())
			buffer << " ; ";
		buffer << *i;
	}
	buffer << '\n' << this->totalPurchased;


	return buffer.str();
}

string Client::getName() const { return this->name; }
unsigned Client::getNIF() const { return this->nif; }
unsigned Client::getHouseholdSize() const { return this->householdSize; }
Address Client::getAddress() const { return this->address; }
vector<unsigned> Client::getTravelPacksBought() const { return this->travelPacksBought; }
string Client::getTravelPacksBoughtStr() const { return this->travelPacksBoughtStr; }
unsigned Client::getTotalPurchased() const { return this->totalPurchased; }

void Client::setName(string newName) { this->name = newName; }
void Client::setAddress(Address addr) { this->address = addr; }
void Client::setNIF(unsigned newNIF) { this->nif = newNIF; }
void Client::setHouseholdSize(unsigned newHouseholdSize) { this->householdSize = newHouseholdSize; }