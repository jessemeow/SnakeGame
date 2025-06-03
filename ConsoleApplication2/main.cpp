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

bool gameIsHappening = true;


class Snake {
    private:
        std::array<bool, BOARD_SIZE * BOARD_SIZE> data;

        int index(int x, int y) const {
            return y * BOARD_SIZE + x;
        }

    public:
        explicit Snake() : data{} {
            data.fill(false);
            data[0] = true;
        }

};

struct Player {
    int playerLength;
    bool shortenSnake;
    bool fruitJustEaten;
    int score;
};


void startNewGame(Player &plr) {

    plr.fruitJustEaten = false;
    plr.playerLength = 1;
    plr.shortenSnake = true;
    plr.score = 0;
}


Position getNewFruitPosition() {

    Position newFruitPosition;

    newFruitPosition.x = rand() % BOARD_SIZE;
    newFruitPosition.y = rand() % BOARD_SIZE;

    return newFruitPosition;

}


char toUpperCase(char ch) {
    
    if (ch >= 'a' && ch <= 'z') {
        ch -= 32;
    }

    return ch;
}


bool isDirectionValid() {
    return true;
}
/// FINISH!!!

Position getDirectionDelta(char hitKey) {

    Position directionDelta = { 0, 0 };

    switch (hitKey) {
    case 'W':
        directionDelta.y = -1;
        break;
    case 'A':
        directionDelta.x = -1;
        break;
    case 'S':
        directionDelta.y = 1;
        break;
    case 'D':
        directionDelta.x = 1;
        break;
    default:
        break;
    }

    return directionDelta;
}


Position getNewPlayerPosition(char hitKey, Position playerPosition) {

    Position playerPositionDelta = getDirectionDelta(hitKey);

    Position newPlayerPosition = playerPosition;

    newPlayerPosition.x += playerPositionDelta.x;
    newPlayerPosition.y += playerPositionDelta.y;

    if (newPlayerPosition.x < 0 || newPlayerPosition.x >= BOARD_SIZE) {
        newPlayerPosition.x = playerPosition.x;
    }

    if (newPlayerPosition.y < 0 || newPlayerPosition.y >= BOARD_SIZE) {
        newPlayerPosition.y = playerPosition.y;
    }


    return newPlayerPosition;

}

//void updateSnakeInfo

void updateBoard(std::vector<std::vector<char>>& board, Position fruitPosition, Position newPlayerPosition, Position removedPlayerPosition, Player &plr) {

    board[fruitPosition.y][fruitPosition.x] = FRUIT_CHAR;
    board[newPlayerPosition.y][newPlayerPosition.x] = SNAKE_CHAR;

    if (newPlayerPosition.x == fruitPosition.x && newPlayerPosition.y == fruitPosition.y) {
        plr.fruitJustEaten = true;
    }
    else {
        board[removedPlayerPosition.y][removedPlayerPosition.x] = BOARD_CHAR;
    }

}
//FIX!!!

int main()
{
    // PRINT SCORES !


    srand((unsigned)time(0));

    Position fruitPos = getNewFruitPosition();
    //auto board = generateBoard(fruitPos);

    Board board(fruitPos);

    Player plr;
    startNewGame(plr);



    //Position prevPlayerPosition = { 0,0 };

    //std::queue<Position> previousPositions;

    //previousPositions.push(prevPlayerPosition);



    while (gameIsHappening) {

        if (_kbhit()) {
            char hitKey = _getch();
            hitKey = toUpperCase(hitKey);


            /*prevPlayerPosition = previousPositions.front();
            
            Position newPlayerPosition = getNewPlayerPosition(hitKey, prevPlayerPosition);
            previousPositions.push(newPlayerPosition);*/


            //updateBoard(board, fruitPos, newPlayerPosition, prevPlayerPosition, plr);

            system("cls");
            board.printBoard();


            if (plr.fruitJustEaten) {
                fruitPos = getNewFruitPosition();
                plr.score += 100;
                plr.playerLength++;
            }
            else {
                //previousPositions.pop();
            }

            plr.fruitJustEaten = false;
        }

        Sleep(SLEEP_TIME);

    }
}

