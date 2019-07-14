#ifndef DATE_H
#define DATE_H

#include <string>

struct Date
{
	unsigned year;
	unsigned month;
	unsigned day;

	Date();
	Date(std::string dateString);

	std::string toString() const;

	int compare(Date &d) const;
};

#endif