#pragma once
#include <array>
#include <iostream>

#include "Position.h"
#include "GameInfo.h"


class Board {
private:
    std::array<char, BOARD_SIZE* BOARD_SIZE> data;

    int index(int x, int y) const {
        return y * BOARD_SIZE + x;
    }

public:
    explicit Board(const Position fruitPos) : data{} {

        data.fill(BOARD_CHAR);
        data[index(fruitPos.x, fruitPos.y)] = FRUIT_CHAR;

    }


    void printBoard() const {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                std::cout << ' ' << data[index(j, i)] << ' ';
            }
            std::cout << '\n';
        }
    }

};

