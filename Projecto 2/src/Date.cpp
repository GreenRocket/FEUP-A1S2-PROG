#include <sstream>
#include <iomanip>
#include "Date.h"
#include "ParsingHelper.h"

using namespace std;

Date::Date() {}
Date::Date(string dateString)
{
	vector<string> date;
	if (ParsingHelper::stringSplit(dateString, date, '/', 3) != 0)
	{
		this->year = 0;
		this->month = 0;
		this->day = 0;
	}

	bool valid = false;
	unsigned maxDay = 31;
	
	if(ParsingHelper::safeStoul(this->year, date[0], 1970, 9999))
	{
		if(ParsingHelper::safeStoul(this->month, date[1], 1, 12))
		{
			//leap year condition, if month is 2
			if(month == 2)
				maxDay = ((year%400==0) || (year%4==0 && year%100!=0)) ? 29 : 28;
			else
			//months which has 31 days
				maxDay = (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month==12) ? 31 : 30;

			if(ParsingHelper::safeStoul(this->day, date[2], 1, maxDay))
				valid = true;
		}
	}

	if (!valid)
	{
		this->year = 0;
		this->month = 0;
		this->day = 0;
	}
}

unsigned Date::getYear() const { return this->year; }
void Date::setYear(unsigned year) { this->year = year; }

unsigned Date::getMonth() const { return this->month; }
void Date::setMonth(unsigned month) { this->month = month; }

unsigned Date::getDay() const { return this->day; }
void Date::setDay(unsigned day) { this->day = day; }

  

string Date::toString() const
{
	stringstream buffer;
	buffer << this->year << '/'
		   << setw(2) << setfill('0') << this->month << '/'
		   << setw(2) << setfill('0') << this->day;
	return buffer.str();
}

int Date::compare(Date &d) const
{
	int i = 0;

	if (this->day < d.day)
		i = -1;
	else if (this->day > d.day)
		i = 1;

	if (this->month < d.month)
		i = -1;
	else if (this->month > d.month)
		i = 1;

	if (this->year < d.year)
		i = -1;
	else if (this->year > d.year)
		i = 1;

	return i;
}