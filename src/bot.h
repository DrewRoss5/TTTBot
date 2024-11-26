#ifndef BOT_H
#define BOT_H

#include "board.h"

class Bot{
    public:
        Bot(GameBoard*, unsigned int symbol);
        void take_turn();
    private:    
        GameBoard* board;
        unsigned int symbol;
        unsigned int move_choice;
        std::vector<unsigned int> get_moves(GameBoard* game);
        void apply_move(int move, int symbol, GameBoard* game);
        int evaluate(GameBoard* game, int to_play, int depth); 
};

#endif