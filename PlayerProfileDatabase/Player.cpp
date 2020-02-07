#include "pch.h"
#include "Player.h"

//default constructer
Player::Player()
{
	strcpy_s(m_name, "nameless");
	m_score = 0;
}

//constructer; takes in name as a const char array and score as an int
Player::Player(const char name[30], int score)
{
	strcpy_s(m_name, name);
	setScore(score);
}

//default deconsttructer
Player::~Player()
{
}

//constructer; takes in a pointer to name and score as an int
Player::Player(char * Name, int score)
{
	strcpy_s(m_name, Name);
	setScore(score);
}

//sets the name of the player
void Player::setName(const char name[30])
{
	strcpy_s(m_name, name);
}

//sets the score of the player
void Player::setScore(const int score)
{
	m_score = score;
}

//saves the player's name and score
void Player::save(std::ofstream & out)
{
	if (!out.is_open())
		return;
	out.write(m_name, 30);
	out.write((char*)&m_score, sizeof(int));
}

//loads the players name and score
bool Player::load(std::ifstream & in)
{
	if (!in.is_open())
	{
		return false;
	}

	//Load name
	in.read(m_name, 30);

	if (in.rdstate())
	{
		return false;
	}

	//Load Score
	in.read((char*)&m_score, sizeof(int));

	if (in.rdstate())
	{
		return false;
	}

	return true;
}
