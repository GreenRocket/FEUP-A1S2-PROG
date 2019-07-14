#include <iostream>
#include <string>
#include "MenuAgency.h"
#include "MenuClient.h"
#include "MenuTravelPack.h"
#include "MenuPurchase.h"
#include "MenuHelper.h"

using namespace std;

void saveChanges(Agency *agency)
{
	MenuHelper::printDivider();
	if (agency->writeClientsToFile() == 0 && agency->writeTravelPacksToFile() == 0)
		cout << "\nOK!.\nPremir 'ENTER'...";
	else
		cout << "\nErro a guardar.\nPremir 'ENTER'...";
	getchar();
	return;
}

int showAgency(Agency *agency)
{
	// Criar vetor com opções do menu
	string codeString;
	vector<MenuHelper::Option> options = {
		{"1", "Gerir clientes"},
		{"2", "Gerir pacotes turisticos"},
		{"3", "Faturacao"},
		{"4", "Guardar alteracoes em disco"},
		{"x", "Sair"},
	};
	// Criar string de comparação de input de acordo com as opções em cima
	for (size_t i = 0; i < options.size(); i++)
		codeString += options[i].code;

	// Repetir enquanto não houver input válido
	char c;
	string input;
	do
	{
		CLEAR();
		MenuHelper::printHeader("Agencia de Viagens Nice Holidays");

		MenuHelper::printLeftPaddedString("Nome  : " + agency->name, LEFTPAD);
		MenuHelper::printLeftPaddedString("NIF   : " + to_string(agency->nif), LEFTPAD);
		MenuHelper::printLeftPaddedString("URL   : " + agency->websiteURL, LEFTPAD);
		MenuHelper::printLeftPaddedString("Morada: " + agency->address.toString(), LEFTPAD);

		// Escrever opções
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
			showClients(agency);
			break;
		case '2':
			showTravelPacks(agency);
			break;
		case '3':
			showPurchases(agency);
			break;
		case '4':
			saveChanges(agency);
			break;
		case 'x':
		case 'X':
			return 0;
			break;
		default:
			break;
		}

		c = 'r';

	} while (!MenuHelper::findCharsInStringCaseInsensitive(c, codeString));
	return -1;
}