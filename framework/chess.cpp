#include "chess.h"

Chess::Chess(){
}

void Chess::set(int _x, int _y, int _exist){
    x = _x;
    y = _y;
    exist = _exist;
}

int Chess::getX(){
    return x;
}

int Chess::getY(){
    return y;
}

int Chess::getExist(){
    return exist;
}
