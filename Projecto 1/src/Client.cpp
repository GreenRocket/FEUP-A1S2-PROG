#include <sstream>
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
}

Client::Client(std::string name, unsigned nif, unsigned householdSize, Address address)
{
	this->name = name;
	this->nif = nif;
	this->householdSize = householdSize;
	this->address = address;
}

Client::Client(std::string name, unsigned nif, unsigned householdSize, Address address, std::vector<int> travelPacksBought)
{
	this->name = name;
	this->nif = nif;
	this->householdSize = householdSize;
	this->address = address;
	this->travelPacksBought = travelPacksBought;
}

void Client::AddTravelPack(int id)
{
	if (!this->travelPacksBought.empty())
		this->travelPacksBoughtStr += " ; ";
	this->travelPacksBought.push_back(id);

	this->travelPacksBoughtStr += to_string(id);
}

string Client::toString() const
{
	stringstream buffer;

	buffer << this->name << '\n'
		   << this->nif << '\n'
		   << this->householdSize << '\n'
		   << this->address.toString() << '\n';

	for (vector<int>::const_iterator i = this->travelPacksBought.begin(); i != this->travelPacksBought.end(); i++)
	{
		if (i != this->travelPacksBought.begin())
			buffer << " ; ";
		buffer << *i;
	}

	return buffer.str();
}