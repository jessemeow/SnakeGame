#pragma once
#include <iostream>

#include <conio.h>
#include <windows.h>
#include <cstdlib> 
#include <ctime>

#include <queue>
#include <array>

#include "Board.h"
#include "Position.h"
#include "GameInfo.h"
#include "Player.h"

// PRINT SCORES !

class Game
{
	private:
		Position fruitPos;
		Player plr;

		bool fruitJustEaten;

		std::queue<Position> previousPositionsQueue;
		Position prevPlayerPosition;
		Position playerSnakeHead;
		
		Position getNewFruitPosition();
		Position getNewPlayerPosition(char hitKey, Position playerPosition);
		Position getDirectionDelta(char hitKey);
		char toUpperCase(char ch);

	public:
		Game();
		Board board;
		void handleInput(char hitKey);
		void reset(Player& plr, Position& PrevPlayerPosition);
		void print(Board board, Player plr);
};

