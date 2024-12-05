#include <iostream>
#include <limits>
#include <stack>
#include "bot.h"

// initializes the bot with a pointer
Bot::Bot(GameBoard* board_ptr, unsigned int symbol){
    this->board = board_ptr;
    this->symbol = symbol;
}

// plays the bot's next move on the board
void Bot::take_turn(){
    this->evaluate(this->symbol, 0);
    apply_move(this->move_choice, this->symbol);
}

// gets every legal move the bot can play from a given board
std::vector<unsigned int> Bot::get_moves(){
    std::vector<unsigned int> moves;
    int row {0}, col {0};
    for (int i = 0; i < 9; i++){
        if (this->board->get_cell(row, col) == SYM_NONE)
            moves.push_back((row * 10) + col);
        col++;
        if (col == 3){
            col = 0;
            row++;
        }
    }
    return moves;
}

// applies a move, represented as an integer to a given board
void Bot::apply_move(int move, int symbol){
    int col = move % 10;
    move -= col;
    int row = move / 10;
    this->board->update_cell(row, col, symbol); 
}

// evaluates the value of a game board at a given depth{
int Bot::evaluate(int to_play, int depth){
    // check base cases (game is drawn or won)
    int winner = board->check_win();
    if (winner != SYM_NONE){
        if (winner == this->symbol)
            return (depth == 1) ? 100 : 1; // this may return 100 as the model should ALWAYS take a move that will instantly win it the game
        return (depth < 3) ? -200 : -2; // this may return -100 as the model should NEVER take a move that will instantly lose it the game (unless all moves are loosing)
    }
    if (!board->get_free_spaces())
        return 0;
    // evaluate each possible move from this point
    std::vector<unsigned int> moves = get_moves();
    int move_count = moves.size();
    int max {std::numeric_limits<int>::min()}, max_index {-1}, min {std::numeric_limits<int>::max()};
    for (int i = 0; i < move_count; i++){
        this->apply_move(moves[i], to_play);
        int value = evaluate((3 ^ to_play), depth + 1);
        this->board->rollback();
        if (value > max){
            max = value;
            max_index = i;
        }
        else if (value < min)
            min = value;

    }
    // if we've reached the end, update the chosen move
    if (depth == 0)
        this->move_choice = moves[max_index];
    // check if this a maximizing node, and return the corresponding value
    if (to_play == this->symbol)
        return max;
    else
        return min;
}