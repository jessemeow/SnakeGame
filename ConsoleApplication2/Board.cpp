#include "Board.h"

Board::Board(const Position fruitPos) : data{} {
    data.fill(BOARD_CHAR);
    data[index(fruitPos.x, fruitPos.y)] = FRUIT_CHAR;
    data[0] = SNAKE_CHAR;
}


int Board::index(int x, int y) const {
    return y * BOARD_SIZE + x;
}



void Board::printBoard() const {

    /// REMOVE VVV !
    std::cout << "   ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i << "  ";
    }
    std::cout << '\n';
    ///

    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i << ' '; ///  REMOVE!
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << ' ' << data[index(j, i)] << ' ';
        }
        std::cout << '\n';
    }
}


void Board::updateBoard(const Position playerSnakeHead, const Position fruitPos,
                        const Position removedPlayerPosition, bool &fruitJustEaten) {

    data[index(fruitPos.x, fruitPos.y)] = FRUIT_CHAR;
    
    if (playerSnakeHead.x == fruitPos.x && playerSnakeHead.y == fruitPos.y) {
        fruitJustEaten = true;
   }

    data[index(removedPlayerPosition.x, removedPlayerPosition.y)] = BOARD_CHAR;
    data[index(playerSnakeHead.x, playerSnakeHead.y)] = SNAKE_CHAR;
}
