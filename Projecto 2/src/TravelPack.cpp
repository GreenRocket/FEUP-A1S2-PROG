#include <sstream>
#include <iostream>
#include <limits>
#include <math.h>
#include "TravelPack.h"
#include "ParsingHelper.h"
#include "defs.h"

using namespace std;

TravelPack::TravelPack(vector<string> travelPackContent)
{
	bool valid = true;

	int tempID = 0;
	valid = ParsingHelper::safeStoi(tempID, travelPackContent[0], -MAX_TRAVELPACKS, MAX_TRAVELPACKS);
	this->isDisabled = (tempID < 0);
	this->id = abs(tempID);

	this->setLocations(travelPackContent[1]);

	Date start(travelPackContent[2]);
	this->startDate = start;
	Date end(travelPackContent[3]);
	this->endDate = end;

	valid = ParsingHelper::safeStod(this->pricePerPerson, travelPackContent[4], 0, numeric_limits<double>::max());

	valid = ParsingHelper::safeStoul(this->maxPeopleAllowed, travelPackContent[5], 0, numeric_limits<unsigned int>::max());

	valid = ParsingHelper::safeStoul(this->numberOfPeopleBooked, travelPackContent[6], 0, numeric_limits<unsigned int>::max());

	this->isSoldOut = (numberOfPeopleBooked == maxPeopleAllowed);

	if (!valid)
	{
		id = numeric_limits<int>::max();
		pricePerPerson = 0.0;
		maxPeopleAllowed = 0;
		numberOfPeopleBooked = 0;
		this->locations.clear();
	}
}

TravelPack::TravelPack(int id, std::string locationsString, Date startDate, Date endDate,
					   double pricePerPerson, unsigned maxPeopleAllowed, unsigned numberOfPeopleBooked)
{
	if(id < 0) this->setAvailability(false);
	this->id = abs(id);
	
	this->setLocations(locationsString);

	this->startDate = startDate;
	this->endDate = endDate;
	this->pricePerPerson = pricePerPerson;
	this->maxPeopleAllowed = maxPeopleAllowed;
	this->numberOfPeopleBooked = numberOfPeopleBooked;
}

unsigned TravelPack::getID() const { return id; }
int TravelPack::getSignedID() const { return (this->isAvailable() ? id : id * -1); }

bool TravelPack::isAvailable() const { return !(isSoldOut || isDisabled); }
void TravelPack::setAvailability(bool b) { isDisabled = b; }

unsigned TravelPack::getMaxPeopleAllowed() const { return maxPeopleAllowed; }
void TravelPack::setMaxPeopleAllowed(unsigned u)
{ 
	maxPeopleAllowed = (u >= numberOfPeopleBooked) ? u : numberOfPeopleBooked;
	isSoldOut = (maxPeopleAllowed > numberOfPeopleBooked);
}

double TravelPack::getPricePerPerson() const { return pricePerPerson; }
void TravelPack::setPricePerPerson(double d) { pricePerPerson = d; }

unsigned TravelPack::getNumberOfPeopleBooked() const { return numberOfPeopleBooked; }

Date TravelPack::getStartDate() const { return startDate; }
Date TravelPack::getEndDate() const { return endDate; }

void TravelPack::setStartDate(Date d) { this->startDate = d; }
void TravelPack::setEndDate(Date d) { this->endDate = d; }


void TravelPack::IncreaseBookingCount()
{
	if(!isAvailable())
		return;

	numberOfPeopleBooked++;

	isSoldOut = (numberOfPeopleBooked == maxPeopleAllowed);
}


string TravelPack::getLocationStr() const { return this->locationsStr; }
const vector<string>& TravelPack::getLocations() const { return this->locations; }
void TravelPack::setLocations(string destination)
{
	this->locations.clear();
	size_t start, pos = 0;
	string s;
	while ((start = destination.find_first_not_of("–-,", pos)) != string::npos)
	{
		pos = destination.find_first_of("–-,", start + 1);
		s = destination.substr(start, pos - start);

		this->locations.push_back(ParsingHelper::removeLeadingTraillingWhitespaces(s));
	}

	updateLocationStr();
}
void TravelPack::updateLocationStr()
{
	stringstream buffer;

	for (vector<string>::const_iterator i = locations.begin(); i != locations.end(); i++)
	{
		if (i == locations.begin() + 1)
			buffer << " - ";
		else if (i != locations.begin())
			buffer << " , ";
		buffer << (*i);
	}

	this->locationsStr = buffer.str();
}


string TravelPack::toString() const
{
	stringstream buffer;

	int sID = id;

	buffer << (this->isAvailable() ? sID : -sID) << '\n';

	for (vector<string>::const_iterator i = locations.begin(); i != locations.end(); i++)
	{
		if (i == locations.begin() + 1)
			buffer << " - ";
		else if (i != locations.begin())
			buffer << " , ";
		buffer << (*i);
	}
	buffer << '\n';

	buffer << startDate.toString() << '\n'
		   << endDate.toString() << '\n'
		   << pricePerPerson << '\n'
		   << maxPeopleAllowed << '\n'
		   << numberOfPeopleBooked;

	return buffer.str();
}