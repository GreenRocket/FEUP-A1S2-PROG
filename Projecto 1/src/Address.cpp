#include <sstream>
#include <vector>
#include <string>
#include "Address.h"
#include "ParsingHelper.h"

#define ELEMENTS_SIZE 5

using namespace std;

Address::Address() {}

Address::Address(string sAddress)
{
	vector<string> addressElements;

	// Morada mal formatada no ficheiro. Preencher com valores de erro
	if (ParsingHelper::stringSplit(sAddress, addressElements, '/', ELEMENTS_SIZE) == -1)
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

	// try/catch para o numero da porta
	// se falhar preencher com valores de erro
	try
	{
		this->doorNumber = stoul(addressElements[1]);
	}
	catch (invalid_argument)
	{
		this->streetName = "XXXX";
		this->doorNumber = 0;
		this->apartNumber = "-";
		this->areaCode = "0000-000";
		this->areaName = "XXXX";
		return;
	}
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