#include <iostream>
#include <iomanip>
#include <string>
#include "MenuPurchase.h"
#include "MenuHelper.h"

using namespace std;

void displayTotalSales(Agency *agency)
{
	unsigned totalPacksSold = 0;
	unsigned totalPacksValue = 0;

	unsigned temp;
	for (auto cl : agency->clientList)
	{
		for (auto tp : cl.travelPacksBought)
		{
			try
			{
				temp = agency->travelPacks.at(abs(tp) - 1).pricePerPerson;
				totalPacksValue += temp;
				totalPacksSold++;
			}
			catch (out_of_range)
			{
			}
		}
	}

	MenuHelper::printLeftPaddedString("Total de vendas (quantidade/valor): " + to_string(totalPacksSold) + " / " + to_string(totalPacksValue), LEFTPAD);
}

void registerPurchase(Agency *agency)
{
	CLEAR();
	Client *client;
	bool foundClient = false;
	const string prompt = " >  ";
	MenuHelper::printHeader("Registar compra");
	MenuHelper::printLeftPaddedString("Introduzir NIF do cliente:", LEFTPAD);
	unsigned nif = MenuHelper::inputPositiveNumber(prompt, 9, 9);

	for (vector<Client>::iterator it = agency->clientList.begin(); it != agency->clientList.end(); it++)
	{
		if ((*it).nif == nif)
		{
			client = &(*it);
			cout << client->nif << endl;
			foundClient = true;
			break;
		}
	}

	if (!foundClient)
	{
		MenuHelper::printDivider();
		MenuHelper::printLeftPaddedString("NIF nao encontrado.", LEFTPAD);
		MenuHelper::printDivider();
		cout << "\nPremir 'ENTER'...";
		getchar();
		return;
	}

	MenuHelper::printLeftPaddedString("Introduzir ID do pacote:", LEFTPAD);
	unsigned id = MenuHelper::inputPositiveNumber(prompt, 1, 9);

	try
	{
		TravelPack *tp = &(agency->travelPacks.at(id - 1));

		if (tp->id < 0)
		{
			MenuHelper::printDivider();
			MenuHelper::printLeftPaddedString("Pacote nao disponivel.", LEFTPAD);
			MenuHelper::printDivider();
			cout << "\nPremir 'ENTER'...";
			getchar();
			return;
		}

		client->AddTravelPack(tp->id);
		tp->IncreaseBookingCount();

		MenuHelper::printDivider();
		MenuHelper::printLeftPaddedString("Compra registada.", LEFTPAD);
		MenuHelper::printDivider();
		cout << "\nPremir 'ENTER'...";
		getchar();
		return;
	}
	catch (out_of_range)
	{
		MenuHelper::printDivider();
		MenuHelper::printLeftPaddedString("Pacote nao existe.", LEFTPAD);
		MenuHelper::printDivider();
		cout << "\nPremir 'ENTER'...";
		getchar();
		return;
	}
}

void displayAllPacksSoldToClient(const Client &client)
{
	MenuHelper::printDivider();
	cout << left;
	cout << "| Cliente: " << setw(LENGTH - 12) << client.name << "|" << endl;
	cout << "| Pacotes comprados: " << setw(LENGTH - 22) << client.travelPacksBoughtStr << "|" << endl;
	cout << right;
	MenuHelper::printDivider();
}

void displayAllPacksSold(Agency *agency)
{
	CLEAR();
	CLEAR();
	MenuHelper::printHeader("Pacotes vendidos");
	for (auto cl : agency->clientList)
	{
		displayAllPacksSoldToClient(cl);
	}

	MenuHelper::printDivider();
	cout << "\nPremir 'ENTER'...";
	getchar();
}

void findClient(Agency *agency)
{
	CLEAR();
	const string prompt = " >  ";
	Client client;
	MenuHelper::printHeader("Pacotes vendidos");
	MenuHelper::printLeftPaddedString("Introduzir NIF do cliente:", LEFTPAD);
	unsigned nif = MenuHelper::inputPositiveNumber(prompt, 9, 9);

	for (vector<Client>::iterator it = agency->clientList.begin(); it != agency->clientList.end(); it++)
	{
		if ((*it).nif == nif)
		{
			client = (*it);
			displayAllPacksSoldToClient(client);
			MenuHelper::printDivider();
			cout << "\nPremir 'ENTER'...";
			getchar();
			return;
		}
	}

	MenuHelper::printDivider();
	MenuHelper::printLeftPaddedString("NIF nao encontrado.", LEFTPAD);
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
		MenuHelper::printHeader("Gestor de pacotes");
		displayTotalSales(agency);
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
			registerPurchase(agency);
			break;
		case '2':
			displayAllPacksSold(agency);
			// showTravelPackEdit(agency);
			break;
		case '3':
			findClient(agency);
			// clearFilters(packIdx, agency->travelPacks);
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