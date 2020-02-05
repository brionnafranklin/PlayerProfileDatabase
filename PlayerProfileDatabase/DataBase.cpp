#include "pch.h"
#include "DataBase.h"
#include <iostream>

DataBase::DataBase()
{
	Player Bri("Bri", 110);
	Player Sarah("Sarah", 75);
	Player Josh("Josh", 83);
	Player Jax("Jax", 92);

	m_players = new Player[m_playerCount]{ Bri };

	addPlayer(Sarah);
	addPlayer(Josh);
	addPlayer(Jax);
}

DataBase::~DataBase()
{
}

void DataBase::start()
{
	load();
	while (!gameover)
	{
		bubbleSort();
		draw();
		getCommand();
		system("CLS");
	}
	save();
}

void DataBase::draw()
{
	for (int i = 0; i < m_playerCount; i++)
	{
		std::cout << m_players[i].m_name << " - " << m_players[i].m_score << std::endl;
	}
}

void DataBase::addPlayer(Player newPlayer)
{
	Player* temparr = new Player[m_playerCount + 1];
	for (int i = 0; i < m_playerCount; i++)
	{
		temparr[i] = m_players[i];
	}

	temparr[m_playerCount] = newPlayer;

	m_playerCount++;

	m_players = temparr;
}

void DataBase::bubbleSort()
{
	bool done = false;

	while (!done)
	{
		done = true;
		for (int i = 0; i < m_playerCount - 1; i++)
		{
			if (strcmp(m_players[i].m_name, m_players[i + 1].m_name) > 0)
			{
				swap(m_players, i, i + 1);

				done = false;

			}
		}
	}
}

void DataBase::swap(Player * players, int n, int k)
{
	char temp[30];

	strcpy_s(temp, players[n].m_name);

	strcpy_s(players[n].m_name, players[k].m_name);

	strcpy_s(players[k].m_name, temp);
}

void DataBase::getCommand()
{
	//Create the input buffer
	char input[50] = "\0";
	int inputint = 0;

	std::cout << "Enter a Command" << std::endl;
	std::cout << "search, save, new, exit" << std::endl;

	//Clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input;

	if (strcmp(input, "save") == 0) 
	{
		save();
		return;
	}
	else if (strcmp(input, "exit") == 0) 
	{
		gameover = true;
		return;
	}
	else if (strcmp(input, "search") == 0)
	{
		search();
	}
	else if (strcmp(input, "new") == 0)
	{
		newPlayer();
	}
	else
	{
		std::cout << "Invalid input" << std::endl;
		system("pause");
	}
}

void DataBase::search()
{
	char input[50] = "\0";
	int inputint = 0;
	int index = 0;

	std::cout << "Enter the name of the player you're searching." << std::endl;

	//Clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input;
	index = binarySearch(input);
	if (index != -1) {

		std::cout << "Name: " << m_players[index].m_name << std::endl;
		std::cout << "Score: " << m_players[index].m_score << std::endl;

		std::cout << "Would you like to alter this Profile Yes/No" << std::endl;
		std::cin.clear();
		std::cin >> input;
		if (strcmp(input, "Yes") == 0)
		{
			std::cout << "Please Choose a new Name For this Profile " << std::endl;
			std::cout << "New Name:" << std::endl;;
			std::cin >> input;
			m_players[index].setName(input);
			std::cout << "Please Choose a new Score For this Profile";
			std::cout << "New Score:";
			std::cin >> inputint;
			m_players[index].setScore(inputint);
			return;
		}
		else if (strcmp(input, "No") == 0)
		{
			return;
		}
		else
		{
			system("CLS");
			std::cout << "Invalid Input" << std::endl;
		}
	}
	else
	{
		system("CLS");
		std::cout << "Player not found." << std::endl;
	}
}

void DataBase::save()
{
	std::ofstream out;

	//Open the file for output in binary mode, and truncate
	out.open("DataBaseSav.dat",
		std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
	if (out.is_open()) {


		out.write((char*)&m_playerCount, sizeof(int));

		//out << m_playerCount;

		for (int i = 0; i < m_playerCount; i++)
		{
			m_players[i].save(out);
		}
	}

	else
	{
		//Could not open the file
		std::cout << "Could not open zorpsave.dat." << std::endl;
	}

	out.flush();
	out.close();

	std::cout << "Progress has been saved" << std::endl;
	system("CLS");
}

bool DataBase::load()
{
	std::ifstream in;

	//Open the file for input
	in.open("DataBaseSav.dat", std::ifstream::in | std::ifstream::binary);

	if (!in.is_open()) {
		std::cout << "loadind unsuscessful" << std::endl;
		system("pause");
		return false;
	}

	//Clear the temporary list
	if (m_tempPlayers != nullptr)
		delete[] m_tempPlayers;

	//Load the powerups
	in.read((char*)&m_tempPlayerCount, sizeof(int));
	if (in.rdstate() || m_tempPlayerCount < 0)
		return false;
	//Read the powerups
	m_tempPlayers = new Player[m_tempPlayerCount];
	for (int i = 0; i < m_tempPlayerCount; i++) {

		if (m_tempPlayers[i].load(in) == false) {
			delete[] m_tempPlayers;
			m_tempPlayers = nullptr;
			return false;
			std::cout << "failure to load";
			system("pause");
		}

	}

	m_playerCount = m_tempPlayerCount;
	m_players = m_tempPlayers;


	std::cout << "Load Successful press any key to continue" << std::endl;
	system("pause");
	system("CLS");
	return true;
}

void DataBase::newPlayer()
{
	char input[50] = "\0";
	int inputint = 0;

	std::cout << "Enter a Name of a existing player to find and edit the score of or a player you wish to create." << std::endl;

	//Clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input;

	std::cout << "Generating New Profile" << std::endl;
	std::cout << "New Name: " << input << std::endl;
	//std::cin >> input;

	std::cout << "Please Choose a new Score For this Profile" << std::endl;
	std::cout << "New Score: ";
	std::cin >> inputint;

	Player newplayer(input, inputint);
	addPlayer(newplayer);
}

int DataBase::binarySearch(char * key)
{
	int max = m_playerCount - 1;
	int min = 0;

	while (max != min)
	{
		int middle = (min + max) / 2;
		if (strcmp(m_players[middle].m_name, key) == 0)
		{
			return middle;
		}
		else if (strcmp(m_players[middle].m_name, key) > 0)
		{
			max = middle - 1;

		}
		else if (strcmp(m_players[middle].m_name, key) < 0)
		{
			min = middle + 1;
		}
	}
	return -1;
}
