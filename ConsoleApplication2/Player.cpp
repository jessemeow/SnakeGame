#include "Player.h"

Player::Player() {
	score = 0;
}

void Player::printScore() {
	std::cout << score << '\n';
}

void Player::increaseScore() {
	score += 100;
}


void Player::resetScore() {
	score = 0;
}