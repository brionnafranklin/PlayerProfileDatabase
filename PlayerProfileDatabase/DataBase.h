#pragma once
#include "Player.h"

//Where most of the main functions are declared
class DataBase
{
//declares all the public functions within the DataBase class
public:
	//creates default players and adds them to the database
	DataBase();
	//default deconstucter
	~DataBase();

	//calls the main functions; loops until you exit the game
	void start();
	//prints the players in the database along with their
	void draw();
	//adds a new player the the array
	void addPlayer(Player x);
	//sorts the players by letter
	void bubbleSort();
	//switches 2 players' positions in the array
	void swap(Player * players, int n, int k);

//declares all the private functions within the DataBase class
private:
	//pointer to the players in the database
	Player* m_players;

	//takes in input from the user and calls the appropriate
	void getCommand();
	//searches for an inputted profile and allows the user to edit it
	void edit();
	//saves the players in the database to a save file
	void save();
	//loads the save file if one exists
	bool load();
	//creates a new player profle and adds it to the batabase
	void newPlayer();
	//searches the database for the inputted player by name
	int binarySearch(char * key);
	
	//a bool that returns true when the game is over
	bool gameover = false;
	//an int that represents the length of the array of players
	int m_playerCount = 1;
	//an int that represents the length of the array of players but only temperarily
	int m_tempPlayerCount = 1;
	//pointer to the players in the database thats temperary
	Player* m_tempPlayers;
};

