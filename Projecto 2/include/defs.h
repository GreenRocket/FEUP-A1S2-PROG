#ifndef DEFS_H
#define DEFS_H

#include <limits>
#include <string>

const unsigned ULIMIT = std::numeric_limits<unsigned>::max();
const double DLIMIT = std::numeric_limits<double>::max();
const unsigned NIF_LOWERBOUND = 100000000;
const unsigned NIF_UPPERBOUND = 999999999;

const unsigned LENGTH = 100;
const unsigned LEFTPAD = 2;


const std::string AGENCY_FILE_NAME = "Data/agency.txt";
const unsigned short AGENCY_SIZE = 6;


const unsigned short TRAVELPACK_SIZE = 7;
const unsigned short CLIENT_SIZE = 6;
const std::string MARKER = "::::::::::";

const unsigned short ADDRESS_ELEMENTS_SIZE = 5;


const unsigned CLIENT_NIF_LEN = 9;

const unsigned MAX_CLIENT_FAMILY_SIZE = 99;

const unsigned MAX_TRAVEL_PACK_PEOPLE = 99;

const unsigned MAX_TRAVELPACKS = 999;

#endif

