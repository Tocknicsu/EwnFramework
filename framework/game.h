#ifndef _GAME_H_
#define _GAME_H_
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cstring>


#include "chess.h"
#include "player.h"

class Game{
private:
    int board[5][5];
    int turn;
    int dice;
    Chess chess[2][6];
    Player *player[2];
public:
    Game();
    ~Game();
    /* reset a new game */
    void init();
    void setBoard(int _board[5][5]);
    void setDice(int _dice);
    void setTurn(int _turn);
    void setPlayer(int index, Player *_player);
    void switchPlayer();
    void generatorDice();
    void genPlayerBoard(int playerBoard[5][5]);
    Movement generatorMove();
    bool isValidMove(Movement movement);
    void move(Movement movement);
    bool terminated();
    void gameOver(int player);
    void print();
};


#endif
