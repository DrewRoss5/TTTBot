#ifndef BOT_H
#define BOT_H

#include "board.h"

class Bot{
    public:
        Bot(GameBoard*, unsigned int symbol);
        void take_turn();
    private:    
        GameBoard* board;
        std::vector<unsigned int> possible_moves;
        unsigned int symbol;
        void get_moves();
        unsigned int decide();
};

#endif