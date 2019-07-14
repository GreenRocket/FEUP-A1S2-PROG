#ifndef MENUHELPER_H
#define MENUHELPER_H

#include <string>

#ifdef _WIN32
#include <Windows.h>
#define CLEAR() system("cls")
#else
#define CLEAR() system("clear")
#endif

#define LENGTH (unsigned)80
#define LEFTPAD (unsigned)2

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

void inputString(std::string prompt, std::string *s);

int inputNumber(const std::string prompt, size_t lowerBound, size_t upperBound);

unsigned inputPositiveNumber(const std::string prompt, size_t lowerBound, size_t upperBound);

bool safeStoi(int *i, const std::string *s, size_t lowerBound, size_t upperBound);

bool safeStoul(unsigned *i, const std::string *s, size_t lowerBound, size_t upperBound);

} // namespace MenuHelper

#endif

//void printTableRow(std::vector<std::string> strings, unsigned spacing);