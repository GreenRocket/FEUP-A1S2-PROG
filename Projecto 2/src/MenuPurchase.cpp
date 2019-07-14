#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "MenuPurchase.h"
#include "MenuClient.h"
#include "MenuTravelPack.h"
#include "MenuHelper.h"
#include "defs.h"

using namespace std;

void displayTotalSales(Agency *agency)
{
	unsigned totalPacksSold = 0;
	unsigned totalPacksValue = 0;
	TravelPack* tempPack;

	for (auto cl : agency->getClients())
	{
		for (auto packID : cl.getTravelPacksBought())
		{
			if(agency->tryGetTravelPack(packID, &tempPack))
			{
				totalPacksValue += tempPack->getPricePerPerson();
				totalPacksSold++;
			}
		}
	}

	MenuHelper::printLeftPaddedString("Total de vendas (quantidade/valor): " + to_string(totalPacksSold) + " / " + to_string(totalPacksValue), LEFTPAD);
}

void registerPurchase(Agency *agency)
{
	Client *client;
	if(!searchForClient(agency, &client, "Faturacao - Registar compra"))
		return;

	TravelPack* pack;
	if(!searchForTravelPack(agency, &pack, "Faturacao - Registar compra"))
		return;

	if(!pack->isAvailable())
	{
		MenuHelper::printDivider();
		MenuHelper::printLeftPaddedString("Pacote indisponivel", LEFTPAD);
		MenuHelper::printDivider();
		cout << "\nPremir 'ENTER'...";
		getchar();
		return;
	}

	client->addTravelPack(pack->getID(), pack->getPricePerPerson());
	pack->IncreaseBookingCount();

	agency->visitLocation(*pack);

	MenuHelper::printDivider();
	MenuHelper::printLeftPaddedString("Compra registada.", LEFTPAD);
	MenuHelper::printDivider();
	cout << "\nPremir 'ENTER'...";
	getchar();
	return;
}

void printAllPacksSoldToClient(const Client &client)
{
	MenuHelper::printDivider();
	cout << left;
	cout << "| Cliente: " << setw(LENGTH - 12) << client.getName() << "|" << endl;
	cout << "| Pacotes comprados: " << setw(LENGTH - 22) << client.getTravelPacksBoughtStr() << "|" << endl;
	cout << right;
	MenuHelper::printDivider();
}

void displayPacksSoldToClient(Agency *agency)
{
	Client *client;
	if(searchForClient(agency, &client, "Faturacao - Registo de compras"))
	{
		printAllPacksSoldToClient(*client);
		MenuHelper::printDivider();
		cout << "\nPremir 'ENTER'...";
		getchar();
		return;
	}
}

void displayPacksSoldToEveryone(Agency *agency)
{
	CLEAR();
	CLEAR();
	MenuHelper::printHeader("Pacotes vendidos");
	for (auto cl : agency->getClients())
		printAllPacksSoldToClient(cl);

	MenuHelper::printDivider();
	cout << "\nPremir 'ENTER'...";
	getchar();
}

void showPurchases(Agency *agency)
{
	string codeString;
	vector<MenuHelper::Option> options = {
		{"1", "Registar compra"},
		{"2", "Mostrar todos os pacotes vendidos"},
		{"3", "Mostrar pacotes vendidos a cliente"},
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
		MenuHelper::printHeader("Faturacao");
		displayTotalSales(agency);
		MenuHelper::printDivider();

		for (size_t i = 0; i < options.size(); i++)
			MenuHelper::printLeftPaddedString(options[i].code + ") " + options[i].text, LEFTPAD);
		MenuHelper::printDivider();

		cout << "  > ";
		getline(cin, input);

		if (input.size() != 1)
			c = 'r';
		else
			c = input[0];

		switch (c)
		{
		case '1':
			registerPurchase(agency);
			break;
		case '2':
			displayPacksSoldToEveryone(agency);
			break;
		case '3':
			displayPacksSoldToClient(agency);
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