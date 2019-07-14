#include <iostream>
#include <iomanip>
#include <string>
#include "TravelPack.h"
#include "ParsingHelper.h"
#include "MenuTravelPackEdit.h"
#include "MenuHelper.h"

using namespace std;

void changeTravelPackUIntField(unsigned *field, string fieldName, size_t lowerBound, size_t upperBound)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de pacotes - Editar " + fieldName);

	MenuHelper::printLeftPaddedString(fieldName + " actual: " + to_string(*field), LEFTPAD);
	unsigned s = MenuHelper::inputPositiveNumber("|  " + fieldName + " novo  : ", lowerBound, upperBound);
	*field = s;
}

void changeTravelPackDestinationField(TravelPack *pack)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de pacotes - Editar destino");

	MenuHelper::printLeftPaddedString("Formato: destinoA - destinoB, destinoC, ...", LEFTPAD);
	MenuHelper::printLeftPaddedString("Destino actual : " + pack->locationsString, LEFTPAD);

	string destination;
	MenuHelper::inputString("|  Destino novo   : ", &destination);

	pack->locationsString = destination;
	pack->locations.clear();
	size_t start, pos = 0;
	string s;
	while ((start = destination.find_first_not_of("–-,", pos)) != string::npos)
	{
		pos = destination.find_first_of("–-,", start + 1);
		s = destination.substr(start, pos - start);
		pack->locations.push_back(ParsingHelper::removeLeadingTraillingWhitespaces(s));
	}
}

void changeTravelPackDateField(TravelPack *pack)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de pacotes - Editar periodo de viagem");

	string date;
	Date *sd;
	do
	{
		MenuHelper::printLeftPaddedString("Data de inicio actual: " + pack->startDate.toString(), LEFTPAD);
		MenuHelper::inputString("|  Data de inicio nova  : ", &date);
		sd = new Date(date);
	} while (sd->year == 0);

	Date *ed;
	do
	{
		MenuHelper::printLeftPaddedString("Data de fim actual: " + pack->endDate.toString(), LEFTPAD);
		MenuHelper::inputString("|  Data de fim nova  : ", &date);
		ed = new Date(date);
	} while (ed->year == 0 || ed->compare(*sd) <= 0);

	pack->startDate = *sd;
	pack->endDate = *ed;

	delete (sd);
	delete (ed);
}

void displayTravelPack(TravelPack *pack)
{
	cout << left;
	cout << "| ID: " << setw(LENGTH - 7) << to_string(pack->id) + " Destino: " + pack->locationsString << "|" << endl;
	cout << "| Periodo da viagem: " << setw(LENGTH - 22)
		 << (pack->startDate.toString() + " a " + pack->endDate.toString()) << "|" << endl;

	cout << "| Preco por pessoa: " << setw(LENGTH - 21)
		 << (to_string(pack->pricePerPerson) + " | Lotacao maxima: " + to_string(pack->maxPeopleAllowed) + " | Lugares vendidos: " + to_string(pack->numberOfPeopleBooked)) << "|" << endl;

	cout << right;
}

bool findPack(Agency *agency, TravelPack **pack)
{
	CLEAR();
	const string prompt = " >  ";
	MenuHelper::printHeader("Gestor de pacotes - Editor");
	MenuHelper::printLeftPaddedString("Introduzir ID do pacote:", LEFTPAD);
	int id = MenuHelper::inputPositiveNumber(prompt, 1, 9);

	for (vector<TravelPack>::iterator it = agency->travelPacks.begin(); it != agency->travelPacks.end(); it++)
	{
		if (abs((*it).id) == id)
		{
			*pack = &(*it);
			return true;
		}
	}

	MenuHelper::printDivider();
	MenuHelper::printLeftPaddedString("ID nao encontrado.", LEFTPAD);
	MenuHelper::printDivider();
	cout << "\nPremir 'ENTER'...";
	getchar();
	return false;
}

void showTravelPackEdit(Agency *agency)
{
	TravelPack *pack;
	bool found = findPack(agency, &pack);
	if (!found)
		return;

	string codeString;
	vector<MenuHelper::Option> options = {
		{"1", "Alterar destino"},
		{"2", "Alterar periodo de viagem"},
		{"3", "Alterar preco"},
		{"4", "Alterar lotacao maxima"},
		{"5", "Remover"},
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
		//cin >> c;

		//cin >> wrongInput;
		// cin.clear();
		// cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (input.size() != 1)
			c = 'r';
		else
			c = input[0];

		switch (c)
		{
		case '1':
			changeTravelPackDestinationField(pack);
			break;
		case '2':
			changeTravelPackDateField(pack);
			break;
		case '3':
			changeTravelPackUIntField(&(pack->pricePerPerson), "preco", 1, 6);
			break;
		case '4':
			changeTravelPackUIntField(&(pack->maxPeopleAllowed), "lotacao maxima", 1, 6);
			if (pack->maxPeopleAllowed > pack->numberOfPeopleBooked)
				pack->id = abs(pack->id);
			break;
		case '5':
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