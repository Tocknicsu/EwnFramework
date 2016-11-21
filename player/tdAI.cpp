#include "tdAI.h"

TDAI::TDAI(){
}

TDAI::~TDAI(){
    if(train){
        int fd = open(filename.c_str(), O_WRONLY | O_CREAT, 0644);
        for(int i = 0 ; i < (int)weight_size.size() ; i++){
            int re = write(fd, weight[i], weight_size[i] * sizeof(double));
        }
    }
    for(int i = 0 ; i < (int)weight_size.size() ; i++)
        delete [] weight[i];
    delete [] weight;
}

void TDAI::init(int argc, char **argv){
    train = atoi(argv[0]);
    alpha = atof(argv[1]);
    filename = std::string(argv[2]);
    for(int i = 0 ; i < 10 ; i++)
        weight_size.push_back(16 * 16 * 16 * 16 * 16);
    for(int i = 0 ; i < 2 ; i++)
        weight_size.push_back(1 << 6);
        /*
    for(int i = 0 ; i < 12 ; i++)
        weight_size.push_back(1 << 17);
        */
    weight = new double* [(int)weight_size.size()]();
    int fd = open(filename.c_str(), O_RDONLY);
    for(int i = 0 ; i < (int)weight_size.size() ; i++){
        weight[i] = new double[weight_size[i]];
        int re = read(fd, weight[i], weight_size[i] * sizeof(double));
    }
    close(fd);
}

Movement TDAI::generatorMove(int board[5][5], int dice){
    Game game;
    game.setBoard(board);
    game.setDice(dice);
    game.setTurn(0);
    double best_winrate = -1;
    Movement best_movement;
    Feature best_feature;
    int next_board[5][5];
    for(int i = 1 ; i <= 6 ; i++){
        for(int j = 1 ; j <= 3 ; j++){
            Movement move;
            move.index = i;
            move.direction = static_cast<Movement::Direction>(j);
            if(game.isValidMove(move)){
                Game next = game;
                next.move(move);
                next.genPlayerBoard(next_board);
                Feature nextFeature(next_board);
                double winrate = getValue(nextFeature);
                if(winrate > best_winrate){
                    best_movement = move;
                    best_winrate = winrate;
                }
            }
        }
    }
    return best_movement;
}

void TDAI::gameOver(int board[5][5], bool win){
    if(train){
        Feature nextFeature, feature;
        double delta;
        feature = Feature(Board(board));
        delta = double(win) - getValue(feature);
        for(int i = 0 ; i < (int)weight_size.size() ; i++){
            weight[i][feature.feature[i]] += alpha * delta;
        }
        nextFeature = feature;
        while(history.size()){
            feature = history.top();
            history.pop();
            delta = getValue(nextFeature) - getValue(feature);
            for(int i = 0 ; i < (int)weight_size.size() ; i++){
                weight[i][feature.feature[i]] += alpha * delta;
            }
            nextFeature = feature;
        }
    }
}

double TDAI::getValue(TDAI::Feature feature){
    double value = 0;
    for(int i = 0 ; i < (int)weight_size.size() ; i++){
        value += weight[i][feature.feature[i]];
    }
    return value;
}

TDAI::Board::Board(){
    board = 0;
}

TDAI::Board::Board(int _board[5][5]){
    board = 0;
    for(int i = 0 ; i < 5 ; i++)
        for(int j = 0 ; j < 5 ; j++)
            setTile(i, j, _board[i][j]);
}

int TDAI::Board::hashpos(int x, int y){
    return 4 * (x * 5 + y);
}

int TDAI::Board::getTile(int x, int y){
    return (board >> hashpos(x, y)) & 0xf;
}

void TDAI::Board::setTile(int x, int y, int value){
    board |= (__int128)value << hashpos(x, y);
}

int TDAI::Board::getRow(int x){
    int re = 0;
    for(int i = 0 ; i < 5 ; i++)
        re |= getTile(x, i) << (4 * i);
    return re;
}

int TDAI::Board::getColumn(int x){
    int re = 0;
    for(int i = 0 ; i < 5 ; i++)
        re |= getTile(i, x) << (4 * i);
    return re;
}

int TDAI::Board::getRemainChess(int player){
    int re = 0;
    for(int i = 0 ; i < 5 ; i++)
        for(int j = 0 ; j < 5 ; j++){
            int tile = getTile(i, j);
            if(tile == 0) continue;
            tile -= 1;
            if(tile / 6 == player){
                re |= 1 << (tile % 6);
            }
        }
    return re;
}

TDAI::Feature::Feature(){
}

TDAI::Feature::Feature(const Feature& _feature){
    for(int i = 0 ; i < 12 ; i++)
        feature[i] = _feature.feature[i];
}

TDAI::Feature::Feature(Board board){
    for(int i = 0 ; i < 5 ; i++)
        feature[i] = board.getRow(i);
    for(int i = 0 ; i < 5 ; i++)
        feature[i+5] = board.getColumn(i);
    for(int i = 0 ; i < 2 ; i++)
        feature[i+10] = board.getRemainChess(i);
    /*
    int remain = (feature[10] << 6 ) | feature[11];
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            int tile = board.getTile(i, j);
            if(tile){
                tile--;
                feature[12+tile] = (remain << 5) + (i * 5 + j);
            }
        }
    }
    */
}
