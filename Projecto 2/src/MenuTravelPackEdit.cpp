#include <iostream>
#include <iomanip>
#include <string>
#include "TravelPack.h"
#include "ParsingHelper.h"
#include "MenuTravelPack.h"
#include "MenuTravelPackEdit.h"
#include "MenuHelper.h"
#include "defs.h"

using namespace std;

void changeFieldUI(string header, string info)
{
	CLEAR();
	MenuHelper::printHeader(header);
	MenuHelper::printLeftPaddedString(info, LEFTPAD);
}

void changeTravelPackDestinationField(TravelPack *pack, Agency *agency)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de pacotes - Editar destino");

	MenuHelper::printLeftPaddedString("Formato: destinoA - destinoB, destinoC, ...", LEFTPAD);
	MenuHelper::printLeftPaddedString("Destino actual : " + pack->getLocationStr(), LEFTPAD);

	string destination;
	if(!MenuHelper::inputString("|  Destino novo   : ", &destination))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}

	agency->tryRemoveLocation(*pack);	
	pack->setLocations(destination);
	agency->tryAddLocation(*pack);
}

void changeTravelPackDateField(TravelPack *pack)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de pacotes - Editar periodo de viagem");

	string date;
	Date *sd = NULL;
	do
	{
		MenuHelper::printLeftPaddedString("Data de inicio actual: " + pack->getStartDate().toString(), LEFTPAD);
		if(!MenuHelper::inputString("|  Data de inicio nova  : ", &date))
		{
			delete(sd);
			cout << "\nOperacao cancelada\nPremir 'ENTER'...";
			getchar();
			return;
		}
		sd = new Date(date);
	} while (sd->getYear() == 0);

	Date *ed = NULL;
	do
	{
		MenuHelper::printLeftPaddedString("Data de fim actual: " + pack->getEndDate().toString(), LEFTPAD);
		if(!MenuHelper::inputString("|  Data de fim nova  : ", &date))
		{
			delete(ed);
			cout << "\nOperacao cancelada\nPremir 'ENTER'...";
			getchar();
			return;
		}
		ed = new Date(date);
	} while (ed->getYear() == 0 || ed->compare(*sd) <= 0);

	pack->setStartDate(*sd);
	pack->setEndDate(*ed);

	delete (sd);
	delete (ed);
}

void displayTravelPack(TravelPack *pack)
{
	cout << left;
	cout << "| ID: " << setw(LENGTH - 7) << to_string(pack->getID()) + " Destino: " + pack->getLocationStr() << "|" << endl;
	cout << "| Periodo da viagem: " << setw(LENGTH - 22)
		 << (pack->getStartDate().toString() + " a " + pack->getEndDate().toString()) << "|" << endl;

	cout << "| Preco por pessoa: " << setw(LENGTH - 21)
		 << (to_string(pack->getPricePerPerson()) + " | Lotacao maxima: " + to_string(pack->getMaxPeopleAllowed()) + " | Lugares vendidos: " + to_string(pack->getNumberOfPeopleBooked())) << "|" << endl;

	cout << right;
}

void showTravelPackEdit(Agency *agency)
{
	TravelPack *pack;
	if (!searchForTravelPack(agency, &pack, "Gestor de clientes - Editor"))
		return;

	string codeString;
	vector<MenuHelper::Option> options = {
		{"1", "Alterar destino"},
		{"2", "Alterar periodo de viagem"},
		{"3", "Alterar preco"},
		{"4", "Alterar lotacao maxima"},
		{"5", "Desativar"},
		{"b", "Retroceder"},
	};
	for (size_t i = 0; i < options.size(); i++)
		codeString += options[i].code;

	char c;
	string input;

	do
	{
		CLEAR();
		MenuHelper::printHeader("Gestor de clientes - Editor");

		displayTravelPack(pack);
		MenuHelper::printDivider();
		for (size_t i = 0; i < options.size(); i++)
			MenuHelper::printLeftPaddedString(options[i].code + ") " + options[i].text, LEFTPAD);
		MenuHelper::printDivider();

		cout << "  > ";
		getline(cin, input);
		c = (input.size() != 1) ? 'r' : input[0];

		

		unsigned tempUnsigned;
		double tempDouble;
		switch (c)
		{
		case '1':
			changeTravelPackDestinationField(pack, agency);
			break;
		case '2':
			changeTravelPackDateField(pack);
			break;
		case '3':
			changeFieldUI("Gestor de pacotes - Editar Preco", ("Preco actual: " + to_string(pack->getPricePerPerson())));
			if(!MenuHelper::inputDouble(tempDouble, "|  Preco novo  : ", 1, DLIMIT))
			{
				cout << "\nOperacao cancelada\nPremir 'ENTER'...";
				getchar();
				break;
			}
			pack->setPricePerPerson(tempDouble);
			break;
		case '4':
			changeFieldUI("Gestor de pacotes - Editar Lotacao maxima", ("Lotacao maxima actual: " + to_string(pack->getMaxPeopleAllowed())));
			if(!MenuHelper::inputPositiveInteger(tempUnsigned, "| Lotacao maxima nova  : ", pack->getNumberOfPeopleBooked(), MAX_TRAVEL_PACK_PEOPLE))
			{
				cout << "\nOperacao cancelada\nPremir 'ENTER'...";
				getchar();
				break;
			}
			pack->setMaxPeopleAllowed(tempUnsigned);
			break;
		case '5':
			pack->setAvailability(false);
			break;
		case 'b':
		case 'B':
			return;
			break;
		default:
			break;
		}
		c = 'r';

	} while (!MenuHelper::findCharsInStringCaseInsensitive(c, codeString));

	return;
}