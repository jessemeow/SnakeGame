#include "Game.h"

bool Game::containsPosition(std::queue<Position> positions, const Position& targetPosition) {
    while (!positions.empty()) {
        if (targetPosition.x == positions.front().x && targetPosition.y == positions.front().y) {
            return true;
        }
        else {
            positions.pop();
        }
    }
    return false;
}

Position Game::getNewFruitPosition(std::queue<Position> previousPositionsQueue) {
    Position newFruitPosition;
    
    newFruitPosition.x = rand() % BOARD_SIZE;
    newFruitPosition.y = rand() % BOARD_SIZE;

    while (containsPosition(previousPositionsQueue, newFruitPosition)) {
        newFruitPosition.x = rand() % BOARD_SIZE;
        newFruitPosition.y = rand() % BOARD_SIZE;
    }

    return newFruitPosition;
}

Position Game::getNewPlayerPosition(char hitKey, Position playerPosition) {
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

Position Game::getDirectionDelta(char hitKey) {

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

char Game::toUpperCase(char ch) {

    if (ch >= 'a' && ch <= 'z') {
        ch -= 32;
    }

    return ch;
}

Game::Game() : fruitPos(getNewFruitPosition({})), board(fruitPos), fruitJustEaten(false) {

    board = Board(fruitPos);
    Position prevPlayerPosition = { 0,0 };
    previousPositionsQueue.push(prevPlayerPosition);

}



void Game::reset(Player& plr, Position& PrevPlayerPosition) {

    fruitJustEaten = false;
    plr.resetScore();

    PrevPlayerPosition = { 0,0 };
    previousPositionsQueue = {};
    previousPositionsQueue.push(prevPlayerPosition);

    fruitPos = getNewFruitPosition(previousPositionsQueue);
    board = Board(fruitPos);
}

void Game::print(Board board) {
    board.printBoard();
    plr.printScore();
}

void Game::handleInput(char hitKey) {

    hitKey = toUpperCase(hitKey);

    Position playerSnakeHead = getNewPlayerPosition(hitKey, prevPlayerPosition);

    previousPositionsQueue.push(playerSnakeHead);

    Position removedPosition = previousPositionsQueue.front();

    board.updateBoard(playerSnakeHead, fruitPos, removedPosition, fruitJustEaten);


    if (!fruitJustEaten) {
        previousPositionsQueue.pop();
    }
    else {
        fruitPos = getNewFruitPosition(previousPositionsQueue);
        plr.increaseScore();
    }

    prevPlayerPosition = playerSnakeHead;


    fruitJustEaten = false;

}
