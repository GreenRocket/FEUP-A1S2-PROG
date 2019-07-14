#include <iostream>
#include <iomanip>
#include <limits>
#include "MenuTravelPack.h"
#include "MenuTravelPackEdit.h"
#include "MenuHelper.h"
#include "defs.h"

using namespace std;

void addTravelPack(Agency *agency)
{
	CLEAR();

	unsigned id = agency->getMaxTravelPackID() + 1;

	const string prompt = " >  ";
	const string prompt2 = "   >  ";
	MenuHelper::printHeader("Gestor de pacotes - Adicionar");

	MenuHelper::printLeftPaddedString("Destino:", LEFTPAD);
	string destination;
	if(!MenuHelper::inputString(prompt, &destination))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}

	string date;
	Date *sd = NULL;
	do
	{
		MenuHelper::printLeftPaddedString("Data de inicio (ano/mes/dia):", LEFTPAD);
		if(!MenuHelper::inputString(prompt, &date))
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
		MenuHelper::printLeftPaddedString("Data de fim (ano/mes/dia):", LEFTPAD);
		if(!MenuHelper::inputString(prompt, &date))
		{
			delete(ed);
			cout << "\nOperacao cancelada\nPremir 'ENTER'...";
			getchar();
			return;
		}
		ed = new Date(date);
	} while (ed->getYear() == 0 || ed->compare(*sd) <= 0);

	MenuHelper::printLeftPaddedString("Preco por pessoa:", LEFTPAD);
	double pricePerPerson;
	if(!MenuHelper::inputDouble(pricePerPerson, prompt, 1, DLIMIT))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}
	

	MenuHelper::printLeftPaddedString("Lotacao maxima:", LEFTPAD);
	unsigned maxPeopleAllowed;
	if(!MenuHelper::inputPositiveInteger(maxPeopleAllowed, prompt, 1, MAX_TRAVEL_PACK_PEOPLE))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}

	TravelPack tp(id, destination, *sd, *ed, pricePerPerson, maxPeopleAllowed, 0);
	agency->addTravelPack(tp);
	delete (sd);
	delete (ed);
	MenuHelper::printDivider();

	cout << "\nPacote criado.\nPremir 'ENTER'...";
	getchar();
	return;
}

bool searchForTravelPack(Agency *agency, TravelPack **pack, const string headerMessage)
{
	CLEAR();
	const string prompt = " >  ";
	MenuHelper::printHeader(headerMessage);
	MenuHelper::printLeftPaddedString("Introduzir ID do pacote:", LEFTPAD);
	unsigned id;
	if(!MenuHelper::inputPositiveInteger(id, prompt, 1, ULIMIT))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return false;
	}

	if(agency->tryGetTravelPack(id, pack))
		return true;

	MenuHelper::printDivider();
	MenuHelper::printLeftPaddedString("ID nao encontrado.", LEFTPAD);
	MenuHelper::printDivider();
	cout << "\nPremir 'ENTER'...";
	getchar();
	return false;
}

void filterByDestination(vector<unsigned> &packIdx, const vector<TravelPack> &packs)
{
	CLEAR();
	MenuHelper::printLeftPaddedString("Introduzir destino:", LEFTPAD);
	string destination;
	if(!MenuHelper::inputString(" >  ", &destination))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}

	vector<unsigned>::const_iterator it = packIdx.begin();
	int i;
	while (it != packIdx.end())
	{
		i = (*it);

		if (packs[packIdx[i]].getLocationStr().find(destination) == string::npos)
			it = packIdx.erase(it);
		else
			it++;
	}
}

void filterByDate(vector<unsigned> &packIdx, const vector<TravelPack> &packs)
{
	CLEAR();
	MenuHelper::printLeftPaddedString("Introduzir intervalo", LEFTPAD);

	string date;
	Date *sd = NULL;
	do
	{
		MenuHelper::printLeftPaddedString("Inicio (ano/mes/dia):", LEFTPAD);
		if(!MenuHelper::inputString(" >  ", &date))
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
		MenuHelper::printLeftPaddedString("Fim (ano/mes/dia):", LEFTPAD);
		if(!MenuHelper::inputString(" >  ", &date))
		{
			delete(ed);
			cout << "\nOperacao cancelada\nPremir 'ENTER'...";
			getchar();
			return;
		}
		ed = new Date(date);
	} while (ed->getYear() == 0 || ed->compare(*sd) <= 0);

	vector<unsigned>::const_iterator it = packIdx.begin();
	int i;
	while (it != packIdx.end())
	{
		i = (*it);

		if (packs[packIdx[i]].getStartDate().compare(*sd) < 0 || packs[packIdx[i]].getEndDate().compare(*ed) > 0)
			it = packIdx.erase(it);
		else
			it++;
	}
}

void clearFilters(vector<unsigned> &packIdx, const vector<TravelPack> &packs)
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
	cout << "| ID: " << setw(LENGTH - 7) << to_string(pack.getSignedID()) + " Destino: " + pack.getLocationStr() << "|" << endl;
	cout << "| Periodo da viagem: " << setw(LENGTH - 22)
		 << (pack.getStartDate().toString() + " a " + pack.getEndDate().toString()) << "|" << endl;

	int temp = LENGTH / 3;

	cout << "| Preco por pessoa: " << setw(temp - 20) << fixed << setprecision(2) << pack.getPricePerPerson() << defaultfloat << setprecision(0);
	cout << " | Lotacao maxima: " << setw(temp - 20) << pack.getMaxPeopleAllowed();
	cout << " | Lugares vendidos: "<< setw(temp - 21) << pack.getNumberOfPeopleBooked() << " |" << endl;

	cout << right;
	MenuHelper::printDivider();
}

void displayTravelPacks(const vector<unsigned> &packVec, const vector<TravelPack> &packs)
{
	for (auto tp : packVec)
	{
		displayTravelPack(packs[tp]);
	}
}

void showTravelPacks(Agency *agency)
{
	vector<unsigned> packIdx;
	clearFilters(packIdx, agency->getTravelPacks());

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
		MenuHelper::printLeftPaddedString("Visiveis/Registados: " + to_string(packIdx.size()) + " / " + to_string(agency->getTravelPacks().size()), LEFTPAD);

		MenuHelper::printDivider();
		displayTravelPacks(packIdx, agency->getTravelPacks());
		MenuHelper::printDivider();

		for (size_t i = 0; i < options.size(); i++)
			MenuHelper::printLeftPaddedString(options[i].code + ") " + options[i].text, LEFTPAD);
		MenuHelper::printDivider();

		cout << "  > ";
		getline(cin, input);
		c = (input.size() != 1) ? 'r' : input[0];

		switch (c)
		{
		case '1':
			addTravelPack(agency);
			clearFilters(packIdx, agency->getTravelPacks());
			break;
		case '2':
			showTravelPackEdit(agency);
			break;
		case '3':
			clearFilters(packIdx, agency->getTravelPacks());
			break;
		case '4':
			filterByDestination(packIdx, agency->getTravelPacks());
			break;
		case '5':
			filterByDate(packIdx, agency->getTravelPacks());
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