#include <iostream>
#include <iomanip>
#include <string>
#include "Address.h"
#include "Client.h"
#include "MenuClient.h"
#include "MenuClientEdit.h"
#include "MenuHelper.h"

using namespace std;

void addClient(Agency *agency)
{
	CLEAR();
	const string prompt = " >  ";
	const string prompt2 = "   >  ";
	MenuHelper::printHeader("Gestor de clientes - Adicionar");

	MenuHelper::printLeftPaddedString("Nome:", LEFTPAD);
	string name;
	MenuHelper::inputString(prompt, &name);

	MenuHelper::printLeftPaddedString("NIF (9 digitos):", LEFTPAD);
	unsigned nif = MenuHelper::inputPositiveNumber(prompt, 9, 9);

	MenuHelper::printLeftPaddedString("Numero de elementos do agregado familiar:", LEFTPAD);
	unsigned af = MenuHelper::inputPositiveNumber(prompt, 1, 2);

	string morada;
	Address *addr;
	do
	{
		MenuHelper::printLeftPaddedString("Morada (Rua / N.Porta / N.Andar / Cod.Pos. / Localidade):", LEFTPAD);
		MenuHelper::inputString(prompt, &morada);
		addr = new Address(morada);
	} while (addr->streetName.compare("XXXX") == 0);

	Client c(name, nif, af, *addr);
	agency->clientList.push_back(c);
	delete (addr);
	MenuHelper::printDivider();

	cout << "\nCliente criado.\nPremir 'ENTER'...";
	getchar();
	return;
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
		 << "| " << endl;
	MenuHelper::printDivider();
	string addr;
	for (auto client : clients)
	{
		addr = client.address.toString();
		cout << "| " << left;
		cout << setw(18) << ((client.name.size() > 17) ? client.name.substr(0, 14) + "..." : client.name)
			 << "| ";
		cout << setw(10) << client.nif
			 << "| ";
		cout << setw(5) << client.householdSize
			 << "| ";
		cout << setw(18) << ((addr.size() > 17) ? addr.substr(0, 14) + "..." : addr)
			 << "| ";
		cout << setw(18) << ((client.travelPacksBoughtStr.size() > 17) ? client.travelPacksBoughtStr.substr(0, 14) + "..." : client.travelPacksBoughtStr)
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
		MenuHelper::printLeftPaddedString("Clientes registados: " + to_string(agency->clientList.size()), LEFTPAD);
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
			addClient(agency);
			break;
		case '2':
			showClientEdit(agency);
			break;
		case '3':
			displayAllClients(agency->clientList);
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