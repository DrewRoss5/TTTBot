#include <iostream>
#include "bot.h"

// initializes the bot with a pointer
Bot::Bot(GameBoard* board_ptr, unsigned int symbol){
    this->board = board_ptr;
    this->symbol = symbol;
}

// plays the bot's next move on the board
void Bot::take_turn(){
    this->evaluate(this->board, 0);
    apply_move(this->move_choice, this->board);
}

// gets every legal move the bot can play from a given board
std::vector<unsigned int> Bot::get_moves(GameBoard* game = nullptr){
    std::vector<unsigned int> moves;
    int row = 0; 
    int col = 0;
    for (int i = 0; i < 9; i++){
        if (game->get_cell(row, col) == SYM_NONE)
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
void Bot::apply_move(int move, GameBoard* game){
    int col = move % 10;
    move -= col;
    int row = move / 10;
    game->update_cell(row, col, this->symbol); 
}

// evaluates the value of a game board at a given depth
int Bot::evaluate(GameBoard* board, int depth){
    // check base cases (game is drawn or won)
    if (!board->get_free_spaces())
        return 0;
    int winner = board->check_win();
    if (winner != SYM_NONE){
        if (winner == this->symbol)
            return (depth == 1) ? 100 : 1; // this may return 100 as the model should ALWAYS take a move that will instantly win it the game
        return (depth == 1) ? -100 : -1; // this may return 100 as the model should NEVER take a move that will instantly loose it the game (unless all moves are loosing)
    }
    // evaluate each possible move from this point
    std::vector<unsigned int> moves = get_moves(board);
    int move_count = moves.size();
    int max = -10000;
    int max_index = -1;
    int parent_val = 0;
    for (int i = 0; i < move_count; i++){
        GameBoard tmp = *board;
        this->apply_move(moves[i], &tmp);
        int value = evaluate(&tmp, depth + 1);
        parent_val += value;
        if (value > max){
            max = value;
            max_index = i;
        }
    }
    // if we've reached the end, update the chosen move
    if (depth == 0)
        this->move_choice = moves[max_index];
    return parent_val;


}

// returns the move the bot makes
unsigned int Bot::decide(){
    return this->evaluate(this->board, 0);

}