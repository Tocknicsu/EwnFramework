#ifndef _CHESS_H_
#define _CHESS_H_

class Chess{
private:
    int x, y, exist;
public:
    Chess();
    void set(int _x, int _y, int _exist);
    int getX();
    int getY();
    int getExist();
};

#endif
