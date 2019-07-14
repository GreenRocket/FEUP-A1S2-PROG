#include <iostream>
#include <iomanip>
#include <string>
#include "Address.h"
#include "Client.h"
#include "MenuHelper.h"
#include "MenuClient.h"
#include "MenuClientEdit.h"
#include "defs.h"

using namespace std;

void addClient(Agency *agency)
{
	CLEAR();
	const string prompt = " >  ";
	const string prompt2 = "   >  ";
	MenuHelper::printHeader("Gestor de clientes - Adicionar");

	MenuHelper::printLeftPaddedString("Nome:", LEFTPAD);
	string name;
	if(!MenuHelper::inputString(prompt, &name))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}

	MenuHelper::printLeftPaddedString("NIF (9 digitos):", LEFTPAD);
	unsigned nif;
	if(!MenuHelper::inputPositiveIntegerFixed(nif, prompt, CLIENT_NIF_LEN))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}

	MenuHelper::printLeftPaddedString("Numero de elementos do agregado familiar:", LEFTPAD);
	unsigned af;
	if(!MenuHelper::inputPositiveInteger(af, prompt, 1, MAX_CLIENT_FAMILY_SIZE))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
	}

	string morada;
	Address *addr = NULL;
	do
	{
		MenuHelper::printLeftPaddedString("Morada (Rua / N.Porta / N.Andar / Cod.Pos. / Localidade):", LEFTPAD);
		if(!MenuHelper::inputString(prompt, &morada))
		{
			delete (addr);
			cout << "\nOperacao cancelada\nPremir 'ENTER'...";
			getchar();
			return;
		}
		addr = new Address(morada);
	} while (addr->getStreetName().compare("XXXX") == 0);

	Client c(name, nif, af, *addr);
	agency->addClient(c);
	delete (addr);
	MenuHelper::printDivider();

	cout << "\nCliente criado.\nPremir 'ENTER'...";
	getchar();
	return;
}

bool searchForClient(Agency *agency, Client **client, const string headerMessage)
{
	CLEAR();
	const string prompt = " >  ";
	MenuHelper::printHeader(headerMessage);
	MenuHelper::printLeftPaddedString("Introduzir NIF do cliente:", LEFTPAD);
	unsigned nif;
	if(!MenuHelper::inputPositiveIntegerFixed(nif, prompt, CLIENT_NIF_LEN))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return false;
	}

	if(agency->tryGetClient(nif, client))
		return true;

	MenuHelper::printDivider();
	MenuHelper::printLeftPaddedString("NIF nao encontrado.", LEFTPAD);
	MenuHelper::printDivider();
	cout << "\nPremir 'ENTER'...";
	getchar();
	return false;
}

void displayAllClients(vector<Client> clients)
{
	CLEAR();
	MenuHelper::printHeader("Gestor de clientes - Listagem");

	cout << "| " << left;
	cout << setw(18) << "Nome"
		 << "| ";
	cout << setw(10) << "NIF"
		 << "| ";
	cout << setw(5) << "A.F."
		 << "| ";
	cout << setw(18) << "Morada"
		 << "| ";
	cout << setw(18) << "Pacotes comprados"
		 << "| ";
	cout << setw(18) << "Valor total"
		 << "| " << endl;
	MenuHelper::printDivider();
	string addr;
	for (auto client : clients)
	{
		addr = client.getAddress().toString();
		cout << "| " << left;
		cout << setw(18) << ((client.getName().size() > 17) ? client.getName().substr(0, 14) + "..." : client.getName())
			 << "| ";
		cout << setw(10) << client.getNIF()
			 << "| ";
		cout << setw(5) << client.getHouseholdSize()
			 << "| ";
		cout << setw(18) << ((addr.size() > 17) ? addr.substr(0, 14) + "..." : addr)
			 << "| ";
		cout << setw(18) << ((client.getTravelPacksBoughtStr().size() > 17) ? client.getTravelPacksBoughtStr().substr(0, 14) + "..." : client.getTravelPacksBoughtStr())
			 << "| ";
		cout << setw(18) << client.getTotalPurchased()
			 << "| " << endl;
	}
	MenuHelper::printDivider();
	cout << "\nPremir 'ENTER'...";
	getchar();
}

void showClients(Agency *agency)
{
	string codeString;
	vector<MenuHelper::Option> options = {
		{"1", "Adicionar cliente"},
		{"2", "Procurar cliente"},
		{"3", "Listar clientes"},
		{"b", "Retroceder"},
	};
	for (size_t i = 0; i < options.size(); i++)
		codeString += options[i].code;

	char c;
	string input;
	do
	{
		CLEAR();
		MenuHelper::printHeader("Gestor de clientes");
		MenuHelper::printLeftPaddedString("Clientes registados: " + to_string(agency->getClients().size()), LEFTPAD);
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
			addClient(agency);
			break;
		case '2':
			showClientEdit(agency);
			break;
		case '3':
			displayAllClients(agency->getClients());
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