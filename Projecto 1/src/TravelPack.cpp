#include <sstream>
#include <limits>
#include "TravelPack.h"
#include "ParsingHelper.h"

using namespace std;

TravelPack::TravelPack(vector<string> travelPackContent)
{
	bool valid = true;
	try
	{
		this->id = stoi(travelPackContent[0]);
	}
	catch (invalid_argument)
	{
		valid = false;
	}

	this->locationsString = travelPackContent[1];
	size_t start, pos = 0;
	string s;
	// Separar string por '–-,', colocando cada substring no vetor locations.
	while ((start = travelPackContent[1].find_first_not_of("–-,", pos)) != string::npos)
	{
		pos = travelPackContent[1].find_first_of("–-,", start + 1);
		s = travelPackContent[1].substr(start, pos - start);
		this->locations.push_back(ParsingHelper::removeLeadingTraillingWhitespaces(s));
	}

	Date sta(travelPackContent[2]);
	this->startDate = sta;
	Date end(travelPackContent[3]);
	this->endDate = end;

	try
	{
		this->pricePerPerson = stoul(travelPackContent[4]);
	}
	catch (invalid_argument)
	{
		valid = false;
	}

	try
	{
		this->maxPeopleAllowed = stoul(travelPackContent[5]);
	}
	catch (invalid_argument)
	{
		valid = false;
	}

	try
	{
		this->numberOfPeopleBooked = stoul(travelPackContent[6]);
	}
	catch (invalid_argument)
	{
		valid = false;
	}

	if (!valid)
	{
		this->id = numeric_limits<int>::max();
		this->pricePerPerson = 0;
		this->maxPeopleAllowed = 0;
		this->maxPeopleAllowed = 0;
		this->locations.clear();
	}
}

TravelPack::TravelPack(int id, std::string locationsString, Date startDate, Date endDate,
					   unsigned pricePerPerson, unsigned maxPeopleAllowed, unsigned numberOfPeopleBooked)
{
	this->id = id;

	this->locationsString = locationsString;
	vector<string> locations;
	size_t start, pos = 0;
	string s;
	while ((start = locationsString.find_first_not_of("–-,", pos)) != string::npos)
	{
		pos = locationsString.find_first_of("–-,", start + 1);
		s = locationsString.substr(start, pos - start);
		this->locations.push_back(ParsingHelper::removeLeadingTraillingWhitespaces(s));
	}

	this->locations = locations;
	this->startDate = startDate;
	this->endDate = endDate;
	this->pricePerPerson = pricePerPerson;
	this->maxPeopleAllowed = maxPeopleAllowed;
	this->numberOfPeopleBooked = numberOfPeopleBooked;
}

void TravelPack::IncreaseBookingCount()
{
	this->numberOfPeopleBooked++;

	if (this->numberOfPeopleBooked >= this->maxPeopleAllowed)
		this->id *= -1;
}

string TravelPack::toString() const
{
	stringstream buffer;

	buffer << this->id << '\n';

	for (vector<string>::const_iterator i = this->locations.begin(); i != this->locations.end(); i++)
	{
		if (i == this->locations.begin() + 1)
			buffer << " - ";
		else if (i != this->locations.begin())
			buffer << " , ";
		buffer << *i;
	}
	buffer << '\n';

	buffer << this->startDate.toString() << '\n'
		   << this->endDate.toString() << '\n'
		   << this->pricePerPerson << '\n'
		   << this->maxPeopleAllowed << '\n'
		   << this->numberOfPeopleBooked;

	return buffer.str();
}