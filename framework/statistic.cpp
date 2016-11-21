#include "statistic.h"

Statistic::Statistic(){
    this->reset();
}

void Statistic::reset(){
    this->GameCount = 0;
    for(int i = 0 ; i < 2 ; i++){
        this->WinPlayer[i] = 0;
        this->MoveCost[i] = 0;
        this->MoveCount[i] = 0;
    }
    this->tick();
}

int Statistic::tick(){
    int re = clock() - this->lasttime;
    this->lasttime = clock();
    return re;
}

void Statistic::increaseOneGame(){
    this->GameCount++;
}

void Statistic::increaseOneMove(int player, int cost){
    this->MoveCount[player]++;
    this->MoveCost[player] += cost;
}

void Statistic::setWinner(int player){
    this->WinPlayer[player]++;
}

void Statistic::print(){
    printf("Total Game: %d\n", this->GameCount);
    for(int i = 0 ; i < 2 ; i++){
        printf("Player%d:\n", i);
        printf("WinRate: %.6f\n", double(this->WinPlayer[i]) / double(this->GameCount));
        printf("MoveCount: %d\n", this->MoveCount[i]);
        printf("MoveCost: %lld\n", this->MoveCost[i]);
        printf("Avg MoveCost: %lld\n", this->MoveCost[i] / (long long)this->MoveCount[i]);
    }
}
