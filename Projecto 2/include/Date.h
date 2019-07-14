#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
private:
	unsigned year;
	unsigned month;
	unsigned day;

public:

	Date();
	Date(std::string dateString);
	Date(unsigned year, unsigned month, unsigned day);

	unsigned getYear() const;
	unsigned getMonth() const;
	unsigned getDay() const;

	void setYear(unsigned year);
	void setMonth(unsigned month);
	void setDay(unsigned day);

	std::string toString() const;

	int compare(Date &d) const;
};

#endif