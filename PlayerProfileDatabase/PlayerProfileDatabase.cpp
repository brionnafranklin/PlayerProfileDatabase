#include "pch.h"
#include <iostream>
#include "DataBase.h"

int main()
{
	std::cout << "Enter a name: ";
		char name[30];
		std::cin >> name;

	std::cout << "Enter a score: ";
		float score;
		std::cin >> score;

		Player player(name, score);


}

void save(std::ofstream& out)
{
	if (!out.is_open())
		return;
	out.write();
}