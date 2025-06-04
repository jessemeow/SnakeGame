#include "Player.h"

Player::Player() {
	score = 0;
}

void Player::printScore() {
	std::cout << score << '\n';
}