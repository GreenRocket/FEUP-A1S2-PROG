#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Address.h"
#include "Client.h"
#include "MenuClientEdit.h"
#include "MenuClient.h"
#include "MenuHelper.h"
#include "defs.h"

using namespace std;

void changeClientStringField(string& newField, const string oldField, const string fieldName)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de clientes - Editar " + fieldName);

	MenuHelper::printLeftPaddedString(fieldName + " actual: " + oldField, LEFTPAD);
	string s;
	if(!MenuHelper::inputString("|  " + fieldName + " novo  : ", &s))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}
	newField = s;
}

void changeClientUIntField(unsigned& newField, const unsigned oldField, string fieldName, size_t lowerBound, size_t upperBound)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de clientes - Editar " + fieldName);

	MenuHelper::printLeftPaddedString(fieldName + " actual: " + to_string(oldField), LEFTPAD);
	unsigned s;
	if(!MenuHelper::inputPositiveInteger(s, "|  " + fieldName + " novo  : ", lowerBound, upperBound))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}
	newField = s;
}

void changeClientAddressField(Client *client)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de clientes - Editar Morada");

	MenuHelper::printLeftPaddedString("Formato: Rua/N.Porta/N.Andar/Cod.Pos./Localidade", LEFTPAD);
	MenuHelper::printLeftPaddedString("Morada actual : " + client->getAddress().toString(), LEFTPAD);
	string morada;
	Address *addr = NULL;
	do
	{
		if(!MenuHelper::inputString("|  Morada nova   : ", &morada))
		{
			delete(addr);
			cout << "\nOperacao cancelada\nPremir 'ENTER'...";
			getchar();
			return;
		}
		addr = new Address(morada);
	} while (addr->getStreetName().compare("XXXX") == 0);

	client->setAddress(*addr);
	delete (addr);
}

void removeClient(Agency *agency, unsigned nif)
{
	if(agency->tryRemoveClient(nif))
	{
		cout << "\nCliente apagado.\nPremir 'ENTER'...";
		getchar();
		return;
	}
	cout << "\nErro ao tentar apagar cliente.\nPremir 'ENTER'...";
	getchar();
	return;
}

void displayClient(Client *client)
{
	string addr = client->getAddress().toString();
	int offset = 13;
	cout << "| Nome    : " << left << setw(LENGTH - offset) << ((client->getName().size() > LENGTH - offset - 2) ? client->getName().substr(0, LENGTH - offset - 4) + "..." : client->getName()) << "|" << endl;
	cout << "| NIF     : " << left << setw(LENGTH - offset) << client->getNIF() << "|" << endl;
	cout << "| A.F.    : " << left << setw(LENGTH - offset) << client->getHouseholdSize() << "|" << endl;
	cout << "| Morada  : " << left << setw(LENGTH - offset) << ((addr.size() > LENGTH - offset - 2) ? addr.substr(0, LENGTH - offset - 4) + "..." : addr) << "|" << endl;
	cout << "| Pacotes : " << left << setw(LENGTH - offset) << ((client->getTravelPacksBoughtStr().size() > LENGTH - offset - 2) ? client->getTravelPacksBoughtStr().substr(0, LENGTH - offset - 4) + "..." : client->getTravelPacksBoughtStr()) << "|" << endl;
}

void showClientEdit(Agency *agency)
{
	Client *client;
	if (!searchForClient(agency, &client, "Gestor de clientes - Editor"))
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

		if (input.size() != 1)
			c = 'r';
		else
			c = input[0];

		string tempString;
		unsigned tempUnsigned;

		switch (c)
		{
		case '1':
			changeClientStringField(tempString, client->getName(), "Nome");
			client->setName(tempString);
			break;
		case '2':
			changeClientUIntField(tempUnsigned, client->getNIF(), "NIF", NIF_LOWERBOUND, NIF_UPPERBOUND);
			client->setNIF(tempUnsigned);
			break;
		case '3':
			changeClientUIntField(tempUnsigned, client->getHouseholdSize(), "A.F.", 1, MAX_CLIENT_FAMILY_SIZE);
			client->setHouseholdSize(tempUnsigned);
			break;
		case '4':
			changeClientAddressField(client);
			break;
		case '5':
			removeClient(agency, client->getNIF());
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