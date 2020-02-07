#pragma once
#include "Player.h"

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

	//
	void getCommand();
	//
	void edit();
	//
	void save();
	//
	bool load();
	//
	void newPlayer();
	//
	int binarySearch(char * key);
	//
	bool gameover = false;
	//
	int m_playerCount = 1;
	//
	int m_tempPlayerCount = 1;
	//
	Player* m_tempPlayers;
};

