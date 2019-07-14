#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

struct Address
{
	std::string streetName;
	unsigned doorNumber;
	std::string apartNumber;
	std::string areaCode;
	std::string areaName;

	std::string toString() const;

	Address();
	Address(std::string sAddress);
	Address(std::string streetName, unsigned doorNumber, std::string apartNumber, std::string areaCode, std::string areaName);
};

#endif