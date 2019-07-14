#include <sstream>
#include <iomanip>
#include "Date.h"
#include "ParsingHelper.h"

using namespace std;

unsigned countDigits(int const &num)
{
	int temp = num;
	int c = 0;
	while (temp != 0)
	{
		temp /= 10;
		c++;
	}
	return c;
}

bool tryStoulDateField(unsigned &val, const string s, const unsigned minDigits, const unsigned maxDigits, const unsigned maxVal)
{
	if (s.size() < minDigits || s.size() > maxDigits)
		return false;

	try
	{
		val = stoul(s);
		unsigned temp = countDigits(val);
		return (temp < minDigits || temp > maxDigits || val > maxVal) ? false : true;
	}
	catch (invalid_argument)
	{
		return false;
	}
}

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

	if (tryStoulDateField(this->year, date[0], 4, 4, 9999))
		if (tryStoulDateField(this->month, date[1], 1, 2, 12))
			if (tryStoulDateField(this->day, date[2], 1, 2, 31))
				valid = true;

	if (!valid)
	{
		this->year = 0;
		this->month = 0;
		this->day = 0;
	}
}

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