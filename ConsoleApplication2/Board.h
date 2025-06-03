#pragma once
#include <array>
#include <iostream>

#include "Position.h"
#include "GameInfo.h"


class Board {
private:

    std::array<char, BOARD_SIZE* BOARD_SIZE> data;

    int index(int x, int y) const;

public:

    explicit Board(const Position fruitPos);

    void printBoard() const;

    void updateBoard(const Position playerPosition, const Position fruitPos, const Position removedPlayerPosition, bool & fruitJustEaten);

};

