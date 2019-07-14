#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Address.h"
#include "Client.h"
#include "MenuClientEdit.h"
#include "MenuHelper.h"

using namespace std;

void changeClientStringField(string *field, string fieldName)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de clientes - Editar " + fieldName);

	MenuHelper::printLeftPaddedString(fieldName + " actual: " + *field, LEFTPAD);
	string s;
	MenuHelper::inputString("|  " + fieldName + " novo  : ", &s);
	*field = s;
}

void changeClientUIntField(unsigned *field, string fieldName, size_t lowerBound, size_t upperBound)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de clientes - Editar " + fieldName);

	MenuHelper::printLeftPaddedString(fieldName + " actual: " + to_string(*field), LEFTPAD);
	unsigned s = MenuHelper::inputPositiveNumber("|  " + fieldName + " novo  : ", lowerBound, upperBound);
	*field = s;
}

void changeClientAddressField(Client *client)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de clientes - Editar Morada");

	MenuHelper::printLeftPaddedString("Formato: Rua/N.Porta/N.Andar/Cod.Pos./Localidade", LEFTPAD);
	MenuHelper::printLeftPaddedString("Morada actual : " + client->address.toString(), LEFTPAD);
	string morada;
	Address *addr;
	do
	{
		MenuHelper::inputString("|  Morada nova   : ", &morada);
		addr = new Address(morada);
	} while (addr->streetName.compare("XXXX") == 0);

	client->address = *addr;
	delete (addr);
}

void removeClient(Agency *agency, unsigned nif)
{
	for (vector<Client>::iterator it = agency->clientList.begin(); it != agency->clientList.end(); it++)
	{
		if ((*it).nif == nif)
		{
			agency->clientList.erase(it);
			cout << "\nCliente apagado.\nPremir 'ENTER'...";
			getchar();
			return;
		}
	}
	cout << "\nErro ao tentar apagar cliente.\nPremir 'ENTER'...";
	getchar();
	return;
}

void displayClient(Client *client)
{
	string addr = client->address.toString();
	int offset = 13;
	cout << "| Nome    : " << left << setw(LENGTH - offset) << ((client->name.size() > LENGTH - offset - 2) ? client->name.substr(0, LENGTH - offset - 4) + "..." : client->name) << "|" << endl;
	cout << "| NIF     : " << left << setw(LENGTH - offset) << client->nif << "|" << endl;
	cout << "| A.F.    : " << left << setw(LENGTH - offset) << client->householdSize << "|" << endl;
	cout << "| Morada  : " << left << setw(LENGTH - offset) << ((addr.size() > LENGTH - offset - 2) ? addr.substr(0, LENGTH - offset - 4) + "..." : addr) << "|" << endl;
	cout << "| Pacotes : " << left << setw(LENGTH - offset) << ((client->travelPacksBoughtStr.size() > LENGTH - offset - 2) ? client->travelPacksBoughtStr.substr(0, LENGTH - offset - 4) + "..." : client->travelPacksBoughtStr) << "|" << endl;
}

bool findClient(Agency *agency, Client **client)
{
	CLEAR();
	const string prompt = " >  ";
	MenuHelper::printHeader("Gestor de clientes - Editor");
	MenuHelper::printLeftPaddedString("Introduzir NIF do cliente:", LEFTPAD);
	unsigned nif = MenuHelper::inputPositiveNumber(prompt, 9, 9);

	for (vector<Client>::iterator it = agency->clientList.begin(); it != agency->clientList.end(); it++)
	{
		if ((*it).nif == nif)
		{
			*client = &(*it);
			return true;
		}
	}

	MenuHelper::printDivider();
	MenuHelper::printLeftPaddedString("NIF nao encontrado.", LEFTPAD);
	MenuHelper::printDivider();
	cout << "\nPremir 'ENTER'...";
	getchar();
	return false;
}

void showClientEdit(Agency *agency)
{
	Client *client;
	bool found = findClient(agency, &client);
	if (!found)
		return;

	string codeString;
	vector<MenuHelper::Option> options = {
		{"1", "Alterar Nome"},
		{"2", "Alterar NIF"},
		{"3", "Alterar A.F."},
		{"4", "Alterar Morada"},
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

		displayClient(client);
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
			changeClientStringField(&(client->name), "Nome");
			break;
		case '2':
			changeClientUIntField(&(client->nif), "NIF", 9, 9);
			break;
		case '3':
			changeClientUIntField(&(client->householdSize), "A.F.", 1, 2);
			break;
		case '4':
			changeClientAddressField(client);
			break;
		case '5':
			removeClient(agency, client->nif);
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