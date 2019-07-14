#include <iostream>
#include <iomanip>
#include "MenuTravelPack.h"
#include "MenuTravelPackEdit.h"
#include "MenuHelper.h"

using namespace std;

void addTravelPack(Agency *agency)
{
	CLEAR();

	int id = (agency->lastTravelPackID++) + 1;

	const string prompt = " >  ";
	const string prompt2 = "   >  ";
	MenuHelper::printHeader("Gestor de pacotes - Adicionar");

	MenuHelper::printLeftPaddedString("Destino:", LEFTPAD);
	string destination;
	MenuHelper::inputString(prompt, &destination);

	string date;
	Date *sd;
	do
	{
		MenuHelper::printLeftPaddedString("Data de inicio (ano/mes/dia):", LEFTPAD);
		MenuHelper::inputString(prompt, &date);
		sd = new Date(date);
	} while (sd->year == 0);

	Date *ed;
	do
	{
		MenuHelper::printLeftPaddedString("Data de fim (ano/mes/dia):", LEFTPAD);
		MenuHelper::inputString(prompt, &date);
		ed = new Date(date);
	} while (ed->year == 0 || ed->compare(*sd) <= 0);

	MenuHelper::printLeftPaddedString("Preco por pessoa:", LEFTPAD);
	unsigned pricePerPerson = MenuHelper::inputPositiveNumber(prompt, 1, 6);

	MenuHelper::printLeftPaddedString("Lotacao maxima:", LEFTPAD);
	unsigned maxPeopleAllowed = MenuHelper::inputPositiveNumber(prompt, 1, 6);

	TravelPack tp(id, destination, *sd, *ed, pricePerPerson, maxPeopleAllowed, 0);
	agency->travelPacks.push_back(tp);
	delete (sd);
	delete (ed);
	MenuHelper::printDivider();

	cout << "\nPacote criado.\nPremir 'ENTER'...";
	getchar();
	return;
}

void filterByDestination(vector<int> &packIdx, const vector<TravelPack> &packs)
{
	CLEAR();
	MenuHelper::printLeftPaddedString("Introduzir destino:", LEFTPAD);
	string destination;
	MenuHelper::inputString(" >  ", &destination);

	vector<int>::const_iterator it = packIdx.begin();
	int i;
	while (it != packIdx.end())
	{
		i = (*it);

		if (packs[packIdx[i]].locationsString.find(destination) == string::npos)
			it = packIdx.erase(it);
		else
			it++;
	}
}

void filterByDate(vector<int> &packIdx, const vector<TravelPack> &packs)
{
	CLEAR();
	MenuHelper::printLeftPaddedString("Introduzir intervalo", LEFTPAD);

	string date;
	Date *sd;
	do
	{
		MenuHelper::printLeftPaddedString("Inicio (ano/mes/dia):", LEFTPAD);
		MenuHelper::inputString(" >  ", &date);
		sd = new Date(date);
	} while (sd->year == 0);

	Date *ed;
	do
	{
		MenuHelper::printLeftPaddedString("Fim (ano/mes/dia):", LEFTPAD);
		MenuHelper::inputString(" >  ", &date);
		ed = new Date(date);
	} while (ed->year == 0 || ed->compare(*sd) <= 0);

	vector<int>::const_iterator it = packIdx.begin();
	int i;
	while (it != packIdx.end())
	{
		i = (*it);

		if (packs[packIdx[i]].startDate.compare(*sd) < 0 || packs[packIdx[i]].endDate.compare(*ed) > 0)
			it = packIdx.erase(it);
		else
			it++;
	}
}

void clearFilters(vector<int> &packIdx, const vector<TravelPack> &packs)
{
	packIdx.clear();
	packIdx.reserve(packs.size());
	int i = 0;
	for (auto p : packs)
	{
		packIdx.push_back(i++);
	}
}

void displayTravelPack(const TravelPack &pack)
{
	MenuHelper::printDivider();
	cout << left;
	cout << "| ID: " << setw(LENGTH - 7) << to_string(pack.id) + " Destino: " + pack.locationsString << "|" << endl;
	cout << "| Periodo da viagem: " << setw(LENGTH - 22)
		 << (pack.startDate.toString() + " a " + pack.endDate.toString()) << "|" << endl;

	cout << "| Preco por pessoa: " << setw(LENGTH - 21)
		 << (to_string(pack.pricePerPerson) + " | Lotacao maxima: " + to_string(pack.maxPeopleAllowed) + " | Lugares vendidos: " + to_string(pack.numberOfPeopleBooked)) << "|" << endl;

	cout << right;
	MenuHelper::printDivider();
}

void displayTravelPacks(const vector<int> &packVec, const vector<TravelPack> &packs)
{
	for (auto tp : packVec)
	{
		displayTravelPack(packs[tp]);
	}
}

void showTravelPacks(Agency *agency)
{
	vector<int> packIdx;
	clearFilters(packIdx, agency->travelPacks);

	string codeString;
	vector<MenuHelper::Option> options = {
		{"1", "Adicionar pacote"},
		{"2", "Editar pacote"},
		{"3", "Mostrar todos os pacotes"},
		{"4", "Filtrar por destino"},
		{"5", "Filtrar por data"},
		{"b", "Retroceder"},
	};
	for (size_t i = 0; i < options.size(); i++)
		codeString += options[i].code;

	char c;
	string input;
	do
	{
		CLEAR();
		CLEAR();
		MenuHelper::printHeader("Gestor de pacotes");
		MenuHelper::printLeftPaddedString("Visiveis/Registados: " + to_string(packIdx.size()) + " / " + to_string(agency->travelPacks.size()), LEFTPAD);

		MenuHelper::printDivider();
		displayTravelPacks(packIdx, agency->travelPacks);
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
			addTravelPack(agency);
			clearFilters(packIdx, agency->travelPacks);
			break;
		case '2':
			showTravelPackEdit(agency);
			break;
		case '3':
			clearFilters(packIdx, agency->travelPacks);
			break;
		case '4':
			filterByDestination(packIdx, agency->travelPacks);
			break;
		case '5':
			filterByDate(packIdx, agency->travelPacks);
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