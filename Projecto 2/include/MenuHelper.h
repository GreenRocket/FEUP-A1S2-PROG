#ifndef MENUHELPER_H
#define MENUHELPER_H

#include <string>

#ifdef _WIN32
#include <Windows.h>
#define CLEAR() system("cls")
#else
#define CLEAR() system("clear")
#endif

namespace MenuHelper
{

struct Option
{
	std::string code;
	std::string text;
};

void printDivider();

void printCenteredString(std::string s);

void printLeftPaddedString(std::string s, unsigned leftPad);

void printHeader(std::string title);

int findCharsInStringCaseInsensitive(char c, std::string target);

bool inputString(std::string prompt, std::string *s);

bool inputInteger(int& num, const std::string prompt, int lowerBound, int upperBound);

bool inputPositiveInteger(unsigned& num, const std::string prompt, unsigned lowerBound, unsigned upperBound);

bool inputPositiveIntegerFixed(unsigned& num, const std::string prompt, unsigned size);

bool inputDouble(double& num, const std::string prompt, double lowerBound, double upperBound);

} // namespace MenuHelper

#endif