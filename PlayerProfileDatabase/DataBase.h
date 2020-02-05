#pragma once
#include "Player.h"

class DataBase
{
public:
	DataBase();
	~DataBase();

	void start();
	void draw();

	void addPlayer(Player x);

	void bubbleSort();

	void swap(Player * players, int n, int k);

private:
	Player* m_players;

	void getCommand();
	void search();
	void save();
	bool load();
	void newPlayer();

	int binarySearch(char * key);

	bool gameover = false;

	int m_playerCount = 1;
	int m_tempPlayerCount = 1;
	Player* m_tempPlayers;
};

