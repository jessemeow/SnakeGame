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

//
//class Snake {
//    private:
//        std::array<bool, BOARD_SIZE * BOARD_SIZE> data;
//
//        int index(int x, int y) const {
//            return y * BOARD_SIZE + x;
//        }
//
//    public:
//        explicit Snake() : data{} {
//            data.fill(false);
//            data[0] = true;
//        }
//
//};
//

struct Player {
    int playerLength;
    bool shortenSnake;
    bool fruitJustEaten;
    int score;
};


void startNewGame(Player &plr, Position PrevPlayerPosition) {

    plr.fruitJustEaten = false;
    plr.playerLength = 1;
    plr.shortenSnake = true;
    plr.score = 0;

    PrevPlayerPosition = { 0,0 };
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

    Board board(fruitPos);

    Position prevPlayerPosition;

    Player plr;
    startNewGame(plr, prevPlayerPosition);

    //std::queue<Position> previousPositions;

    //previousPositions.push(prevPlayerPosition);



    while (gameIsHappening) {

        if (_kbhit()) {
            char hitKey = _getch();
            hitKey = toUpperCase(hitKey);

            Position newPlayerPosition = getNewPlayerPosition(hitKey, prevPlayerPosition);
            board.updateBoard(newPlayerPosition, fruitPos, {0,0}, plr.fruitJustEaten);

            /*prevPlayerPosition = previousPositions.front();
            
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

