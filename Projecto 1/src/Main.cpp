#include <iostream>
#include "Agency.h"
#include "MenuAgency.h"
#include "MenuHelper.h"

using namespace std;

// #ifdef _WIN32
// #include <Windows.h>
// #include <cstdio>
// #define ENABLEPT() SetConsoleOutputCP(CP_UTF8);
// #else
// #define ENABLEPT()
// #endif

/*
TODO:
		Restrições no destino de novos/alterados pacotes
		Permitir filtrar destino ignorando maiusculas/minusculas

		Mais controlo no input de moradas
		verificar nº porta antes de fazer stoul - ver se só tem numeros(loop char - ascii code)

		Datas mais restritas (anos bissextos, numero de dias de cada mes)
		Gerir disponibilidade consoante a data actual do sistema

		Bastante codigo redundante entre Menus (particularmente cliente e pacote)
		Remover logica dos menus para controladores proprios
		
		Mudar estrutura dos pacotes comprados de vector para map com id como chave

		Transformar acessos de pointer para referencia
		Backup antes de abrir os ficheiros com "trunc" na altura de guardar alterações
*/

int main(void)
{
	//ENABLEPT()

	CLEAR();

	// Pedir caminho para o ficheiro da agencia a abrir.
	string agencyFilePath = "Data/agency.txt";
	cout << "Introduzir nome do ficheiro da agencia: ";
	//ENTRY_POINT:
	cin >> agencyFilePath;

	cout << endl;
	cout << endl;

	// Preencher struct da agencia com o conteudo do ficheiro
	Agency agency(agencyFilePath);
	cout << agencyFilePath << " OK!" << endl;

	// Criar structs dos pacotes de viagens, e guardar na agencia.
	if (agency.readTravelPacksFile(agency.travelPackFilePath) == -1)
	{
		cerr << "Falha ao analisar ficheiro dos pacotes de viagens: " << agency.travelPackFilePath << endl;
		exit(EXIT_FAILURE);
	}
	cout << agency.travelPackFilePath << " OK! " << agency.travelPacks.size() << " pacotes" << endl;

	// Criar structs dos clientes, e guardar na agencia.
	if (agency.readClientsFile(agency.clientFilePath) == -1)
	{
		cerr << "Falha ao analisar ficheiro dos clientes: " << agency.clientFilePath << endl;
		exit(EXIT_FAILURE);
	}
	cout << agency.clientFilePath << " OK! " << agency.clientList.size() << " clientes" << endl;

	// Ficheiros foram devidamente processados. Arrancar com o menu.
	cout << "\nInit OK!\nPremir 'ENTER' para continuar..." << endl;

	//ENTRY_POINT:
	getchar();
	showAgency(&agency);

	return 0;
}
