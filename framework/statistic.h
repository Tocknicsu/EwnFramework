#ifndef _STATISTIC_H_
#define _STATISTIC_H_
#include <cstdio>
#include <ctime>

class Statistic{
private:
    int GameCount;
    int WinPlayer[2];
    int MoveCount[2];
    long long MoveCost[2];
    clock_t lasttime;
public:
    Statistic();
    void reset();
    void print();
    void increaseOneGame();
    void increaseOneMove(int player, int cost);
    void setWinner(int player);
    int tick();
};

#endif
