#include <sstream>
#include <iostream>
#include <vector>
#include "Address.h"
#include "ParsingHelper.h"
#include "Defs.h"

using namespace std;

Address::Address() {}

Address::Address(string sAddress)
{
	vector<string> addressElements;

	// Morada mal formatada no ficheiro. Preencher com valores de erro
	if (ParsingHelper::stringSplit(sAddress, addressElements, '/', ADDRESS_ELEMENTS_SIZE) == -1)
	{
		//cerr << "Morada mal formatada: " << sAddress << endl;
		this->streetName = "XXXX";
		this->doorNumber = 0;
		this->apartNumber = "-";
		this->areaCode = "0000-000";
		this->areaName = "XXXX";
		return;
	}

	this->streetName = addressElements[0];

	if(!ParsingHelper::safeStoul(this->doorNumber, addressElements[1], 0, numeric_limits<unsigned>::max()))
		this->doorNumber = 0;

	this->apartNumber = addressElements[2];
	this->areaCode = addressElements[3];
	this->areaName = addressElements[4];
}

Address::Address(string streetName, unsigned doorNumber, string apartNumber, string areaCode, string areaName)
{
	this->streetName = streetName;
	this->doorNumber = doorNumber;
	this->apartNumber = apartNumber;
	this->areaCode = areaCode;
	this->areaName = areaName;
}

string Address::getStreetName() const
{
	return this->streetName;
}

string Address::toString() const
{
	stringstream buffer;
	buffer << this->streetName << " / "
		   << this->doorNumber << " / "
		   << this->apartNumber << " / "
		   << this->areaCode << " / "
		   << this->areaName;

	return buffer.str();
}