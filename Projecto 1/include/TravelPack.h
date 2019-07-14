#ifndef TRAVELPACK_H
#define TRAVELPACK_H

#include <string>
#include <vector>
#include "Date.h"

struct TravelPack
{
	int id;
	std::vector<std::string> locations;
	std::string locationsString;
	Date startDate;
	Date endDate;
	unsigned pricePerPerson;
	unsigned maxPeopleAllowed;
	unsigned numberOfPeopleBooked;

	TravelPack(std::vector<std::string> travelPackContent);

	TravelPack(int id, std::string locationsString, Date startDate, Date endDate, unsigned pricePerPerson, unsigned maxPeopleAllowed, unsigned numberOfPeopleBooked);

	void IncreaseBookingCount();

	std::string toString() const;
};

#endif