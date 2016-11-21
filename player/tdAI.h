#ifndef _TD_H_
#define _TD_H_
#include "player.h"
#include "game.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <stack>


class TDAI : Player {
private:
    struct Board{
        __int128 board;
        Board();
        Board(int _board[5][5]);
        int hashpos(int x, int y);
        int getTile(int x, int y);
        void setTile(int x, int y, int value);
        int getRow(int x);
        int getColumn(int x);
        int getRemainChess(int player);
    };
    struct Feature{
        int feature[12];
        Feature();
        Feature(const Feature& _feature);
        Feature(Board board);
    };
    bool train;
    double alpha;
    std::string filename;
    double **weight;
    std::vector<int> weight_size;
    double getValue(Feature feature);
    std::stack<Feature> history;
public:
    TDAI();
    ~TDAI();
    virtual void init(int argc, char **argv);
    virtual Movement generatorMove(int board[5][5], int dice);
    virtual void gameOver(int board[5][5], bool win);
};

#endif
