#include <iostream>
#include <iomanip>
#include "MenuHelper.h"

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
	MenuHelper::printDivider();
	MenuHelper::printCenteredString(title);
	MenuHelper::printDivider();
}

int findCharsInStringCaseInsensitive(char c, string target)
{
	if (target.find(tolower(c, locale())) == string::npos)
		return 0;
	return 1;
}

unsigned inputPositiveNumber(const string prompt, size_t lowerBound, size_t upperBound)
{
	unsigned num;
	string s;
	bool valid = true;
	do
	{
		inputString(prompt, &s);
		valid = safeStoul(&num, &s, lowerBound, upperBound);
	} while (!valid || num < 1);
	return num;
}

int inputNumber(const string prompt, size_t lowerBound, size_t upperBound)
{
	int num;
	string s;
	bool valid = true;
	do
	{
		inputString(prompt, &s);
		valid = safeStoi(&num, &s, lowerBound, upperBound);
	} while (!valid);
	return num;
}

bool safeStoi(int *i, const string *s, size_t lowerBound, size_t upperBound)
{
	try
	{
		*i = stoi(*s);
		size_t size = to_string(*i).size();
		return (size < lowerBound || size > upperBound);
	}
	catch (invalid_argument)
	{
		return false;
	}
}
bool safeStoul(unsigned *i, const string *s, size_t lowerBound, size_t upperBound)
{
	try
	{
		*i = stoul(*s);
		size_t size = to_string(*i).size();
		return (size >= lowerBound && size <= upperBound);
	}
	catch (invalid_argument)
	{
		return false;
	}
}

void inputString(const string prompt, string *s)
{
	do
	{
		cout << prompt;
		getline(cin, *s);
	} while ((*s).empty());
}

} // namespace MenuHelper