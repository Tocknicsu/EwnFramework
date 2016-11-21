#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "game.h"
#include "randomAI.h"
#include "statistic.h"

int main(int argc, char **argv){
    if(argc < 2){
        printf("./ewn [play_times]\n");
        exit(1);
    }
    int times = atoi(argv[1]);
    srand(time(NULL));
    Game game;
    Player *player[2];
    RandomAI ai[2];
    player[0] = (Player*)&ai[0];
    player[1] = (Player*)&ai[1];
    for(int i = 0 ; i < 2 ; i++){
        game.setPlayer(i, player[i]);
    }
    Movement movement;
    Statistic statistic;
    int last_player;
    while(times--){
        game.init();
        //game.print();
        statistic.increaseOneGame();
        while(!game.terminated()){
            for(int k = 0 ; k < 2 && !game.terminated() ; k++){
                last_player = k;
                game.generatorDice();
                statistic.tick();
                do {
                    movement = game.generatorMove();
                } while(!game.isValidMove(movement));
                game.move(movement);
                statistic.increaseOneMove(k, statistic.tick());
                game.switchPlayer();
            }
        }
        game.gameOver(last_player);
        statistic.setWinner(last_player);
    }
    statistic.print();
    return 0;
}
