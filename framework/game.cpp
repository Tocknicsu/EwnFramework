#include "game.h"


Game::Game(){
    this->player[0] = NULL;
    this->player[1] = NULL;
}

Game::~Game(){
}

void Game::init(){
    memset(this->board, 0, sizeof(this->board));
    this->turn = 0;
    int pos[6][2] = {
        {0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {2, 0}
    };
    int p[6] = {0, 1, 2, 3, 4, 5};
    for(int k = 0 ; k < 2 ; k++){
        std::random_shuffle(p, p+6);
        for(int i = 0 ; i < 6 ; i++){
            if(k == 0){
                this->chess[k][i].set(pos[p[i]][0], pos[p[i]][1], 1);
                this->board[pos[p[i]][0]][pos[p[i]][1]] = i + 1;
            } else {
                this->chess[k][i].set(4 - pos[p[i]][0], 4 - pos[p[i]][1], 1);
                this->board[4-pos[p[i]][0]][4-pos[p[i]][1]] = i + 7;
            }
        }
    }
}

void Game::setBoard(int _board[5][5]){
    for(int i = 0 ; i < 2 ; i++)
        for(int j = 0 ; j < 6 ; j++)
            this->chess[i][j].set(0, 0, 0);
    for(int i = 0 ; i < 5 ; i++)
        for(int j = 0 ; j < 5 ; j++){
            this->board[i][j] = _board[i][j];
            if(this->board[i][j]){
                int index = this->board[i][j] - 1;
                this->chess[index / 6][index % 6].set(i, j, 1);
            }
        }
}

void Game::setDice(int _dice){
    this->dice = _dice;
}
void Game::setTurn(int _turn){
    this->turn = _turn;
}

void Game::setPlayer(int index, Player *_player){
    this->player[index] = _player;
}

void Game::print(){
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++)
            printf("%2d ", this->board[i][j]);
        printf("\n");
    }
}

void Game::switchPlayer(){
    this->turn ^= 1;
}

void Game::generatorDice(){
    this->dice = rand() % 6 + 1;
}

void Game::genPlayerBoard(int playerBoard[5][5]){
    if(turn == 0){
        for(int i = 0 ; i < 5 ; i++)
            for(int j = 0 ; j < 5 ; j++)
                playerBoard[i][j] = this->board[i][j];
    } else {
        for(int i = 0 ; i < 5 ; i++)
            for(int j = 0 ; j < 5 ; j++){
                playerBoard[i][j] = this->board[4-i][4-j];
                if(playerBoard[i][j] != 0){
                    if(playerBoard[i][j] <= 6){
                        playerBoard[i][j] += 6;
                    } else {
                        playerBoard[i][j] -= 6;
                    }
                }
            }
    }
}

Movement Game::generatorMove(){
    int playerBoard[5][5];
    this->genPlayerBoard(playerBoard);
    Movement movement = this->player[turn]->generatorMove(playerBoard, dice);
    return movement;
}

bool Game::isValidMove(Movement movement){
    if(movement.direction <= 0 || movement.direction > 3)
        return false;
    int index = movement.index - 1;
    int dice = this->dice - 1;
    if(index != dice){
        if(this->chess[this->turn][dice].getExist())
            return false;
        int start = index;
        int end   = dice;
        if(start > end)
            std::swap(start, end);
        for(int i = start + 1 ; i < end ; i++){
            if(this->chess[this->turn][i].getExist())
                return false;
        }
    }
    if(!this->chess[this->turn][index].getExist())
        return false;
    int x = this->chess[this->turn][index].getX();
    int y = this->chess[this->turn][index].getY();
    int nx = x + (this->turn ? -1 : 1) * (movement.direction & 1 ? 1 : 0);
    int ny = y + (this->turn ? -1 : 1) * (movement.direction & 2 ? 1 : 0);
    if(nx < 0 || ny < 0 || nx >= 5 || ny >= 5)
        return false;
    return true;
}

void Game::move(Movement movement){
    int index = movement.index - 1;
    int dice = this->dice - 1;
    int x = this->chess[this->turn][index].getX();
    int y = this->chess[this->turn][index].getY();
    int nx = x + (this->turn ? -1 : 1) * (movement.direction & 1 ? 1 : 0);
    int ny = y + (this->turn ? -1 : 1) * (movement.direction & 2 ? 1 : 0);
    int eaten = this->board[nx][ny];
    if(eaten){
        eaten--;
        this->chess[eaten / 6][eaten % 6].set(0, 0, 0);
    }
    this->board[nx][ny] = this->board[x][y];
    this->board[x][y] = 0;
    this->chess[this->turn][index].set(nx, ny, 1);
}

bool Game::terminated(){
    if(this->board[0][0] && this->board[0][0] >= 7)
        return true;
    if(this->board[4][4] && this->board[4][4] <= 6)
        return true;
    for(int k = 0 ; k < 2 ; k++){
        bool end = true;
        for(int i = 0 ; i < 6 ; i++)
            if(this->chess[k][i].getExist())
                end = false;
        if(end)
            return true;
    }
    return false;
}

void Game::gameOver(int player){
    this->player[0]->gameOver(player == 0);
    this->player[1]->gameOver(player == 1);
}

Chess Game::getChess(int player, int index){
    return this->chess[player][index];
}

int Game::getDice(){
    return this->dice;
}
