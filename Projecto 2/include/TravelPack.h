#ifndef TRAVELPACK_H
#define TRAVELPACK_H

#include <string>
#include <vector>
#include <set>
#include "Date.h"

struct location
{
	std::string name;
	std::set<unsigned> packs;
	unsigned numberOfVisits;

	location(std::string name)
	{
		this->name = name;
		this->packs = packs;
		this->numberOfVisits = 0;
	}

	bool operator<(const location& other) const { return (numberOfVisits > other.numberOfVisits); }

	void addPack(unsigned u) { packs.insert(u); }
};

class TravelPack
{
private:
	unsigned id;
	bool isSoldOut;
	bool isDisabled;
	unsigned maxPeopleAllowed;
	double pricePerPerson;
	unsigned numberOfPeopleBooked;
	Date startDate;
	Date endDate;
	std::vector<std::string> locations;
	std::string locationsStr;

	void updateLocationStr();

public:

	TravelPack(std::vector<std::string> travelPackContent);
	TravelPack(int id, std::string locationsString, Date startDate, Date endDate, double pricePerPerson, unsigned maxPeopleAllowed, unsigned numberOfPeopleBooked);

	void IncreaseBookingCount();

	unsigned getID() const;
	int getSignedID() const;
	bool isAvailable() const;
	void setAvailability(bool b);

	unsigned getMaxPeopleAllowed() const;
	void setMaxPeopleAllowed(unsigned u);

	double getPricePerPerson() const;
	void setPricePerPerson(double u);

	unsigned getNumberOfPeopleBooked() const;

	Date getStartDate() const;
	Date getEndDate() const;

	void setStartDate(Date d);
	void setEndDate(Date d);

	void setLocations(std::string destination);
	const std::vector<std::string>& getLocations() const;
	std::string getLocationStr() const;

	std::string toString() const;
};

#endif