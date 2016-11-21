#include "randomAI.h"

RandomAI::RandomAI(){
}

RandomAI::~RandomAI(){
}

void RandomAI::init(int argc, char **argv){
}

Movement RandomAI::generatorMove(int board[5][5], int dice){
    Movement movement;
    movement.index = rand() % 6 + 1;
    movement.direction = static_cast<Movement::Direction>(rand() % 3 + 1);
    return movement;
}

void RandomAI::gameOver(bool win){
}
