#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address
{
private:
	std::string streetName;
	unsigned doorNumber;
	std::string apartNumber;
	std::string areaCode;
	std::string areaName;

public:
	Address();
	Address(std::string sAddress);
	Address(std::string streetName, unsigned doorNumber, std::string apartNumber, std::string areaCode, std::string areaName);

	std::string getStreetName() const;
	std::string toString() const;
};

#endif