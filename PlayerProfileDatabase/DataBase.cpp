#include "pch.h"
#include "DataBase.h"
#include <iostream>

//creates default players and adds them to the database
DataBase::DataBase()
{
	//creates 4 players and gives them each a score
	Player Bri("Bri", 110);
	Player Jax("Jax", 92);
	Player Josh("Josh", 69);
	Player Sarah("Sarah", 75);

	//creates an array of players that contains the player Bri
	m_players = new Player[m_playerCount]{ Bri };

	//adds the other 3 players to the array
	addPlayer(Jax);
	addPlayer(Josh);
	addPlayer(Sarah);
}

//default deconstucter
DataBase::~DataBase()
{
}

//calls the main functions; loops until you exit the game
void DataBase::start()
{
	//loads the save file if one exists
	load();
	//loops until the game loads
	while (!gameover)
	{
		//sorts the players by letter
		bubbleSort();
		//prints the players in the database along with their scores
		draw();
		//takes in input from the user and calls the appropriate function based on it
		getCommand();
		//clears the console
		system("CLS");
	}
	//saves the players in the database to a save file
	save();
}

//prints the players in the database along with their scores
void DataBase::draw()
{
	//iterate through the array
	for (int i = 0; i < m_playerCount; i++)
	{
		//print each player's name " - " and their score
		std::cout << m_players[i].m_name << " - " << m_players[i].m_score << std::endl;
	}
}

//adds a new player the the array
void DataBase::addPlayer(Player newPlayer)
{
	//creates a player array 1 bigger than the original
	Player* temparr = new Player[m_playerCount + 1];
	//iterates through the array
	for (int i = 0; i < m_playerCount; i++)
	{
		//fills the array with the what was in the old array
		temparr[i] = m_players[i];
	}

	//puts the new player in the last slot
	temparr[m_playerCount] = newPlayer;

	//increases the m_playerCount by 1
	m_playerCount++;

	//sets old array equal to the new one
	m_players = temparr;
}

//sorts the players by letter
void DataBase::bubbleSort()
{
	//creates a bool thats false by default
	bool sorted = false;

	//loops until sorted returns true
	while (!sorted)
	{
		//set sorted true
		sorted = true;
		//iterate through the array
		for (int i = 0; i < m_playerCount - 1; i++)
		{
			//checks to see if the name it is currently on is in order according to the one after it
			if (strcmp(m_players[i].m_name, m_players[i + 1].m_name) > 0)
			{
				//switches the player with the one after it
				swap(m_players, i, i + 1);

				//sets sorted to false
				sorted = false;
			}
		}
	}
}

//switches 2 players' positions in the array
void DataBase::swap(Player * players, int n, int k)
{
	Player temp;

	temp = players[n];

	players[n] = players[k];

	players[k] = temp;
}

//takes in input from the user and calls the appropriate function based on it
void DataBase::getCommand()
{
	//Create the input buffer
	char input[50] = "\0";
	int inputint = 0;

	//prints a message to the console telling the user which 
	std::cout << "Enter a Command" << std::endl;
	std::cout << "edit, save, new, exit" << std::endl;

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
	else if (strcmp(input, "edit") == 0)
	{
		edit();
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

void DataBase::edit()
{
	char input[50] = "\0";
	int inputint = 0;
	int index = 0;

	std::cout << "Enter the name of the player to search for." << std::endl;

	//Clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input;
	index = binarySearch(input);
	if (index != -1) {

		std::cout << m_players[index].m_name << m_players[index].m_score << std::endl;

		std::cout << "Would you like to alter this profile (yes/no)" << std::endl;
		std::cin.clear();
		std::cin >> input;
		if (strcmp(input, "yes") == 0)
		{
			std::cout << "Choose a new name for this profile " << std::endl;
			std::cout << "New name:" << std::endl;;
			std::cin >> input;
			m_players[index].setName(input);
			std::cout << "Choose a new score For this profile" << std::endl;
			std::cout << "New score:";
			std::cin >> inputint;
			m_players[index].setScore(inputint);
			return;
		}
		else if (strcmp(input, "no") == 0)
		{
			return;
		}
		else
		{
			system("CLS");
			std::cout << "Invalid input" << std::endl;
		}
	}
	else
	{
		system("CLS");
		std::cout << "Player not found." << std::endl;
	}
}

//saves the players in the database to a save file
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

//loads the save file if one exists
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


	std::cout << "Load successful." << std::endl;
	system("pause");
	system("CLS");
	return true;
}

void DataBase::newPlayer()
{
	char input[50] = "\0";
	int inputint = 0;

	std::cout << "Enter a name for the player you wish to create." << std::endl;

	//Clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input;

	std::cout << "Generating new profile" << std::endl;
	std::cout << "New Name: " << input << std::endl;
	//std::cin >> input;

	std::cout << "Please choose a new score For this profile" << std::endl;
	std::cout << "New Score: " << std::endl;
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
