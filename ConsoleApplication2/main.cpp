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

char toUpperCase(char ch) {

    if (ch >= 'a' && ch <= 'z') {
        ch -= 32;
    }

    return ch;
}

int main()
{
    srand((unsigned)time(0));

    Game game;
    game.print(game.board);

    while (gameIsHappening) {

        if (_kbhit()) {
            char hitKey = _getch();
            hitKey = toUpperCase(hitKey);

            game.handleInput(hitKey);
            
        }
        Sleep(SLEEP_TIME);
    }
}

