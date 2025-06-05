#include "Game.h"

void Game::Sleep(const int ms) const {

    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

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

    std::default_random_engine randGenerator;
    std::uniform_int_distribution<int> distribution(0, BOARD_SIZE-1);


    Position newFruitPosition;
    
    newFruitPosition.x = distribution(randGenerator);
    newFruitPosition.y = distribution(randGenerator);

    while (containsPosition(previousPositionsQueue, newFruitPosition)) {
        newFruitPosition.x = distribution(randGenerator);
        newFruitPosition.y = distribution(randGenerator);
    }

    return newFruitPosition;
}

bool Game::isDirectionValid(const Position newPlayerPosition, const std::queue<Position> previousPositionsQueue) {

    if (newPlayerPosition.x < 0 || newPlayerPosition.x >= BOARD_SIZE) {
        return false;
    }

    if (newPlayerPosition.y < 0 || newPlayerPosition.y >= BOARD_SIZE) {
        return false;
    }

    if (containsPosition(previousPositionsQueue, newPlayerPosition)) {
        return false;
    }

    return true;
}

bool Game::isKeyValid(const char hitKey) {

    if (hitKey == 'W' || hitKey == 'A' || hitKey == 'S' || hitKey == 'D' || hitKey == 'Q') {
        return true;
    }

    return false;
}

Position Game::getNewPlayerPosition(char hitKey, Position playerPosition) {
    Position playerPositionDelta = getDirectionDelta(hitKey);

    Position newPlayerPosition = playerPosition;

    newPlayerPosition.x += playerPositionDelta.x;
    newPlayerPosition.y += playerPositionDelta.y;

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


Game::Game() : fruitPos(getNewFruitPosition({})), board(fruitPos), fruitJustEaten(false) {

    board = Board(fruitPos);
    Position prevPlayerPosition = { 0,0 };
    previousPositionsQueue.push(prevPlayerPosition);
    
    Sleep(SLEEP_TIME*5);

}



void Game::reset(Player& plr, Position& PrevPlayerPosition, char &hitKey) {

    fruitJustEaten = false;
    plr.resetScore();

    PrevPlayerPosition = { 0,0 };
    previousPositionsQueue = {};
    previousPositionsQueue.push(prevPlayerPosition);

    fruitPos = getNewFruitPosition(previousPositionsQueue);
    board = Board(fruitPos);

    hitKey = 'S';
}

void Game::printGameInfo() {
    std::cout << "\n   Press W, A, S, D to move.\n" <<
                 "       Press Q to quit.\n";
}

void Game::print(Board const& board) {
    board.printBoard();
    std::cout << "\nSCORE:  ";
    plr.printScore();
    printGameInfo();
}

void Game::gameOverText() {
    Sleep(1500);
    system("cls");
    std::cout << "\n\n\n\t\t--- YOU LOST! ---\n\n"
              << "\t\t   SCORE: ";
    plr.printScore();
    Sleep(3000);

    std::cout << "\n\n\t\t--- RESTARTING --- \n\n";
    Sleep(1000);
    std::cout << "\n\t\t        3\n";
    Sleep(1000);
    std::cout << "\n\t\t        2\n";
    Sleep(1000);
    std::cout << "\n\t\t        1\n";
    Sleep(1000);
}

void Game::exitGame() {
    system("cls");
    exit(0);
}


void Game::handleInput(char &hitKey) {

    if (!isKeyValid(hitKey)) {
        return;
    }
    if (hitKey == 'Q') {
        exitGame();
    }

    Position playerSnakeHead = getNewPlayerPosition(hitKey, prevPlayerPosition);

    bool validDirection = isDirectionValid(playerSnakeHead, previousPositionsQueue);

    if (!validDirection) {

        gameOverText();
        reset(plr, prevPlayerPosition, hitKey);

    }
    else {

        previousPositionsQueue.push(playerSnakeHead);

        Position removedPosition = previousPositionsQueue.front();

        board.updateBoard(playerSnakeHead, fruitPos, removedPosition, fruitJustEaten);

        system("cls");
        print(board);


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

}
