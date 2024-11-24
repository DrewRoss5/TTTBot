#include <iostream>
#include <vector>

#include "board.h"

// constructs an empty TicTacToe board
GameBoard::GameBoard(){
    for (int i = 0; i < 9; i++)
        this->board.push_back(SYM_NONE);
}

// returns the integer representing the symbol at row, col. This function does not validate input.
unsigned GameBoard::get_cell(unsigned int row, unsigned int col) const{
    return this->board[(row * 3) + col];
}

// sets the cell at row, col to a given value. This is a non-operation if the cell is already occupied
void GameBoard::update_cell(unsigned int row, unsigned int col, unsigned int symbol){
    int index = (row * 3) + col;
    if (this->board[index] == SYM_NONE)
        this->board[index] = symbol;
}

// checks if there is a winner, returns SYM_NONE if there is no winner, or the symbol that won if there is
unsigned GameBoard::check_win() const{
    int tmp;
    for (int i = 0; i < 3; i++){
        // check the ith row for a win
        int row_index = 3 * i;
        tmp = this->board[row_index];
        if (tmp != SYM_NONE && this->board[row_index + 1] == tmp && this->board[row_index + 2] == tmp)
            return tmp;
        // check the ith column for a win
        tmp = this->get_cell(0, i);
        if (tmp != SYM_NONE && this->get_cell(1, i) == tmp && this->get_cell(2, i) == tmp)
            return tmp;
    }
    // check each diagonal for a win
    tmp = this->get_cell(1, 1);
    if (tmp != SYM_NONE && ((this->get_cell(0, 0) == tmp && this->get_cell(2, 2) == tmp) ||  (this->get_cell(0, 2) == tmp && this->get_cell(2, 0) == tmp)))
        return tmp;
    return SYM_NONE;
}

// displays the game board
void GameBoard::display() const{
    std::cout << "|";
    char symbol;
    for (int i = 0; i < 9; i++){
        std::cout << " " << SYMBOL_STR[this->board[i]] << " |";
        if (i != 8 && (i + 1) % 3 == 0)
            std::cout << "\n------------\n|";
    }
    std::cout << std::endl;
}