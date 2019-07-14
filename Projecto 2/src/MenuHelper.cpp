#include "MenuHelper.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <csignal>
#include "ParsingHelper.h"
#include "defs.h"

using namespace std;

namespace MenuHelper
{

void printDivider()
{
	cout << '|';
	for (unsigned i = 0; i < LENGTH - 2; i++)
		cout << '-';
	cout << '|' << endl;
}

void printCenteredString(string s)
{
	unsigned leftPad = LENGTH / 2 + (s.size() / 2);
	unsigned rightPad = LENGTH - leftPad;
	cout << '|' << setw(leftPad) << s << setw(rightPad - 1) << right << '|' << endl;
}

void printLeftPaddedString(string s, unsigned leftPad)
{
	unsigned _leftPad = leftPad + s.size();
	unsigned _rightPad = LENGTH - _leftPad - 1;
	cout << '|' << right << setw(_leftPad) << s << setw(_rightPad) << right << '|' << endl;
}

void printHeader(string title)
{
	printDivider();
	printCenteredString(title);
	printDivider();
}

int findCharsInStringCaseInsensitive(char c, string target)
{
	c = tolower(c);
	if (target.find(c) == string::npos)
		return 0;
	return 1;
}

bool checkStringIsNotBlank(const string s)
{
	return (s.find_first_not_of(' ') != std::string::npos);
}

bool inputString(const string prompt, string *s)
{
	do
	{
		cout << prompt;
		getline(cin, *s);

		size_t n = (*s).find( '\x18' );
		if (n != (*s).npos)
			return false;

	} while ((*s).empty() || !checkStringIsNotBlank(*s));

	return true;
}

bool inputInteger(int& num, const string prompt, int lowerBound, int upperBound)
{
	string s;
	bool valid = true;
	do
	{
		if(!inputString(prompt, &s))
			return false;

		valid = ParsingHelper::safeStoi(num, s, lowerBound, upperBound);
	} while (!valid);
	return true;
}

bool inputPositiveInteger(unsigned& num, const string prompt, unsigned lowerBound, unsigned upperBound)
{
	string s;
	bool valid = true;
	do
	{
		if(!inputString(prompt, &s))
			return false;

		valid = ParsingHelper::safeStoul(num, s, lowerBound, upperBound);
	} while (!valid || num < 1);
	return true;
}

bool inputPositiveIntegerFixed(unsigned& num, const string prompt, unsigned size)
{
	string s;
	bool valid = true;
	do
	{
		if(!inputString(prompt, &s))
			return false;

		valid = (s.length() == size && ParsingHelper::safeStoul(num, s, 0, numeric_limits<unsigned>::max() ));
	} while (!valid || num < 1);
	return true;
}

bool inputDouble(double& num, const string prompt, double lowerBound, double upperBound)
{
	string s;
	bool valid = true;
	do
	{
		if(!inputString(prompt, &s))
			return false;

		valid = ParsingHelper::safeStod(num, s, lowerBound, upperBound);
	} while (!valid || num < 1);
	return true;
}

} // namespace MenuHelper