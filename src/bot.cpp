#include <iostream>
#include "bot.h"

// initializes the bot with a pointer
Bot::Bot(GameBoard* board_ptr, unsigned int symbol){
    this->board = board_ptr;
    this->symbol = symbol;
}

// plays the bot's next move on the board
void Bot::take_turn(){
    this->get_moves();
    int row = this->decide();
    // parse the row and colum from the decided move
    int col = row % 10;
    row -= col;
    row /= 10;
    this->board->update_cell(row, col, this->symbol);
    this->possible_moves.clear();
}

// gets every legal move the bot can play
void Bot::get_moves(){
    int row = 0; 
    int col = 0;
    for (int i = 0; i < 9; i++){
        if (this->board->get_cell(row, col) == SYM_NONE)
            this->possible_moves.push_back((row * 10) + col);
        col++;
        if (col == 3){
            col = 0;
            row++;
        }
    }
}

// returns the move the bot makes
unsigned int Bot::decide(){
    return this->possible_moves[0];
}
