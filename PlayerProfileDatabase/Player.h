#pragma once
#include <fstream>

class Player
{
public:
	//default constructer
	Player();
	//constructer; takes in name as a const char array and
	Player(const char name[30], int score);
	//default deconstructer
	~Player();
	//constructer; takes in a pointer to name and score as an int
	Player(char* Name, int score);
	
	//sets the name of the player
	void setName(const char name[30]);
	//sets the score of the player
	void setScore(const int score);
	
	//saves the player's name and score
	void save(std::ofstream& out);
	//loads the players name and score
	bool load(std::ifstream& in);

	//character array that hold the player's name
	char m_name[30];
	//intiger that holds the player's score
	int m_score;
};

