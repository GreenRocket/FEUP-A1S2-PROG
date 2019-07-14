#include <iostream>
#include "Agency.h"
#include "ParsingHelper.h"

#define AGENCY_SIZE 6
#define TRAVELPACK_SIZE 7
#define CLIENT_SIZE 5
#define MARKER "::::::::::"

using namespace std;

Agency::Agency(string agencyFilePath)
{
	// Abrir ficheiro em modo de leitura
	ifstream inputFile;
	if (ParsingHelper::openFileRead(inputFile, agencyFilePath) == -1)
	{
		cerr << "Falha ao tentar abrir o ficheiro " << agencyFilePath << endl;
		exit(EXIT_FAILURE);
	}

	// Dividir linhas do ficheiro vetor de strings
	vector<string> agencyElements;
	if (ParsingHelper::iStreamSplitFixedSize(inputFile, agencyElements, '\n', AGENCY_SIZE) == -1)
	{
		cerr << "Ficheiro da Agência não está devidamente formatado." << endl;
		exit(EXIT_FAILURE);
	}
	inputFile.close();

	this->name = agencyElements[0];
	try
	{
		this->nif = stoi(agencyElements[1]);
	}
	catch (invalid_argument)
	{
		this->nif = 999999999;
	}
	this->websiteURL = agencyElements[2];
	Address adr(agencyElements[3]);
	this->address = adr;
	this->clientFilePath = agencyElements[4];
	this->travelPackFilePath = agencyElements[5];
	this->agencyFilePath = agencyFilePath;
}

int Agency::readTravelPacksFile(string travelPacksFileName)
{
	// Abrir ficheiro em modo de leitura
	ifstream inputFile;
	if (ParsingHelper::openFileRead(inputFile, travelPacksFileName) == -1)
		return -1;

	// Ler 1ª linha contendo o ultimo ID usado
	string travelPackSizeString;
	getline(inputFile, travelPackSizeString);
	lastTravelPackID = stoul(travelPackSizeString);

	// Dividir blocos separados por 'MARKER' em vetor de strings
	vector<string> travelPackElements;
	while (inputFile.good())
	{
		travelPackElements.clear();
		if (ParsingHelper::iStreamSplitUntilMarker(inputFile, travelPackElements, '\n', TRAVELPACK_SIZE, MARKER) == -1)
		{
			cerr << "Pacote de viagens não está devidamente formatado" << endl;
		}

		// Contruir pacote de viagens com cada bloco extraido.
		// Em caso de erro, é criado um pacote com valores de erro
		TravelPack travelPack(travelPackElements);
		this->travelPacks.push_back(travelPack);
	}

	if (lastTravelPackID != this->travelPacks.size())
		cerr << "Erro no número de pacotes esperado: " << lastTravelPackID << "/" << this->travelPacks.size() << " esperado/real" << endl;

	inputFile.close();

	return 0;
}

int Agency::readClientsFile(string clientsFileName)
{
	// Abrir ficheiro em modo de leitura
	ifstream inputFile;
	if (ParsingHelper::openFileRead(inputFile, clientsFileName) == -1)
		return -1;

	// Dividir blocos separados por 'MARKER' em vetor de strings
	vector<string> clientElements;
	while (inputFile.good())
	{
		clientElements.clear();
		if (ParsingHelper::iStreamSplitUntilMarker(inputFile, clientElements, '\n', CLIENT_SIZE, MARKER) == -1)
		{
			cerr << "Cliente não está devidamente formatado" << endl;
		}

		// Contruir cliente com cada bloco extraido.
		Client client(clientElements);
		this->clientList.push_back(client);
	}

	inputFile.close();

	return 0;
}

int Agency::writeTravelPacksToFile()
{
	// Abrir ficheiro em modo de escrita
	ofstream outputFile;
	if (ParsingHelper::openFileWrite(outputFile, this->travelPackFilePath) == -1)
	{
		cerr << "Falha ao tentar abrir o ficheiro " << this->travelPackFilePath << endl;
		getchar();
		return -1;
	}

	// Escrever na 1ª linha o ultimo ID usado
	outputFile << this->lastTravelPackID << endl;

	// Escrever cada pacote no ficheiro, separados com 'MARKER'
	for (vector<TravelPack>::const_iterator it = this->travelPacks.begin(); it != this->travelPacks.end(); it++)
	{
		if (it != this->travelPacks.begin())
			outputFile << MARKER << endl;
		outputFile << (*it).toString() << endl;
	}

	return 0;
}

int Agency::writeClientsToFile()
{
	// Abrir ficheiro em modo de escrita
	ofstream outputFile;
	if (ParsingHelper::openFileWrite(outputFile, this->clientFilePath) == -1)
	{
		cerr << "Falha ao tentar abrir o ficheiro " << this->clientFilePath << endl;
		getchar();
		return -1;
	}

	// Escrever cada cliente no ficheiro, separados com 'MARKER'
	for (vector<Client>::const_iterator it = this->clientList.begin(); it != this->clientList.end(); it++)
	{
		if (it != this->clientList.begin())
			outputFile << MARKER << endl;
		outputFile << (*it).toString() << endl;
	}

	return 0;
}