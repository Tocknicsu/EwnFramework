#include "player.h"

Player::Player(){
}

Player::~Player(){
}

void Player::init(int argc, char **argv){
}

Movement Player::generatorMove(int board[5][5], int dice){
    Movement movement;
    movement.index = 0;
    movement.direction = static_cast<Movement::Direction>(0);
    return movement;
}

void Player::gameOver(int board[5][5], bool win){
}
