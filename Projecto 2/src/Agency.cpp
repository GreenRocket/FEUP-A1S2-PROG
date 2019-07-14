#include <iostream>
#include "Agency.h"
#include "ParsingHelper.h"
#include "defs.h"

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
		cerr << "Ficheiro da Agencia nao esta devidamente formatado." << endl;
		exit(EXIT_FAILURE);
	}
	inputFile.close();

	this->name = agencyElements[0];

	if(!ParsingHelper::safeStoul(this->nif, agencyElements[1], NIF_LOWERBOUND, NIF_UPPERBOUND))
	{
		cerr << "Agencia contem NIF invalido" << endl;
		exit(EXIT_FAILURE);
	}

	this->websiteURL = agencyElements[2];

	Address adr(agencyElements[3]);
	this->address = adr;
	this->clientFilePath = agencyElements[4];
	this->travelPackFilePath = agencyElements[5];
}


string Agency::getName() const { return this->name; }
string Agency::getWebsiteURL() const { return this->websiteURL; }
unsigned Agency::getNif() const { return this->nif; }
Address Agency::getAddress() const { return this->address; }


string Agency::getTravelPackFilePath() const { return this->travelPackFilePath; }
vector<TravelPack> Agency::getTravelPacks() const { return this->travelPacks; }
unsigned Agency::getMaxTravelPackID() const { return this->maxTravelPackID; }
int Agency::readTravelPacksFile()
{
	// Abrir ficheiro em modo de leitura
	ifstream inputFile;
	if (ParsingHelper::openFileRead(inputFile, this->travelPackFilePath) == -1)
		return -1;

	// Ler 1ª linha contendo o ultimo ID usado
	string travelPackSizeString;
	getline(inputFile, travelPackSizeString);

	ParsingHelper::safeStoul(this->maxTravelPackID, travelPackSizeString, 0, MAX_TRAVELPACKS);

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
		TravelPack tp(travelPackElements);
		addTravelPack(tp);
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
	outputFile << this->maxTravelPackID << endl;

	// Escrever cada pacote no ficheiro, separados com 'MARKER'
	for (vector<TravelPack>::const_iterator it = this->travelPacks.begin(); it != this->travelPacks.end(); it++)
	{
		if (it != this->travelPacks.begin())
			outputFile << MARKER << endl;
		outputFile << (*it).toString() << endl;
	}

	return 0;
}
void Agency::addTravelPack(TravelPack pack)
{
	travelPacks.push_back(pack);
	if(maxTravelPackID < pack.getID())
		maxTravelPackID = pack.getID();

	tryAddLocation(pack);
}
bool Agency::tryGetTravelPack(unsigned travelPackID, TravelPack **pack)
{
	for (vector<TravelPack>::iterator it = this->travelPacks.begin(); it != this->travelPacks.end(); it++)
	{
		if (it->getID() == travelPackID)
		{
			*pack = &(*it);
			return true;
		}
	}
	return false;
}


string Agency::getClientFilePath() const { return this->clientFilePath; }
vector<Client> Agency::getClients() const { return this->clients; }
unsigned Agency::getMaxClientID() const { return this->maxClientID; }
int Agency::readClientsFile()
{
	// Abrir ficheiro em modo de leitura
	ifstream inputFile;
	if (ParsingHelper::openFileRead(inputFile, this->clientFilePath) == -1)
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
		addClient(client);
		clientElements.clear();
	}

	inputFile.close();

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

	vector<Client> tempClients = this->getClients();
	// Escrever cada cliente no ficheiro, separados com 'MARKER'
	for (vector<Client>::const_iterator it = tempClients.begin(); it != tempClients.end(); it++)
	{
		if (it != tempClients.begin())
			outputFile << MARKER << endl;
		outputFile << (*it).toString() << endl;
	}

	return 0;
}
void Agency::addClient(Client client)
{
	clients.push_back(client);

	// Para cada pacote do cliente
	for (size_t i = 0; i < client.getTravelPacksBought().size(); i++)
	{
		// Se esse pacote existir
		TravelPack *pack;
		if(tryGetTravelPack(client.getTravelPacksBought().at(i), &pack))
		{
			// Para cada local do pacote (key)
			for (size_t j = 0; j < pack->getLocations().size(); j++)
			{
				// pegar no local (value)
				// incrementar "visits" do local
				locations.at(pack->getLocations().at(j)).numberOfVisits++;
			}
		}
	}
}
bool Agency::tryGetClient(unsigned nif, Client **client)
{
	for (vector<Client>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
	{
		if (it->getNIF() == nif)
		{
			*client = &(*it);
			return true;
		}
	}
	return false;
}
bool Agency::tryRemoveClient(unsigned nif)
{
	for (vector<Client>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
	{
		Client client = *it;

		if (client.getNIF() == nif)
		{
			for (size_t i = 0; i < client.getTravelPacksBought().size(); i++)
			{
				// Se esse pacote existir
				TravelPack *pack;
				if(tryGetTravelPack(client.getTravelPacksBought().at(i), &pack))
				{
					// Para cada local do pacote (key)
					for (size_t j = 0; j < pack->getLocations().size(); j++)
					{
						// pegar no local (value)
						// decrementar "visits" do local
						locations.at(pack->getLocations().at(j)).numberOfVisits--;
					}
				}

			}



			this->clients.erase(it);
			return true;
		}
	}
	return false;
}


void Agency::tryAddLocation(const TravelPack& pack)
{
	size_t size = pack.getLocations().size();
	for (size_t i = 0; i < size; i++)
	{
		string locStr = pack.getLocations().at(i);

		location loc(locStr);

		// Tentar adicionar local ao map de locais
		locRet = locations.emplace(locStr, loc);

		// Tentar adicionar ID do pacote ao set do local
		locRet.first->second.addPack(pack.getID());
	}
}
void Agency::tryRemoveLocation(const TravelPack& pack)
{
	map<string,location>::iterator mapIt;	
  	set<unsigned>::iterator setIt;

	// Ver todos os locais de um pacote:
	// se o local só existir em "pack", remove local
	// Se existir em vários, retirar apenas o ID de "pack" do local

	for (size_t i = 0; i < pack.getLocations().size(); i++)
	{
		mapIt = locations.find(pack.getLocations().at(i));
		if (mapIt != locations.end())
		{
			// remover id do pack do set do local
			setIt = mapIt->second.packs.find(pack.getID());
  			mapIt->second.packs.erase (setIt);

			// se set for vazio, remover local
			if(mapIt->second.packs.empty())
				locations.erase(mapIt);
		}
	}
}
void Agency::visitLocation(const TravelPack& pack)
{
	// Para cada local do pacote (key)
	for (size_t j = 0; j < pack.getLocations().size(); j++)
	{
		// pegar no local (value)
		// incrementar "visits" do local
		this->locations.at(pack.getLocations().at(j)).numberOfVisits++;
	}
}


const std::map<std::string, location>& Agency::getLocations() const { return this->locations; }