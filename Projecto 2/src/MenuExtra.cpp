#include <algorithm>
#include <iostream>
#include "MenuExtra.h"
#include "MenuHelper.h"
#include "defs.h"

using namespace std;

bool inputListLength(unsigned& num, const string headerMessage, const unsigned upperBound)
{
	CLEAR();
	const string prompt = " >  ";
	MenuHelper::printHeader(headerMessage);
	MenuHelper::printLeftPaddedString("Introduzir numero de locais: (maximo = " + to_string(upperBound) + ")" , LEFTPAD);
	if(!MenuHelper::inputPositiveInteger(num, prompt, 1, upperBound))
	{
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return false;
	}
	return true;
}

void getSortedLocations(vector<location>& sortedLocations, const Agency* agency)
{
    sortedLocations.clear();
    for (const auto &s : agency->getLocations())
        sortedLocations.push_back(s.second);

    sort(sortedLocations.begin(), sortedLocations.end());
}

void showMostVisited(Agency *agency, const vector<location>& sortedLocations)
{
    unsigned num;

    if(!inputListLength(num, "Locais mais visitados", agency->getLocations().size()))
    {
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
    }
    
    num = (num > sortedLocations.size()) ? sortedLocations.size() : num;

    MenuHelper::printDivider();
    for (size_t i = 0; i < num; i++)
        MenuHelper::printLeftPaddedString(sortedLocations.at(i).name + ": " + to_string(sortedLocations.at(i).numberOfVisits) + " visitas", LEFTPAD);
    MenuHelper::printDivider();

    cout << "\nPremir 'ENTER'...";
    getchar();
    return;
}

void showRecommendation(Agency *agency, const vector<location>& sortedLocations)
{
    unsigned num;

    if(!inputListLength(num, "Recomendacoes para clientes", agency->getLocations().size()))
    {
		cout << "\nOperacao cancelada\nPremir 'ENTER'...";
		getchar();
		return;
    }

    num = (num > sortedLocations.size()) ? sortedLocations.size() : num;

    vector<unsigned> pacotesMaisVisitados;
    vector<unsigned>::iterator itr;

    // Para cada local em "sortedLocations"
    for (size_t i = 0; i < num; i++)
    {
        // Para cada pacote que passa nesse local
        for (const auto &s : sortedLocations.at(i).packs)
        {
            // Se ainda não está em "pacotesMaisVisitados", adicionar
            itr = find(pacotesMaisVisitados.begin(), pacotesMaisVisitados.end(), s);
            if (itr == pacotesMaisVisitados.end())
                pacotesMaisVisitados.push_back(s);
        }
    }

    vector<unsigned> packIDs;
    bool found = false;

    // Para cada cliente
    Client client;
    for (size_t i = 0; i < agency->getClients().size(); i++)
    {
        client = agency->getClients().at(i);
        packIDs = client.getTravelPacksBought();
        TravelPack *pack;

        // Para cada pacote mais visitado
        for (size_t j = 0; j < pacotesMaisVisitados.size(); j++)
        {
            unsigned ui = pacotesMaisVisitados.at(j);

            // Se não foi comprado pelo cliente
            itr = find(packIDs.begin(), packIDs.end(), ui);
            if (itr == packIDs.end())
            {
                found = true;
                agency->tryGetTravelPack(ui, &pack);

                // Recomendar
                MenuHelper::printDivider();
                MenuHelper::printLeftPaddedString(client.getName() + ": " + 
                                                "Pacote " + to_string(ui) + 
                                                " ("+ pack->getLocationStr() +")", LEFTPAD);
                MenuHelper::printDivider();
                break;
            }
        }

        if(!found)
        {
            // Dizer que cliente já comprou todos os pacotes com N locais mais visitados
            MenuHelper::printDivider();
            MenuHelper::printLeftPaddedString(client.getName() + ": ja visitou os " + to_string(num) + " locais mais visitados", LEFTPAD);
            MenuHelper::printDivider();
        }
    }

    cout << "\nPremir 'ENTER'...";
    getchar();
    return;
}

void showExtra(Agency *agency)
{
    vector<location> sortedLocations;
    getSortedLocations(sortedLocations, agency);

	string codeString;
	vector<MenuHelper::Option> options = {
		{"1", "Locais mais visitados"},
		{"2", "Recomendacoes para clientes"},
		{"b", "Retroceder"},
	};
	for (size_t i = 0; i < options.size(); i++)
		codeString += options[i].code;

	char c;
	string input;

	do
	{
		CLEAR();
		MenuHelper::printHeader("Utilitarios");

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
            showMostVisited(agency, sortedLocations);
			break;
		case '2':
            showRecommendation(agency, sortedLocations);
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