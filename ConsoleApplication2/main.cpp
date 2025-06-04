#include <iostream>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <conio.h>
#include <windows.h>

#include <queue>
#include <array>
#include <cctype>

#include "Board.h"
#include "Position.h"
#include "GameInfo.h"
#include "Game.h"
#include "Player.h"

bool gameIsHappening = true;

int main()
{
    Game game;
    game.print(game.board);
    char hitKey = 'S';
    Sleep(2000);

    while (gameIsHappening) {

        if (_kbhit()) {
            hitKey = _getch();
            hitKey = static_cast<char>(std::toupper(static_cast<unsigned char>(hitKey))); //maybe i overdid it
        }

        game.handleInput(hitKey);

        Sleep(SLEEP_TIME);
    }
}

