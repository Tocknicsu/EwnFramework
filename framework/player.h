#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "movement.h"

class Player{
public:
    Player();
    ~Player();
    virtual void init(int argc, char **argv);
    virtual Movement generatorMove(int board[5][5], int dice);
    virtual void gameOver(bool win);
};

#endif
