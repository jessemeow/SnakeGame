#pragma once
#include <iostream>

class Player
{
	private:
		int score;

	public:
		Player();
		void printScore();
		void increaseScore();
		void resetScore();
};

