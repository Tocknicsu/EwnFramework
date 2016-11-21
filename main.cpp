#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "game.h"
#include "randomAI.h"
#include "tdAI.h"
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
    RandomAI randomAI;
    TDAI tdAI;
    TDAI tdAI2;
    player[0] = (Player*)&tdAI;
    player[1] = (Player*)&tdAI2;
    int arg_count = 2;
    for(int i = 0 ; i < 2 ; i++){
        int ai_argc = atoi(argv[arg_count++]);
        char *ai_argv[ai_argc];
        for(int j = 0 ; j < ai_argc ; j++){
            ai_argv[j] = argv[arg_count++];
        }
        game.setPlayer(i, player[i]);
        player[i]->init(ai_argc, ai_argv);
    }
    Movement movement;
    Statistic statistic;
    statistic.reset();
    int last_player;
    while(times--){
        game.init();
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
