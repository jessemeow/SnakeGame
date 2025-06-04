#pragma once
#include <iostream>

#include <windows.h>
#include <random>

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

	Position getNewFruitPosition(std::queue<Position> previousPositionsQueue);
	Position getNewPlayerPosition(char hitKey, Position playerPosition);
	Position getDirectionDelta(char hitKey);

	bool containsPosition(std::queue<Position> positions, const Position& targetPosition);
	bool isKeyValid(const char hitKey);
	bool isDirectionValid(const Position newPlayerPosition, const std::queue<Position> previousPositionsQueue);

public:
	Game();
	Board board;
	void handleInput(char &hitKey);
	void reset(Player& plr, Position& prevPlayerPosition, char &hitKey);
	void print(Board const& board);
	void gameOverText();
	void printGameInfo();
	void exitGame();
};

