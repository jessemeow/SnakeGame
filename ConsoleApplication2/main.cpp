#include <iostream>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <conio.h>
#include <windows.h>
#include <cstdlib> 
#include <ctime>

#include <queue>
#include <array>

#include "Board.h"
#include "Position.h"
#include "GameInfo.h"
#include "Game.h"
#include "Player.h"

bool gameIsHappening = true;

int main()
{
    srand((unsigned)time(0));

    Game game;

    while (gameIsHappening) {

        if (_kbhit()) {
            char hitKey = _getch();
            
            game.handleInput(hitKey);
            system("cls");
            game.print(game.board);

        }

        Sleep(SLEEP_TIME);

    }
}

