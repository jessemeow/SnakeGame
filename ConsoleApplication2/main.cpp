#include <iostream>

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
    game.Sleep(1000);
 
    while (gameIsHappening) {

        if (_kbhit()) {
            hitKey = _getch();
            hitKey = static_cast<char>(std::toupper(static_cast<unsigned char>(hitKey))); //maybe i overdid it
        }

        game.handleInput(hitKey);

        game.Sleep(SLEEP_TIME);
    }
}

