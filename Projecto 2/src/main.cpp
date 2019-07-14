#include <iostream>
#include "Agency.h"
#include "MenuAgency.h"
#include "MenuHelper.h"
#include "defs.h"

using namespace std;

int main(void)
{
	CLEAR();

	Agency agency(AGENCY_FILE_NAME);

	// Criar structs dos pacotes de viagens, e guardar na agencia.
	if (agency.readTravelPacksFile() == -1)
	{
		cerr << "Falha ao analisar ficheiro dos pacotes de viagens: " << agency.getTravelPackFilePath() << endl;
		exit(EXIT_FAILURE);
	}
	cout << agency.getTravelPackFilePath() << " OK! " << agency.getTravelPacks().size() << " pacotes" << endl;

	// Criar structs dos clientes, e guardar na agencia.
	if (agency.readClientsFile() == -1)
	{
		cerr << "Falha ao analisar ficheiro dos clientes: " << agency.getClientFilePath() << endl;
		exit(EXIT_FAILURE);
	}
	cout << agency.getClientFilePath() << " OK! " << agency.getClients().size() << " clientes" << endl;

	// Ficheiros foram devidamente processados. Arrancar com o menu.
	cout << "\nInit OK!\nPremir 'ENTER' para continuar..." << endl;

	getchar();
	showAgency(&agency);

	return 0;
}
