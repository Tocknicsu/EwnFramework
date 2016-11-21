#ifndef _RANDOMAI_H_
#define _RANDOMAI_H_
#include "player.h"
#include <cstdlib>
#include <cstdio>

class RandomAI : Player {
public:
    RandomAI();
    ~RandomAI();
    virtual void init(int argc, char **argv);
    virtual Movement generatorMove(int board[5][5], int dice);
    virtual void gameOver(bool win);
};

#endif
